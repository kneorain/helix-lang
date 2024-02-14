from types import MappingProxyType as map
from sys import stdout as sys_stdout
from threading import Thread
from typing import Callable
from classes.WorkerPool import WorkerPool
from functions._include import include as _include
from functions._functions import function as _function
from functions._class import _class
from functions._match import _match
from classes.Token import Token_List, Processed_Line

def dummy(line: Token_List, current_scope, parent_scope, root_scope) -> str:
    return Processed_Line('    '*line.indent_level + ' '.join([_.token for _ in line]), line)
    
CACHE: dict = {}
POOL: WorkerPool = WorkerPool(50)

LINE_BREAK:     str = '\x03'
SUB_LINE_BREAK: str = '\x04'

DOUBLE_CHARACTER: list[str] = [
    r"=="    ,
    r"!="    ,
    r"->"    ,
    r"<-"    ,
    r"<="    ,
    r">="    ,
    r"&&"    ,
    r"--"    ,
    r"\:\:"  ,
    r"\|\|"  ,
    r"\+\+"  ,
    r"\+\="  ,
    r"\-\="  ,
    r"\*\="  ,
    r"\/\="  ,
    r"\&\="  ,
    r"\|\="  ,
    r"\^\="  ,
    r"\%\="  ,
    r"\*\*"  ,
    r"\.\.\.",
    r"=\=\=",
    r"!\=\=",
]

KEYWORDS: map[str, map[str, str | bool | Callable[..., str]]] = map({
    # Control Flow
    "if"           : map({"internal_name": "IF"        , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "control_flow"}),
    "else"         : map({"internal_name": "ELSE"      , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "control_flow"}),
    "elif"         : map({"internal_name": "ELSE_IF"   , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "control_flow"}),
    "unless"       : map({"internal_name": "ELSE_IF"   , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "control_flow"}),

    # Loops
    "continue"     : map({"internal_name": "CONTINUE"  , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "loop_control"}),
    "stop"         : map({"internal_name": "BREAK"     , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "loop_control"}),
    "while"        : map({"internal_name": "WHILE"     , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "loop"}),
    "for"          : map({"internal_name": "FOR"       , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "loop"}),

    # Switch/Match
    "case"         : map({"internal_name": "CASE"      , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "case_control"}),
    "default"      : map({"internal_name": "DEFAULT"   , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "case_control"}),
    "switch"       : map({"internal_name": "SWITCH"    , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "case_control"}),
    "match"        : map({"internal_name": "MATCH"     , "parser": _match       , "namespace": False, "body_required": False, "keyword_type": "case_control"}),

    # Function
    "fn"           : map({"internal_name": "FUNCTION"  , "parser": _function    , "namespace": True , "body_required": True , "keyword_type": "function_declaration"}),
    "lambda"       : map({"internal_name": "LAMBDA"    , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "function_declaration"}),
    "thread"       : map({"internal_name": "THREAD"    , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "function_declaration"}),
    "macro"        : map({"internal_name": "MACRO"     , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "function_declaration"}),
    "async"        : map({"internal_name": "ASYNC"     , "parser": _function    , "namespace": False, "body_required": False, "keyword_type": "function_modifier"}),
    "return"       : map({"internal_name": "RETURN"    , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "function_control"}),

    # Class
    "class"        : map({"internal_name": "CLASS"     , "parser": _class       , "namespace": True , "body_required": True , "keyword_type": "class_declaration"}),
    "impl"         : map({"internal_name": "EXTEND"    , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "class_declaration"}),

    # Struct, Interface, Union, Enum
    "interface"    : map({"internal_name": "INTERFACE" , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "type_declaration"}),
    "struct"       : map({"internal_name": "STRUCT"    , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "type_declaration"}),
    "union"        : map({"internal_name": "UNION"     , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "type_declaration"}),
    "enum"         : map({"internal_name": "ENUM"      , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "type_declaration"}),

    # Error Handling
    "try"          : map({"internal_name": "TRY"       , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "error_handling"}),
    "catch"        : map({"internal_name": "CATCH"     , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "error_handling"}),
    "finally"      : map({"internal_name": "FINALLY"   , "parser": dummy        , "namespace": False, "body_required": True , "keyword_type": "error_handling"}),
    "throw"        : map({"internal_name": "THROW"     , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "error_handling"}),

    # Core
    "break"        : map({"internal_name": "BREAK"     , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "core"}),
    "delegate"     : map({"internal_name": "DELEGATE"  , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "core"}),

    # Access Modifiers
    "private"      : map({"internal_name": "PRIVATE"   , "parser": _function        , "namespace": False, "body_required": False, "keyword_type": "access_modifier"}),
    "protected"    : map({"internal_name": "PROTECTED" , "parser": _function        , "namespace": False, "body_required": False, "keyword_type": "access_modifier"}),
    "public"       : map({"internal_name": "PUBLIC"    , "parser": _function        , "namespace": False, "body_required": False, "keyword_type": "access_modifier"}),
    "final"        : map({"internal_name": "FINAL"     , "parser": _function        , "namespace": False, "body_required": False, "keyword_type": "access_modifier"}),
    "unsafe"       : map({"internal_name": "UNSAFE"     , "parser": _function        , "namespace": False, "body_required": False, "keyword_type": "access_modifier"}),
    "static"       : map({"internal_name": "STATIC"     , "parser": _function        , "namespace": False, "body_required": False, "keyword_type": "access_modifier"}),

    # Class/Type Modifiers
    "abstract"     : map({"internal_name": "ABSTRACT"  , "parser": dummy        , "namespace": True , "body_required": True , "keyword_type": "class_modifier"}),
    "implements"   : map({"internal_name": "IMPLEMENTS", "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "class_modifier"}),

    # Variable Declarations
    "let"          : map({"internal_name": "LET"       , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "variable_declaration"}),
    "const"        : map({"internal_name": "CONST"     , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "variable_declaration"}),
    "var"          : map({"internal_name": "VAR"       , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "variable_declaration"}),

    # Module/Package Management
    "include"      : map({"internal_name": "IMPORT"    , "parser": _include     , "namespace": False, "body_required": False, "keyword_type": "module_import"}),
    "import"       : map({"internal_name": "IMPORT"    , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "module_import"}),
    "using"        : map({"internal_name": "USING"     , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "module_import"}),
    "from"         : map({"internal_name": "FROM"      , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "module_import"}),

    # Asynchronous Programming
    "yield from"   : map({"internal_name": "YIELD_FROM", "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "asynchronous_control"}),
    "yield"        : map({"internal_name": "YIELD"     , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "asynchronous_control"}),
    "await"        : map({"internal_name": "AWAIT"     , "parser": dummy        , "namespace": False, "body_required": False, "keyword_type": "asynchronous_control"}),
})
BODY_REQUIRED_KEYWORDS: map[str, str] = map({
    keyword: KEYWORDS[keyword]["internal_name"]
    for keyword in KEYWORDS.keys()
    if KEYWORDS[keyword]["body_required"]
})
NAMESPACED_KEYWORD: map[str, str] = map({
    keyword: KEYWORDS[keyword]["internal_name"]
    for keyword in KEYWORDS.keys()
    if KEYWORDS[keyword]["namespace"]
})
PUNCTUATION = r".,:?()[]{}<>+-*/=|&^%$#~"
COMMENT = r"\~\~.*"
BLOCK_COMMENT = r"\~\*\~"
INLINE_COMMENT = r"\~\*.*\*\~"
STRING = r"\".*\""
CHAR = r"'.*'"
INDENT_CHAR = "    "


def ASYNC(func):
    def wrapper(*args, **kwargs):
        Thread(target=func, args=args, kwargs=kwargs).start()
    return wrapper



















#print(highlight_code("""
#fn main() {
#    n: int?; ~~ ? initializes to null instead of 0
#    n: opt[int]; ~~ opt is a generic type that can be used to initialize to null
#    n = input("Enter a positive integer ");
#    print("Factorial of " + n + " = " + factorial(n));
#    fn factorial(n: int) -> int {
#        if (n == 0) {
#            return 1;
#        } else {
#            return n * factorial(n - 1);
#        }
#    }
#
#    for (var i = 0; i < 10; i++) {
#        print(i);
#    }
#}
#"""))
#exit()