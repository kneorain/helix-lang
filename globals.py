from sys import stdout as sys_stdout
from threading import Thread
from types import MappingProxyType as map
from typing import Callable

from classes.Token import Processed_Line, Token_List
from classes.WorkerPool import WorkerPool
from functions._class import _class
from functions._for import _for
from functions._functions import function as _function
from functions._include import include as _include
from functions._let import _let
from functions._match import _match
from functions._unless import _unless


def dummy(line: Token_List, current_scope, parent_scope, root_scope) -> str:
    return Processed_Line('    '*line.indent_level + ' '.join([_.token for _ in line]), line)

def _no_change(line: Token_List, *args) -> str:
    return Processed_Line('    '*line.indent_level + ' '.join([_.token for _ in line]), line)
    
CACHE: dict = {}
POOL: WorkerPool = WorkerPool(50)

LINE_BREAK:     str = '\x03'
SUB_LINE_BREAK: str = '\x04'

DOUBLE_CHARACTER: list[str] = [
    r"==="   ,
    r"!=="   ,
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
    r"!\=\=",
]

# All Primitive Types
# int;
# string;
# float;
# map;
# list;
# bool;
# char;
# void;
# tuple;
# array;
# set;
#
# u8;
# u16;
# u32;
# u64;
# u128;
# i8;
# i16;
# i32;
# i64;
# i128;
# f32;
# f64;
# f128;

IGNORE_TYPES_MAP: tuple[str, ...] = (
    "Callable",
)

EARLY_REPLACEMENTS: map[str, str] = map({ # These are replaced as soon as the tokenization is done (before normalization and transpilation)
    "true"         : "True"          ,
    "false"        : "False"         ,
    "null"         : "None"          ,
    "none"         : "None"          ,
    "&&"           : "and"           ,
    "||"           : "or"            ,
    "!"            : "not"           ,
    "==="          : "is"            ,
    "!=="          : "is not"            ,
    "stop"         : "break"         ,
    
    "int"          : "hx_int"      ,
    "string"       : "hx_string"   ,
    "float"        : "hx_float"    ,
    "map"          : "hx_map"      ,
    "list"         : "hx_list"     ,
    "bool"         : "hx_bool"     ,
    "char"         : "hx_char"     ,
    "void"         : "hx_void"     ,
    "tuple"        : "hx_tuple"    ,
    "array"        : "hx_array"    ,
    "set"          : "hx_set"      ,
    "unknown"      : "hx_unknown"  ,
    
    "Int"          : "hx_int"      ,
    "String"       : "hx_string"   ,
    "Float"        : "hx_float"    ,
    "Map"          : "hx_map"      ,
    "List"         : "hx_list"     ,
    "Bool"         : "hx_bool"     ,
    "Char"         : "hx_char"     ,
    "Void"         : "hx_void"     ,
    "Tuple"        : "hx_tuple"    ,
    "Array"        : "hx_array"    ,
    "Set"          : "hx_set"      ,
    "Unknown"      : "hx_unknown"  ,
    
    "u8"           : "hx_u8"       ,
    "u16"          : "hx_u16"      ,
    "u32"          : "hx_u32"      ,
    "u64"          : "hx_u64"      ,
    "u128"         : "hx_u128"     ,
    "i8"           : "hx_i8"       ,
    "i16"          : "hx_i16"      ,
    "i32"          : "hx_i32"      ,
    "i64"          : "hx_i64"      ,
    "i128"         : "hx_i128"     ,
    "f32"          : "hx_f32"      ,
    "f64"          : "hx_f64"      ,
    "f128"         : "hx_f128"     ,
})

KEYWORDS: map[str, map[str, str | bool | Callable[..., str]]] = map({
    # Control Flow
    "if"           : map({"internal_name": "IF"        , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),
    "elif"         : map({"internal_name": "ELSE_IF"   , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),
    "else"         : map({"internal_name": "ELSE"      , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),
    "unless"       : map({"internal_name": "UNLESS"    , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),

    # Loops
    "continue"     : map({"internal_name": "CONTINUE"  , "parser": _no_change   , "scoped": False, "body_required": False, "keyword_type": "loop_control"}),
    ## "stop"         : map({"internal_name": "BREAK"     , "parser": _no_change   , "scoped": False, "body_required": False, "keyword_type": "loop_control"}),
    "while"        : map({"internal_name": "WHILE"     , "parser": _no_change   , "scoped": False, "body_required": True , "keyword_type": "loop"}),
    "for"          : map({"internal_name": "FOR"       , "parser": _for         , "scoped": True, "body_required":  True , "keyword_type": "loop"}),

    # Switch/Match
    "case"         : map({"internal_name": "CASE"      , "parser": dummy        , "scoped": False, "body_required": True , "keyword_type": "case_control"}),
    "default"      : map({"internal_name": "DEFAULT"   , "parser": dummy        , "scoped": False, "body_required": True , "keyword_type": "case_control"}),
    "switch"       : map({"internal_name": "SWITCH"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "case_control"}),
    "match"        : map({"internal_name": "MATCH"     , "parser": _match       , "scoped": False, "body_required": False, "keyword_type": "case_control"}),

    # Function
    "fn"           : map({"internal_name": "FUNCTION"  , "parser": _function    , "scoped": True , "body_required": True , "keyword_type": "function_declaration"}),
    "lambda"       : map({"internal_name": "LAMBDA"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "function_declaration"}),
    "thread"       : map({"internal_name": "THREAD"    , "parser": dummy        , "scoped": True , "body_required": True , "keyword_type": "function_declaration"}),
    "macro"        : map({"internal_name": "MACRO"     , "parser": dummy        , "scoped": True , "body_required": True , "keyword_type": "function_declaration"}),
    "async"        : map({"internal_name": "ASYNC"     , "parser": _function    , "scoped": False, "body_required": False, "keyword_type": "function_modifier"}),
    "return"       : map({"internal_name": "RETURN"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "function_control"}),

    # Class
    "class"        : map({"internal_name": "CLASS"     , "parser": _class       , "scoped": True , "body_required": True , "keyword_type": "class_declaration"}),
    "interface"    : map({"internal_name": "INTERFACE" , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
    "struct"       : map({"internal_name": "STRUCT"    , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
    "union"        : map({"internal_name": "UNION"     , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
    "enum"         : map({"internal_name": "ENUM"      , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
    "abstract"     : map({"internal_name": "ABSTRACT"  , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "class_modifier"}),
    ## "impl"         : map({"internal_name": "EXTEND"    , "parser": dummy        , "scoped": True , "body_required": True , "keyword_type": "class_declaration"}),

    # Error Handling
    "try"          : map({"internal_name": "TRY"       , "parser": dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
    "catch"        : map({"internal_name": "CATCH"     , "parser": dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
    "finally"      : map({"internal_name": "FINALLY"   , "parser": dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
    "throw"        : map({"internal_name": "THROW"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "error_handling"}),

    # Core
    "break"        : map({"internal_name": "BREAK"     , "parser": _no_change   , "scoped": False, "body_required": False, "keyword_type": "core"}),
    "delegate"     : map({"internal_name": "DELEGATE"  , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "core"}),

    # Access Modifiers
    "private"      : map({"internal_name": "PRIVATE"   , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
    "protected"    : map({"internal_name": "PROTECTED" , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
    "public"       : map({"internal_name": "PUBLIC"    , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
    "final"        : map({"internal_name": "FINAL"     , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
    "static"       : map({"internal_name": "STATIC"    , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
    "unsafe"       : map({"internal_name": "UNSAFE"    , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),

    # Class/Type Modifiers
    ## "implements"   : map({"internal_name": "IMPLEMENTS", "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "class_modifier"}),

    # Variable Declarations
    "let"          : map({"internal_name": "LET"       , "parser": _let         , "scoped": False, "body_required": False, "keyword_type": "variable_declaration"}),
    "const"        : map({"internal_name": "CONST"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "variable_declaration"}),
    "var"          : map({"internal_name": "VAR"       , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "variable_declaration"}),
    
    # Module/Package Management
    "include"      : map({"internal_name": "IMPORT"    , "parser": _include     , "scoped": False, "body_required": False, "keyword_type": "module_import"}),
    "import"       : map({"internal_name": "IMPORT"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "module_import"}),
    "using"        : map({"internal_name": "USING"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "module_import"}),
    "from"         : map({"internal_name": "FROM"      , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "module_import"}),

    # Asynchronous Programming
    "yield from"   : map({"internal_name": "YIELD_FROM", "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "asynchronous_control"}),
    "yield"        : map({"internal_name": "YIELD"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "asynchronous_control"}),
    "await"        : map({"internal_name": "AWAIT"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "asynchronous_control"}),
})
BODY_REQUIRED_KEYWORDS: map[str, str] = map({
    keyword: KEYWORDS[keyword]["internal_name"]
    for keyword in KEYWORDS.keys()
    if KEYWORDS[keyword]["body_required"]
})
NAMESPACED_KEYWORD: map[str, str] = map({
    keyword: KEYWORDS[keyword]["internal_name"]
    for keyword in KEYWORDS.keys()
    if KEYWORDS[keyword]["scoped"]
})
PUNCTUATION = r".,:?()[]{}<>+-*/=|&^%$#~"
COMMENT = r"\~\~.*"
BLOCK_COMMENT = r"\~\*\~"
INLINE_COMMENT = r"\~\*.*\*\~"
STRING = r"\".*\""
CHAR = r"'.*'"
INDENT_CHAR = "    "

from core.cache_store import file_cache


@file_cache
def find_keyword(internal_name: str) -> str: return [keyword for keyword in KEYWORDS.keys() if KEYWORDS[keyword]["internal_name"] == internal_name][0]

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