from classes.Token import Token_List, Token
from headder import INDENT_CHAR
from core.panic import panic
from os import path as os_path
import re2 as re

def _unmarked(ast_list: Token_List, current_scope, parent_scope, root_scope) -> str:
    # any line that does not start with a keyword is unmarked
    # example: print("Hello, World!")
    # example: 5 + 5
    # example: name = "John"
    # example: name = 5
    
    return "yessir"