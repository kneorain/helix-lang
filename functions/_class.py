from classes.Token import Processed_Line, Token, Token_List
from core.config import load_config

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from core.panic import panic

CLASS_EXTENSION = "::"
SEPARATOR_FOR_CLASSES = "+"

def _class(ast_list: Token_List, current_scope, parent_scope, root_scope, modifiers=None) -> str:
    allowed_modifiers = (
        root_scope.get_keyword("ASYNC"),
        root_scope.get_keyword("PRIVATE"),
        root_scope.get_keyword("PROTECTED"),
        root_scope.get_keyword("FINAL"),
        root_scope.get_keyword("UNSAFE"),
        root_scope.get_keyword("STATIC")
    )
    
    class_name:    str       = ast_list[1].token
    class_extends: tuple[Token] = [i for i in ast_list.get_all_after(CLASS_EXTENSION) if i.token != SEPARATOR_FOR_CLASSES and i.token != ":" and i.token != "(" and i.token != ")"] if ast_list[2].token == CLASS_EXTENSION else []
    
    [panic(SyntaxError(f"Unexpected token '{i.token}' in class extension"), i.token, file=ast_list.file, line_no=ast_list.find_line_number(i.token)) for i in class_extends if i.token in (CLASS_EXTENSION, SEPARATOR_FOR_CLASSES, "(", ")", ",")] if class_extends else None
    
    for i in class_extends:
        if i.token not in parent_scope.classes.keys():
            panic(NameError(f"Class '{i.token}' not found"), i.token, file=ast_list.file, line_no=ast_list.find_line_number(i.token))
        
    output = f"class {class_name}"
    if class_extends:
        output += f"({', '.join([i.token for i in class_extends])}, metaclass=multimeta)"
    else:
        output += "(metaclass=multimeta)"
    output += ":"
    
    parent_scope.classes[class_name] = {
        "extends": class_extends,
        "modifiers": modifiers,
        "unsafe": False,
        "static": False,
        "private": False,
        "protected": False,
        "final": False,
    }
    
    if modifiers:
        if root_scope.get_keyword("ASYNC") in modifiers:
            panic(SyntaxError(f"Classes cannot be async"), file=ast_list.file, line_no=ast_list.find_line_number(root_scope.get_keyword("ASYNC")))
        if root_scope.get_keyword("STATIC") in modifiers:
            panic(SyntaxError(f"Classes cannot be static"), file=ast_list.file, line_no=ast_list.find_line_number(root_scope.get_keyword("STATIC")))
        parent_scope.classes[class_name] = {
            "extends": class_extends,
            root_scope.get_keyword("STATIC"): True if root_scope.get_keyword("STATIC") in modifiers else False,
            root_scope.get_keyword("PRIVATE"): True if root_scope.get_keyword("PRIVATE") in modifiers else False,
            root_scope.get_keyword("UNSAFE"): True if root_scope.get_keyword("UNSAFE") in modifiers else False,
        }
    else:
        parent_scope.classes[class_name] = {
            "extends": class_extends,
            "unsafe": False,
            "static": False,
            "final": False,
        }

    return Processed_Line(output, ast_list)