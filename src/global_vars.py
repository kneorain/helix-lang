from types import MappingProxyType as map

CACHE: dict = {}

LINE_BREAK:     str = "\x03"
SUB_LINE_BREAK: str = "\x04"

DOUBLE_CHARACTER: list[str] = [
    r"==",
    r"!=",
    r"->",
    r"<-",
    r"<=",
    r">=",
    r"&&",
    r"--",
    r"\:\:",
    r"\|\|",
    r"\+\+",
    r"\+\=",
    r"\-\=",
    r"\*\=",
    r"\/\=",
    r"\&\=",
    r"\|\=",
    r"\^\=",
    r"\%\=",
    r"\*\*",
    r"\.\.\.",
]

KEYWORDS: map[str, map[str, str | bool]] = map({
    # Control Flow
    "if"           : map({"internal_name": "IF"        , "body_required": True , "keyword_type": "control_flow"}),
    "else"         : map({"internal_name": "ELSE"      , "body_required": True , "keyword_type": "control_flow"}),
    "elif"         : map({"internal_name": "ELSE_IF"   , "body_required": True , "keyword_type": "control_flow"}),
    "unless"       : map({"internal_name": "ELSE_IF"   , "body_required": True , "keyword_type": "control_flow"}),

    # Loops
    "continue"     : map({"internal_name": "CONTINUE"  , "body_required": False, "keyword_type": "loop_control"}),
    "stop"         : map({"internal_name": "BREAK"     , "body_required": False, "keyword_type": "loop_control"}),
    "while"        : map({"internal_name": "WHILE"     , "body_required": True , "keyword_type": "loop"}),
    "for"          : map({"internal_name": "FOR"       , "body_required": True , "keyword_type": "loop"}),

    # Switch/Match
    "case"         : map({"internal_name": "CASE"      , "body_required": True , "keyword_type": "case_control"}),
    "default"      : map({"internal_name": "DEFAULT"   , "body_required": True , "keyword_type": "case_control"}),
    "switch"       : map({"internal_name": "SWITCH"    , "body_required": False, "keyword_type": "case_control"}),
    "match"        : map({"internal_name": "MATCH"     , "body_required": False, "keyword_type": "case_control"}),

    # Function
    "fn"           : map({"internal_name": "FUNCTION"  , "body_required": True , "keyword_type": "function_declaration"}),
    "lambda"       : map({"internal_name": "LAMBDA"    , "body_required": True , "keyword_type": "function_declaration"}),
    "thread"       : map({"internal_name": "THREAD"    , "body_required": True , "keyword_type": "function_declaration"}),
    "macro"        : map({"internal_name": "MACRO"     , "body_required": True , "keyword_type": "function_declaration"}),
    "async"        : map({"internal_name": "ASYNC"     , "body_required": True , "keyword_type": "function_modifier"}),
    "return"       : map({"internal_name": "RETURN"    , "body_required": False, "keyword_type": "function_control"}),

    # Class
    "class"        : map({"internal_name": "CLASS"     , "body_required": True , "keyword_type": "class_declaration"}),

    # Struct, Interface, Union, Enum
    "interface"    : map({"internal_name": "INTERFACE" , "body_required": True , "keyword_type": "type_declaration"}),
    "struct"       : map({"internal_name": "STRUCT"    , "body_required": True , "keyword_type": "type_declaration"}),
    "union"        : map({"internal_name": "UNION"     , "body_required": True , "keyword_type": "type_declaration"}),
    "enum"         : map({"internal_name": "ENUM"      , "body_required": True , "keyword_type": "type_declaration"}),

    # Error Handling
    "try"          : map({"internal_name": "TRY"       , "body_required": True , "keyword_type": "error_handling"}),
    "catch"        : map({"internal_name": "CATCH"     , "body_required": True , "keyword_type": "error_handling"}),
    "finally"      : map({"internal_name": "FINALLY"   , "body_required": True , "keyword_type": "error_handling"}),
    "throw"        : map({"internal_name": "THROW"     , "body_required": False, "keyword_type": "error_handling"}),

    # Core
    "break"        : map({"internal_name": "BREAK"     , "body_required": False, "keyword_type": "core"}),
    "delegate"     : map({"internal_name": "DELEGATE"  , "body_required": False, "keyword_type": "core"}),

    # Access Modifiers
    "private"      : map({"internal_name": "PRIVATE"   , "body_required": False, "keyword_type": "access_modifier"}),
    "protected"    : map({"internal_name": "PROTECTED" , "body_required": False, "keyword_type": "access_modifier"}),
    "public"       : map({"internal_name": "PUBLIC"    , "body_required": False, "keyword_type": "access_modifier"}),

    # Class/Type Modifiers
    "final"        : map({"internal_name": "FINAL"     , "body_required": False, "keyword_type": "class_modifier"}),
    "abstract"     : map({"internal_name": "ABSTRACT"  , "body_required": False, "keyword_type": "class_modifier"}),
    "implements"   : map({"internal_name": "IMPLEMENTS", "body_required": False, "keyword_type": "class_modifier"}),

    # Variable Declarations
    "let"          : map({"internal_name": "LET"       , "body_required": False, "keyword_type": "variable_declaration"}),
    "const"        : map({"internal_name": "CONST"     , "body_required": False, "keyword_type": "variable_declaration"}),
    "var"          : map({"internal_name": "VAR"       , "body_required": False, "keyword_type": "variable_declaration"}),

    # Module/Package Management
    "include"      : map({"internal_name": "IMPORT"   , "body_required": False , "keyword_type": "module_import"}),
    "import"       : map({"internal_name": "IMPORT"    , "body_required": False, "keyword_type": "module_import"}),
    "using"        : map({"internal_name": "USING"     , "body_required": False, "keyword_type": "module_import"}),
    "from"         : map({"internal_name": "FROM"      , "body_required": False, "keyword_type": "module_import"}),

    # Asynchronous Programming
    "yield from"   : map({"internal_name": "YIELD_FROM", "body_required": False, "keyword_type": "asynchronous_control"}),
    "yield"        : map({"internal_name": "YIELD"     , "body_required": False, "keyword_type": "asynchronous_control"}),
    "await"        : map({"internal_name": "AWAIT"     , "body_required": False, "keyword_type": "asynchronous_control"}),
})

BODY_REQUIRED_KEYWORDS: map[str, str] = map({
    keyword: KEYWORDS[keyword]["internal_name"]
    for keyword in KEYWORDS.keys()
    if KEYWORDS[keyword]["body_required"]
})

PUNCTUATION = r".,:?()[]{}<>+-*/=|&^%$#~"
COMMENT = r"\~\~.*"
BLOCK_COMMENT = r"\~\*\~"
INLINE_COMMENT = r"\~\*.*\*\~"

class error:
    def __init__(self, line: int, error: str) -> None:
        self.line:  int = line
        self.error: str = error

    def __str__(self) -> str:
        return f"ERROR::{self.line}||{self.error}"