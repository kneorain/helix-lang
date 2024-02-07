from classes.Token import Token_List, Token
from headder import INDENT_CHAR
from core.panic import panic
from os import path as os_path
import re2 as re

def extract_variables(ast_line: Token_List, root_scope) -> str:
    variables = {}
    # remove the fn keyword
    line = ast_line.line[1:]
    
    line = line[1:]

    in_param = False
    if line[0].token == "(" and line[1].token == ")":
        if line[2].token == "->":
            # no parameters, just a return type
            if line[3].token == ":" or line[3].token == "<\\r1>":
                panic(SyntaxError(f"<Hex(02.E3)>: Expected a return type after the {root_scope.get_keyword("FUNCTION")} keyword"), "->", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword("FUNCTION")))
            return {"return_type": line[3].token, "params": {}}
        else:
            # no parameters, no return type
            if line[2].token != ":" and line[2].token != "<\\r1>":
                panic(SyntaxError(f"<Hex(02.E3)>: Expected a colon after the parameters"), ":", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword("FUNCTION")))
            return {"return_type": None, "params": {}}
    elif line[0].token == "(":
        in_param = True
        line = line[1:]
    else:
        panic(SyntaxError(f"<Hex(02.E3)>: Expected an open parenthesis after the {root_scope.get_keyword("FUNCTION")} keyword"), "(", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword("FUNCTION")))
    
    in_generic: bool = False
    generic: str = ""
    generic_count: int = 0
    return_type: str = ""
    found_return_generic: bool = False
    
    if in_param:
        while line:
            if line[0].token == ")":
                if line[1].token == "->":
                    # no parameters, just a return type
                    if line[2].token == ":" or line[2].token == "<\\r1>":
                        panic(SyntaxError(f"<Hex(02.E3)>: Expected a return type after the {root_scope.get_keyword("FUNCTION")} keyword"), "->", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword("FUNCTION")))
                    return {"return_type": line[2].token, "params": variables}
                else:
                    # no parameters, no return type
                    if line[1].token != ":" and line[1].token != "<\\r1>":
                        panic(SyntaxError(f"<Hex(02.E3)>: Expected a colon after the parameters"), ":", file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword("FUNCTION")))
                    return {"return_type": None, "params": variables}
            if line[0].token == "<":
                generic_count += 1
                in_generic = True if generic_count > 0 else False
                if not in_generic:
                    in_generic = False
                    variables[tuple(variables.keys())[-1]] = {"type": variables[tuple(variables.keys())[-1]]["type"] + generic}
                    line = line[1:]
                    continue
                generic += "["
                line = line[1:]
            elif line[0].token == ">":
                generic_count -= 1
                in_generic = True if generic_count > 0 else False
                generic += "]"
                if not in_generic:
                    in_generic = False
                    variables[tuple(variables.keys())[-1]] = {"type": variables[tuple(variables.keys())[-1]]["type"] + generic}
                    line = line[1:]
                    continue
                line = line[1:]
            elif in_generic:
                generic += line[0].token
                line = line[1:]
            elif line[0].token == ",":
                line = line[1:]
            else:
                if line[1].token == ":":
                    variables[line[0].token] = {"type": line[2].token}
                    line = line[3:]
                else:
                    if line[0].token == "=":
                        panic(SyntaxError(f"<Hex(02.E3)>: Default values are not allowed in function parameters"), line[0].token, file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword("FUNCTION")))
                    if line[0].token == "<":
                        in_generic = True
                        generic = ""
                        continue
                    panic(SyntaxError(f"<Hex(02.E3)>: Expected a colon and a type after the variable name"), line[0].token, file=ast_line.file, line_no=ast_line.find_line_number(root_scope.get_keyword("FUNCTION")))
                    
    return variables
    

def process_modifiers(ast_list: Token_List, root_scope) -> list[str]:
    # all modifiers are optional
    # all allowed modifiers:
    #   - async
    #   - static
    #   - public
    #   - private
    #   - protected
    #   - final
    #   - virtual
    allowed_modifiers = (
        root_scope.get_keyword("ASYNC"),
        root_scope.get_keyword("PRIVATE"),
        root_scope.get_keyword("PROTECTED"),
        root_scope.get_keyword("PUBLIC"),
        root_scope.get_keyword("FINAL"),
        root_scope.get_keyword("UNSAFE"),
        root_scope.get_keyword("STATIC")
    )

    modifiers = []
    index = 0
    
    if ast_list.line[0].token != root_scope.get_keyword("FUNCTION"):
        line = ast_list.line.copy()
        while line:
            index += 1
            if line[0].token in allowed_modifiers:
                modifiers.append(line[0].token)
                line = line[1:]
            else:
                if line[0].token != root_scope.get_keyword("FUNCTION"):
                    return modifiers
                else:
                    break
        ast_list.line = ast_list.line[index-1:]
        return modifiers
    else:
        return modifiers


def contains(line: Token_List, compare: tuple):
    # check if any of the tokens in compare are in line and
    return any([_ in line for _ in compare])

def function(ast_list: Token_List, current_scope, parent_scope, root_scope) -> str:
    modifiers = process_modifiers(ast_list, root_scope)
    if ast_list.line[0].token != root_scope.get_keyword("FUNCTION"):
        # TODO: link with classes and other namespaces
        panic(SyntaxError(f"<Hex(02.E3)>: Expected the {root_scope.get_keyword("FUNCTION")} keyword"), file=ast_list.file, line_no=ast_list.find_line_number(root_scope.get_keyword("FUNCTION")))
    
    variables = extract_variables(ast_list, root_scope)
    name = ast_list.line[1].token
    
    print(variables, modifiers, name)

    output: str = ""
    output += f"{INDENT_CHAR*ast_list.indent_level}def "
    output += " ".join([_.token for _ in ast_list.line[1:]])
    return output