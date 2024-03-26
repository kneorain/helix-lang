from src.core.imports import (
    Processed_Line,
    Token,
    Token_List,
<<<<<<< HEAD
    load_config,
=======
    CONFIG,
>>>>>>> 5b3e87180733de6321e2707e5feed733434b5ce5
    INDENT_CHAR,
    re,
    panic,
    _class,
)

def _match(ast_list: Token_List, current_scope, parent_scope, root_scope, modifiers=None) -> Processed_Line:
    print(ast_list)
    return Processed_Line("yessir", ast_list)