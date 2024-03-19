from types import UnionType
from src.classes.Token import Token, Token_List, Processed_Line
from src.config import load_config
from src.token.tokenize_line import tokenize_line

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from src.panic import panic

"""
from src.core.imports import (
    Token_List,
    UnionType,
    Processed_Line,
    INDENT_CHAR,
    panic,
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
            elif token in ("(", "[", "{"):
                in_brackets = True
                bracket_count += 1
            elif token in (")", "]", "}"):
                bracket_count -= 1
                if bracket_count == 0:
                    in_brackets = False
            name += token.token + " "
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
                continue
            elif token in ("(", "[", "{"):
                in_brackets = True
                bracket_count += 1
            elif token in (")", "]", "}"):
                bracket_count -= 1
                if bracket_count == 0:
                    in_brackets = False
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