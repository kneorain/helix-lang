from classes.Token import Processed_Line, Token, Token_List
from core.config import load_config

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from core.panic import panic
from functions._class import _class


def _match(ast_list: Token_List, current_scope, parent_scope, root_scope, modifiers=None) -> Processed_Line:
    print(ast_list)
    return Processed_Line("yessir", ast_list)