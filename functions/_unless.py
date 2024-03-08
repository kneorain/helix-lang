from classes.Token import Processed_Line, Token, Token_List
import globals
from core.cache_store import cache
from core.config import load_config
from classes.Scope import Scope

INDENT_CHAR = load_config().Formatter["indent_char"]
re = __import__(load_config().Transpiler["regex_module"])

from core.panic import panic

def _unless(ast_list: Token_List, current_scope: Scope, parent_scope: Scope, root_scope: Scope, modifiers=None) -> Processed_Line:
    # unless condition:   ->   if not condition:
    # else if condition:  ->   elif condition:
    output = ""
    if ast_list[0].token == globals.find_keyword("UNLESS"):
        output = f"if not ({ast_list.splice(1, -1).full_line()}):"
    elif ast_list[0].token == globals.find_keyword("IF"):
        output = f"if ({ast_list.splice(1, -1).full_line()}):"
    elif ast_list[0].token == globals.find_keyword("ELSE_IF"):
        output = f"elif ({ast_list.splice(1, -1).full_line()}):"
    elif ast_list[0].token == globals.find_keyword("ELSE") and ast_list[1].token == globals.find_keyword("IF"):
        output = f"elif ({ast_list.splice(2, -1).full_line()}):"
    elif ast_list[0].token == globals.find_keyword("ELSE") and len(ast_list) == 2:
        output = "else:"
    else:
        panic(SyntaxError(f"Unexpected token '{ast_list[0].token}'"), ast_list[0].token, file=ast_list.file, line_no=ast_list.find_line_number(ast_list[0].token))
    
    return Processed_Line(INDENT_CHAR *ast_list.indent_level + output, ast_list)