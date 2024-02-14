from classes.Token import Token, Token_List
from core.config import load_config

INDENT_CHAR = load_config().Formatter["indent_char"]

from os import path as os_path

import re2 as re

from core.panic import panic


def _unmarked(ast_list: Token_List, current_scope, parent_scope, root_scope) -> str:
    # any line that does not start with a keyword is unmarked
    # example: print("Hello, World!")
    # example: 5 + 5
    # example: name = "John"
    # example: name = 5
    
    return "yessir"