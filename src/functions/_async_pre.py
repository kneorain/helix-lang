from src.classes._ast import AST_LIST, AST
from src.headder import INDENT_CHAR
from src.core.panic import panic
from os import path as os_path
import re2 as re

def async_prefixed(ast_list: AST_LIST, current_scope, parent_scope, root_scope) -> str:
    print("SHJSJSJ")
    panic(
        SyntaxError(f"<Hex(02.E3)>: prefixing a function with {root_scope.get_keyword("ASYNC")}"
                  + f" or any modifier is not valid, use modifiers after the {root_scope.get_keyword("FUNCTION")} keyword instead"
        ),
        root_scope.get_keyword("ASYNC"),
        file=ast_list.file,
        line_no=ast_list.find_line_number(root_scope.get_keyword("ASYNC"))
    )