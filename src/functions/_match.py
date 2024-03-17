from src.core.imports import (
    Processed_Line,
    Token,
    Token_List,
    CONFIG,
    INDENT_CHAR,
    re,
    panic,
    _class,
)

def _match(ast_list: Token_List, current_scope, parent_scope, root_scope, modifiers=None) -> Processed_Line:
    print(ast_list)
    return Processed_Line("yessir", ast_list)