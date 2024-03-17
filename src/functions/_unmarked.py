from src.core.imports import (
    Token_List,
    UnionType,
    Processed_Line,
    INDENT_CHAR,
    panic,
    INDENT_CHAR,
    Scope,
)

class UnmarkedTranslator:
    def __init__(self, ast_list: Token_List, current_scope: Scope, parent_scope: Scope, root_scope: Scope, ignore_main: bool):
        self.ast_list = ast_list
        self.current_scope = current_scope
        self.parent_scope = parent_scope
        self.root_scope = root_scope
        self.ignore_main = ignore_main

    def parse(self) -> Processed_Line:
        if self._check_main_rule():
            return self._process_assignment()
        else:
            return self._process_non_assignment()

    def _check_main_rule(self) -> bool:
        if self.ast_list.indent_level == 0 and not self.ignore_main:
            panic(SyntaxError("You cannot have code outside of a function"), self.ast_list[0], file=self.ast_list.file, line_no=self.ast_list[0].line_number)
        return "=" in self.ast_list

    def _process_assignment(self) -> Processed_Line:
        self._validate_multiple_assignments()
        variables = self._extract_variables_before_equal()
        self._parse_assignment_values(variables)

        # output = self._generate_assignment_output(variables)
        # TODO: Fix the above code
        _output: list[str] = [f"{name} = {value}" for name, value in variables.items()]
        output = "\n".join([f"{INDENT_CHAR * self.ast_list.indent_level}{i}" for i in _output])
        del variables, _output
        return Processed_Line(output, self.ast_list)

    def _process_non_assignment(self) -> Processed_Line:
        return Processed_Line(INDENT_CHAR * self.ast_list.indent_level + self.ast_list.full_line().replace("::", "."), self.ast_list)

    def _validate_multiple_assignments(self):
        if self.ast_list.count("=") > 1:
            panic(
                SyntaxError("Multiple assignments are not allowed in a single line\nYou can use un-packing instead and do `a, b = 1, 2` rather than `a = 1, b = 2`"),
                self.ast_list[self.ast_list.index("=")].token,
                file=self.ast_list.file,
                line_no=self.ast_list[0].line_number
            )

    def _extract_variables_before_equal(self) -> dict[str, str | Token_List]:
        temp = self.ast_list.get_all_before("=")
        variables: dict[str, str | Token_List] = {}
        name = ""
        in_brackets = False
        bracket_count = 0

        for token in temp:
            if token == ":" and not in_brackets:
                panic(SyntaxError("You cannot use the `:` operator in a variable assignment"), token, file=self.ast_list.file, line_no=self.ast_list[0].line_number)
            if token == "," and not in_brackets:
                variables[name.strip()] = ""
                name = ""
                continue
            elif token == "::" and not in_brackets:
                panic(SyntaxError("You cannot use the `::` operator in a variable assignment"), token, file=self.ast_list.file, line_no=self.ast_list[0].line_number)
            elif token in ("(", "[", "{"):
                in_brackets = True
                bracket_count += 1
            elif token in (")", "]", "}"):
                bracket_count -= 1
                if bracket_count == 0:
                    in_brackets = False
            name += token.token + " "

        if name:
            variables[name.strip()] = ""
        return variables

    def _parse_assignment_values(self, variables: dict[str, str | Token_List]):
        temp = self.ast_list.get_all_after("=")
        value = ""
        in_brackets = False
        bracket_count = 0
        index = 0

        for token in temp:
            if token == "," and not in_brackets:
                variables[list(variables)[index]] = value.strip()
                index += 1
                value = ""
                continue
            elif token in ("(", "[", "{"):
                in_brackets = True
                bracket_count += 1
            elif token in (")", "]", "}"):
                bracket_count -= 1
                if bracket_count == 0:
                    in_brackets = False
            value += token.token + " "

        if value:
            variables[list(variables)[index]] = value.strip()

        if index != len(variables) - 1:
            panic(SyntaxError("Not enough values to unpack for assignment"), "=", file=self.ast_list.file, line_no=self.ast_list[-1].line_number)

    def _generate_assignment_output(self, variables: dict[str, str | Token_List]) -> str:
        output = ""
        for name, value in variables.items():
            if not self._is_variable_defined(name):
                continue
            output += f"{INDENT_CHAR * self.ast_list.indent_level}{name} = {value}\n"
        
        return output

    def _is_variable_defined(self, name: str) -> bool:
        return name in self.current_scope.variables or name in self.parent_scope.variables


def _unmarked(ast_list: Token_List, current_scope: Scope, parent_scope: Scope, root_scope: Scope, ignore_main: bool) -> Processed_Line:
    return UnmarkedTranslator(ast_list, current_scope, parent_scope, root_scope, ignore_main).parse()