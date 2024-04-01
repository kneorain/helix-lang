import src.core.core as core
from src.core.imports import (
    Processed_Line,
    Token_List,
    Scope,
    INDENT_CHAR,
    panic,
)

def _unless(ast_list: Token_List, current_scope: Scope, parent_scope: Scope, root_scope: Scope, modifiers=None) -> Processed_Line:
    # unless condition:   ->   if not condition:
    # else if condition:  ->   elif condition:
    output = ""
    if ast_list[0].token == core.find_keyword("UNLESS"):
        output = f"if not ({ast_list.splice(1, -1).full_line()}):"
    elif ast_list[0].token == core.find_keyword("IF"):
        output = f"if ({ast_list.splice(1, -1).full_line()}):"
    elif ast_list[0].token == core.find_keyword("ELSE_IF"):
        output = f"elif ({ast_list.splice(1, -1).full_line()}):"
    elif ast_list[0].token == core.find_keyword("ELSE") and ast_list[1].token == core.find_keyword("IF"):
        output = f"elif ({ast_list.splice(2, -1).full_line()}):"
    elif ast_list[0].token == core.find_keyword("ELSE") and len(ast_list) == 2:
        output = "else:"
    else:
        panic(SyntaxError(f"Unexpected token '{ast_list[0].token}'"), ast_list[0].token, file=ast_list.file, line_no=ast_list.find_line_number(ast_list[0].token))
    
    return Processed_Line(INDENT_CHAR *ast_list.indent_level + output, ast_list)