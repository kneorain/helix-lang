from classes.Token import Token, Token_List, Processed_Line
from core.config import load_config
from core.token.tokenize_line import tokenize_line
import globals

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
    variables: dict[str, dict[str, Token_List]] = {} # {name: {type: Token_List, value: Token_List}}
    name = ""
    type: Token_List = Token_List([], ast_list.indent_level, ast_list.file)
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
            
            type.line.append(token)

            if not in_type:
                variables[name.strip()] = {"type": type.replace("<", "[").replace(">", "]"), "value": ""}
                name = ""
                type = Token_List([], ast_list.indent_level, ast_list.file)
                continue
            
            continue
        if token == ":" and not in_brackets:
            in_type = True
            continue
        if token == "," and not in_brackets:
            variables[name.strip()] = {"type": type.replace("<", "[").replace(">", "]") if type.line else "", "value": ""}
            name = ""
            continue
        elif token == "::" and not in_brackets:
            panic(SyntaxError("You cannot use the `::` operator in a variable assignment"), token, file=ast_list.file, line_no=ast_list[0].line_number)
        elif token in ("(", "[", "{"):
            in_brackets = True
            try:
                bracket_count += 1
            except UnboundLocalError:
                panic(SyntaxError(f"Unknown Keyword '{ast_list[0].token}'"), ast_list[0].token, file=ast_list.file, line_no=ast_list[0].line_number)
        elif token in (")", "]", "}"):
            bracket_count -= 1
            if bracket_count == 0:
                in_brackets = False
        name += token.token + " "
    else:
        if name:
            variables[name.strip()] = {"type": type.replace("<", "[").replace(">", "]") if type.line else "", "value": ""}
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
    
    def mass_replace(string: str, replacements: dict[str, str]) -> str:
        for key, value in replacements.items():
            string = string.replace(key, value)
        return string
    
    cleaning = {
        " , ": ", ",
        " [ ": "[" ,
        " ] ": "]" ,
        " ]": "]"
    }
    
    override_dispatch_error = False
    broken_type = False
    
    for name, value in variables.items():
        null_value = True if "?" in value["type"] else False
        if null_value:
            value["type"].remove("?")

        current_scope.variables[name] = value["type"].full_line().strip() if not isinstance(value["type"], str) else value["type"]
        
        value["type"] = (type if type.full_line().strip() else panic(SyntaxError("You must specify the type of the variable"), "=", file=ast_list.file, line_no=ast_list[0].line_number)) if not value["type"] else value["type"]
        #value["value"] = (
        #    (
        #        ' '.join([_.token for _ in value["type"].get_all_before("[")]) if "[" in value["type"]
        #        else value["type"].full_line()
        #    )
        #    + "(" + (
        #        value["value"].full_line() if value["value"]
        #        else "None"
        #
        #        if null_value
        #        else null_value
        #    )
        #    + ")" + (
        #        (".__set_generic__(\"[" + mass_replace(extract_generics_from_type(value["type"]).full_line().strip(), cleaning) + ']")')
        #        if "[" in value["type"]
        #        else ""
        #    )
        #) if not value["type"] else value["value"].full_line()
        
        
        value["value"] = (
            (value["value"].full_line()
            ) if (
                value["value"]
            ) else (
                ' '.join([_.token for _ in value["type"].get_all_before("[")])
                if (
                    "[" in value["type"]
                ) else (
                    value["type"].full_line()
                )
            ) + "(" + (
                "None"
                if null_value
                else null_value
            ) + ")"
        ) if (
            not value["type"] and not null_value
        ) else (
            "None"
        ) if (
            null_value and not value["value"]
        ) else (
            ' '.join([_.token for _ in value["type"].get_all_before("[")])
            if (
                "[" in value["type"]
            ) else (
                value["type"].full_line() + "(" + ")"
            )
        ) if (
            not value["value"]
        ) else (
            value["value"].full_line()
        )
        
        
        for values in globals.IGNORE_TYPES_MAP:
            if values in value["type"]:
                value["value"] = "Any"
                broken_type = True
        
        value["type"] = mass_replace(value["type"].full_line().strip(), cleaning) if not broken_type else "Any"

        if not null_value:
            output += f"{INDENT_CHAR*(ast_list.indent_level + (1 if override_dispatch_error else 0))}{name}: {globals.replace_primitive(value['type'])} = {globals.replace_primitive(value['type'], 3) if globals.replace_primitive(value['type'], 3) not in value['value'] else ''}({value['value']})\n"
        elif null_value and value["value"] == "None":
            output += f"{INDENT_CHAR*(ast_list.indent_level + (1 if override_dispatch_error else 0))}{name}: Optional[{globals.replace_primitive(value['type'])}] = {value['value']}\n"
        elif null_value and value["value"]:
            output += f"{INDENT_CHAR*(ast_list.indent_level + (1 if override_dispatch_error else 0))}{name}: Optional[{globals.replace_primitive(value['type'])}]= {globals.replace_primitive(value['type'], 3) if globals.replace_primitive(value['type'], 3) not in value['value'] else ''}({value['value']})\n"
        #    + "\n" + (
        #    (
        #        INDENT_CHAR*(ast_list.indent_level) + "print(" + name + ")\n"
        #        + INDENT_CHAR*(ast_list.indent_level) + "if isinstance(" + name + ", " + "Exception):\n"
        #        + INDENT_CHAR*(ast_list.indent_level + 1) + "raise " + name + "\n"
        #    )
        #)
        #if override_dispatch_error:
        #    output  = f"{INDENT_CHAR*ast_list.indent_level}try:\n{output}{INDENT_CHAR*ast_list.indent_level}except DispatchError:\n{INDENT_CHAR*((ast_list.indent_level+1))}panic(TypeError(f\"Method '{value["type"]}' expects, '{{str(tuple({value["type"]}.__annotations__.values())[-1]).replace('|', 'or')}}', got something else.\"), ':', file=inspect.stack()[0].filename, line_no=inspect.stack()[0].lineno-8)\n"
        #    output += f"{INDENT_CHAR*ast_list.indent_level}except Exception as {name}:\n{INDENT_CHAR*((ast_list.indent_level+1))}panic({name}, ':', file=inspect.stack()[0].filename, line_no=inspect.stack()[0].lineno-8)\n"
    return Processed_Line(output, ast_list)
