# move the dir one up
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from classes.Token import Processed_Line, Token_List, Token
from classes.Scope import Scope
from headder import INDENT_CHAR
from core.panic import panic
from functions._class import _class
from os import path as os_path
import re2 as re

def _match(ast_list: Token_List, current_scope, parent_scope, root_scope) -> str:
    return "JOSH!!!!!!!!!!!!!!!!!!!!!!!!"


if __name__ == "__main__":
    root_scope = Scope("root", "root", None, 0)
    root_scope.operator_functions["add"] = "+"
    root_scope.operator_functions["sub"] = "-"
    root_scope.operator_functions["greaterThan"] = ">"
    root_scope.operator_functions["lessThan"] = "<"
    
    # n > (m + a) < 10 -> greaterThan(lessThan(n, add(m, a)), 10)
    
    test_line = ["n", ">", "(", "m", "+", "a", ")", "<", "10"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(output)) # should be "greaterThan(n, lessThan(add(m, a), 10))"
    


    test_line = ["n", ">", "m", "+", "a", "<", "10"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(output)) # should be "greaterThan(n, lessThan(add(m, a), 10))"
    


    test_line = ["n", ">", "a", "<", "10"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(output)) # should be "greaterThan(n, lessThan(a, 10))"
    
    