from src.core.imports import (
    Scope,
    Processed_Line,
    Token,
    Token_List,
)

def _match(ast_list: Token_List, current_scope, parent_scope, root_scope) -> Processed_Line:
    return Processed_Line("JOSH!!!!!!!!!!!!!!!!!!!!!!!!", ast_list)


#if __name__ == "__main__":
#    root_scope = Scope("root", "root", None, 0)
#    root_scope.operator_functions["add"] = "+"
#    root_scope.operator_functions["sub"] = "-"
#    root_scope.operator_functions["greaterThan"] = ">"
#    root_scope.operator_functions["lessThan"] = "<"
#
#    # n > (m + a) < 10 -> greaterThan(lessThan(n, add(m, a)), 10)
#
#    ## Test 1
#    test_line = ["let", "i", ":", "int", "=", "n", ">", "(", "m", "+", "a", ")", "<", "10"]
#    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
#    print("input:", repr(ast_list.full_line()))
#    output = _match(ast_list, None, None, root_scope)
#    print("output (python code):", repr(ast_list)) # should be ["let", "i", ":", "int", "=", "greaterThan(lessThan(n, add(m, a)), 10)"]
#
#    ## Test 2
#    test_line = ["return", "n", ">", "10"]
#    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
#    print("input:", repr(ast_list.full_line()))
#    output = _match(ast_list, None, None, root_scope)
#    print("output (python code):", repr(ast_list)) # should be ["return", "greaterThan(n, 10)"]
#
#    ## Test 3
#    test_line = ["print", "(", "(", "n", ">", "10", ")", "or", "(", "m", "<", "10", ")", ")"]
#    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
#    print("input:", repr(ast_list.full_line()))
#    output = _match(ast_list, None, None, root_scope)
#    print("output (python code):", repr(ast_list)) # should be ["print", "(", or(greaterThan(n, 10), lessThan(m, 10)), ")"]
#
#    ## Test 4
#    test_line = ["print", "(", "i", "++", ")"]
#    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
#    print("input:", repr(ast_list.full_line()))
#    output = _match(ast_list, None, None, root_scope)
#    print("output (python code):", repr(ast_list)) # should be ["print", "(", "increment(i)", ")"]
#
#
#    ## Test 5
#    test_line = ["print", "(", "add", "(", "n", ",", "m", ")", "-", "23", ")"]
#    ast_list = Token_List([Token("None", test_line[index], 1, 0) for index in range(len(test_line))], 0, "test.file")
#    print("input:", repr(ast_list.full_line()))
#    output = _match(ast_list, None, None, root_scope)
#    print("output (python code):", repr(ast_list)) # should be ["print", "(", "subtract(add(n, m), 23)", ")"]