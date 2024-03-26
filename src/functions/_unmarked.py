<<<<<<< HEAD
from types import UnionType
from src.classes.Token import Token, Token_List, Processed_Line
from src.config import load_config
from src.token.tokenize_line import tokenize_line

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from src.panic import panic

"""
=======
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
from src.core.imports import (
    Token_List,
    UnionType,
    Processed_Line,
    INDENT_CHAR,
    panic,
<<<<<<< HEAD
)
"""

def _unmarked(ast_list: Token_List, current_scope, parent_scope, root_scope, ignore_main) -> str:

    # example: name = "John" ->  name.set("John")
    # example: a, b = 5, 6 ->  a.set(5); b.set(6)
    # example: a . somethign = 12 ->  a.something.set(12)
    # example: a, b = (5, 6), (7, 8)  ->  a.set((5, 6)); b.set((7, 8))
    # example: a, b = (5, 6), somecall("yes", a=19) -> a.set((5, 6)); b.set(somecall("yes", a=19))
    
    output = ""
    
    if ast_list.indent_level == 0 and not ignore_main:
        panic(SyntaxError("You cannot have code outside of a function"), ast_list[0], file=ast_list.file, line_no=ast_list[0].line_number)
    
    if "=" in ast_list:
        # so something like a = 5 would become a.set(5)
        # and something like a, b = 5, 6 would become a.set(5); b.set(6)
        if ast_list.count("=") > 1:
            panic(
                SyntaxError("Multiple assignments are not allowed in a single line\nYou can use un-packing instead and do `a, b = 1, 2` rather then `a = 1, b = 2`"),
                ast_list[ast_list.index("=")].token,
                file=ast_list.file,
                line_no=ast_list[0].line_number
            )
    
        temp = ast_list.get_all_before("=")
        variables: dict[str, Token_List] = {} # {name: value}
        name = ""
        in_brackets = False
        bracket_count: int = 0
        
        for token in temp:
            if token == ":" and not in_brackets:
                panic(SyntaxError("You cannot use the `:` operator in a variable assignment"), token, file=ast_list.file, line_no=ast_list[0].line_number)
            if token == "," and not in_brackets:
                variables[name] = ""
                name = ""
                continue
            elif token == "::" and not in_brackets:
                panic(SyntaxError("You cannot use the `::` operator in a variable assignment"), token, file=ast_list.file, line_no=ast_list[0].line_number)
=======
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
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
            elif token in ("(", "[", "{"):
                in_brackets = True
                bracket_count += 1
            elif token in (")", "]", "}"):
                bracket_count -= 1
                if bracket_count == 0:
                    in_brackets = False
            name += token.token + " "
<<<<<<< HEAD
        else:
            if name:
                variables[name] = ""
                name = ""
                
        temp = ast_list.get_all_after("=")
        value = Token_List([], ast_list.indent_level, ast_list.file)
        in_brackets = False
        bracket_count: int = 0
        
        index = 0
        
        for token in temp:
            if token == "," and not in_brackets:
                try:
                    variables[tuple(variables.keys())[index]] = value
                except IndexError:
                    panic(SyntaxError("Too many values to unpack for assignment"), "=", file=ast_list.file, line_no=ast_list[index].line_number)
                index += 1
                value = Token_List([], ast_list.indent_level, ast_list.file)
=======

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
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
                continue
            elif token in ("(", "[", "{"):
                in_brackets = True
                bracket_count += 1
            elif token in (")", "]", "}"):
                bracket_count -= 1
                if bracket_count == 0:
                    in_brackets = False
<<<<<<< HEAD
            value.line.append(token)
        else:
            if value:
                try:
                    variables[tuple(variables.keys())[index]] = value
                except IndexError:
                    panic(SyntaxError("Too many values to unpack for assignment"), "=", file=ast_list.file, line_no=ast_list[-1].line_number)
                value = Token_List([], ast_list.indent_level, ast_list.file)

        if index != len(variables.keys()) - 1:
            panic(SyntaxError("Not enough values to unpack for assignment"), "=", file=ast_list.file, line_no=ast_list[-1].line_number)
        
        
        def split_or(str_: str, value: UnionType) -> str:
            # so something like split_or("a, b", "," or "a") would return either "a" or "b" depending on the value
            return str_.split(",")[0] if value == "," else str_.split(",")[1]
            return value
        
        
        for name, value in variables.items():
            if name not in current_scope.variables and name not in parent_scope.variables:
                #panic(NameError(f"Name '{name.strip()}' is not defined"), name.strip(), file=ast_list.file, line_no=ast_list[0].line_number)
                # TODO: add support for checking if the name is defined in the parent scope
                pass
            
            if "::" in value:
                static_call = value.get_all_after("::")[0]
                # TODO: add support for static calls

            if "self" not in name:
                output += f"{INDENT_CHAR*ast_list.indent_level}try:\n"
                try:
                    output += f"{INDENT_CHAR*(ast_list.indent_level+1)}{name} = {value.full_line()}\n"
                except KeyError:
                    panic(NameError(f"Variable '{name.strip()}' is not defined"), name.strip(), file=ast_list.file, line_no=ast_list[0].line_number)
                output += f"{INDENT_CHAR*ast_list.indent_level}except AttributeError:\n"
                output += f"{INDENT_CHAR*(ast_list.indent_level+1)}{name} = {value.full_line()}\n"
                output += f"{INDENT_CHAR*(ast_list.indent_level+1)}print(\"WARN: \\\"{name}\\\" does not contain the attribute '__set__' falling back to default assignment.\")\n"
            else:
                output += f"{INDENT_CHAR*ast_list.indent_level}{name} = {value.full_line()}\n"
                # TODO: add support for self calls
    else:
        output = INDENT_CHAR*ast_list.indent_level + ast_list.full_line().replace("::", ".")

    return Processed_Line(output, ast_list)
=======
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
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
