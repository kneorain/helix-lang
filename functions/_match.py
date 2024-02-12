from classes.Token import Processed_Line, Token_List, Token
from headder import INDENT_CHAR
from core.panic import panic
from functions._class import _class
from os import path as os_path
import re2 as re

def _match(ast_list: Token_List, current_scope, parent_scope, root_scope, modifiers=None) -> str:
    print(ast_list)
    return "yessir"