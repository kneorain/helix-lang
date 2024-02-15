from classes.Token import Processed_Line, Token, Token_List
from core.config import load_config

INDENT_CHAR = load_config().Formatter["indent_char"]

from os import path as os_path

re = __import__(load_config().Transpiler["regex_module"])

from core.panic import panic
from functions._class import _class


def _match(ast_list: Token_List, current_scope, parent_scope, root_scope, modifiers=None) -> str:
    print(ast_list)
    return "yessir"