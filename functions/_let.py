from classes.Token import Token, Token_List, Processed_Line
from core.config import load_config
from core.token.tokenize_line import tokenize_line

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from core.panic import panic


def _let(ast_list: Token_List, current_scope, parent_scope, root_scope) -> str:
    output = ""
    
    # so something like a = 5 would become a.set(5)
    # and something like a, b = 5, 6 would become a.set(5); b.set(6)
    if ast_list.count("=") > 1:
        panic(
            SyntaxError("Multiple assignments are not allowed in a single line\nYou can use un-packing instead and do `a, b = 1, 2` rather then `a = 1, b = 2`"),
            ast_list[ast_list.index("=")].token,
            file=ast_list.file,
            line_no=ast_list[0].line_number
        )

    temp = ast_list.splice(1).get_all_before("=") if "=" in ast_list else ast_list.splice(1)
    variables: dict[str, Token_List] = {} # {name: value}
    name = ""
    type = ""
    in_type: bool = False
    in_brackets = False
    generic_count: int = 0
    
    if ":" not in temp:
        panic(SyntaxError("You must specify the type of the variable"), "=", file=ast_list.file, line_no=ast_list[0].line_number)
    
    for token in temp:
        if in_type:
            if (token == "," or token == "=") and generic_count == 0:
                in_type = False
            if token in ("(", "[", "{"):
                panic(SyntaxError("You cannot use brackets in a type declaration"), token, file=ast_list.file, line_no=ast_list[0].line_number)
            elif token in (")", "]", "}"):
                panic(SyntaxError("You cannot use brackets in a type declaration"), token, file=ast_list.file, line_no=ast_list[0].line_number)
            
            elif token == "<":
                generic_count += 1
            
            elif token == ">":
                generic_count -= 1
                if generic_count == 0:
                    in_type = False
            
            type += token.token + " "

            if not in_type:
                variables[name.strip()] = {"type": type.strip().replace("<", "[").replace(">", "]"), "value": ""}
                name = ""
                type = ""
                continue
            
            continue
        if token == ":" and not in_brackets:
            in_type = True
            continue
        if token == "," and not in_brackets:
            variables[name.strip()] = {"type": type.strip().replace("<", "[").replace(">", "]") if type else "", "value": ""}
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
            variables[name.strip()] = {"type": type.strip().replace("<", "[").replace(">", "]") if type else "", "value": ""}
            name = ""

    if "=" in ast_list:
        temp = ast_list.get_all_after("=")
        value = Token_List([], ast_list.indent_level, ast_list.file)
        in_brackets = False
        bracket_count: int = 0
        index = 0
        
        for token in temp:
            if token == "," and not in_brackets:
                try:
                    variables[tuple(variables.keys())[index]]["value"] = value
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
                    variables[tuple(variables.keys())[index]]["value"] = value
                except IndexError:
                    panic(SyntaxError("Too many values to unpack for assignment"), "=", file=ast_list.file, line_no=ast_list[-1].line_number)
                value = Token_List([], ast_list.indent_level, ast_list.file)
    
    print(variables)
        
        
