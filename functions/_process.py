# move the dir one up
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from classes.Scope import Scope
from classes.Token import Processed_Line, Token, Token_List
from core.config import load_config

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from core.panic import panic
from functions._class import _class


def _match(ast_list: Token_List, current_scope, parent_scope, root_scope) -> Token_List:
    return Processed_Line("JOSH!!!!!!!!!!!!!!!!!!!!!!!!", ast_list)


if __name__ == "__main__":
    root_scope = Scope("root", "root", None, 0)
    root_scope.operator_functions["add"] = "+"
    root_scope.operator_functions["sub"] = "-"
    root_scope.operator_functions["greaterThan"] = ">"
    root_scope.operator_functions["lessThan"] = "<"
    
    # n > (m + a) < 10 -> greaterThan(lessThan(n, add(m, a)), 10)
    
    ## Test 1
    test_line = ["let", "i", ":", "int", "=", "n", ">", "(", "m", "+", "a", ")", "<", "10"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(ast_list)) # should be ["let", "i", ":", "int", "=", "greaterThan(lessThan(n, add(m, a)), 10)"]
    
    ## Test 2
    test_line = ["return", "n", ">", "10"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(ast_list)) # should be ["return", "greaterThan(n, 10)"]
    
    ## Test 3
    test_line = ["print", "(", "(", "n", ">", "10", ")", "or", "(", "m", "<", "10", ")", ")"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(ast_list)) # should be ["print", "(", or(greaterThan(n, 10), lessThan(m, 10)), ")"]
    
    ## Test 4
    test_line = ["print", "(", "i", "++", ")"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(ast_list)) # should be ["print", "(", "increment(i)", ")"]
    
    
    ## Test 5
    test_line = ["print", "(", "add", "(", "n", ",", "m", ")", "-", "23", ")"]
    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
    print("input:", repr(ast_list.full_line()))
    output = _match(ast_list, None, None, root_scope)
    print("output (python code):", repr(ast_list)) # should be ["print", "(", "subtract(add(n, m), 23)", ")"]