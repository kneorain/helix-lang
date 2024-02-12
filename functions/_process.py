# n > (m + a) < 10 -> gthan(lthan(n, add(m, a)), 10)
from classes.Token import Processed_Line, Token_List, Token
from classes.Scope import Scope
from headder import INDENT_CHAR
from core.panic import panic
from functions._class import _class
from os import path as os_path
import re2 as re

def _match(ast_list: Token_List, current_scope, parent_scope, root_scope, modifiers=None) -> str:
    print(ast_list)
    return "yessir"


if __name__ == "__main__":
    root_scope = Scope("root", "root", None, 0)
    root_scope.operator_functions["add"] = "+"
    root_scope.operator_functions["sub"] = "-"
    root_scope.operator_functions["greaterThan"] = ">"
    root_scope.operator_functions["lessThan"] = "<"
    
    ast_list = 
    
    _match(ast_list, None, None, root_scope)