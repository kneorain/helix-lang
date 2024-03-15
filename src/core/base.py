from __future__ import annotations
from src.core.imports import (
    re,
    sys,
    map,
    enum,
    Thread,
    Callable,
    Iterable,
    Optional,
    Token_List,
    WorkerPool,
    Processed_Line,
    NoReturn,

    _unless,
    _for,
    _match,
    _function,
    _class,
    _let,
    _include,
    _unmarked,
    file_cache,
    
    panic,
)



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

def dummy(
    line: Token_List,
    current_scope,
    parent_scope,
    root_scope,
) -> Processed_Line:
    return Processed_Line(
        "    " * line.indent_level
        + " ".join([str(_.token) for _ in line]),
        line,
    )


def _no_change(line: Token_List, *args) -> Processed_Line:
    return Processed_Line(
        "    " * line.indent_level
        + " ".join([str(_.token) for _ in line]),
        line,
    )



CACHE: dict[str, tuple[Token_List, ...]] = {}
POOL: WorkerPool = WorkerPool(50)
USE_POOL: bool = True

LINE_BREAK: str = "\x03"
SUB_LINE_BREAK: str = "\x04"
PUNCTUATION = r".,:?()[]{}<>+-*/=|&^%$#~"
COMMENT = r"\~\~.*"
BLOCK_COMMENT = r"\~\*\~"
INLINE_COMMENT = r"\~\*.*\*\~"
STRING = r"\".*\""
CHAR = r"'.*'"
INDENT_CHAR = "    "


"""
07/14/2016     08/02/2016
07/22/2022     08/02/2022
08/11/2023     12/19/2023

Al Mankhool, Bur Dubai
305, Al Falasi Residences, 317 - 11 B St
"""

FAT_CHARACTER = [
    # CHARACTERS MUST BE > 2
    r"\=\=\=",  # ===
    r"\!\=\=",  # !==
    r"\.\.\.",  # ...
    r"\r\/\/",  # r//
    r"\r\*\*",  # r**
    r"\r\<\<",  # r<<
    r"\r\>\>",  # r>>
    r"\/\/\=",  # //=
    r"\*\*\=",  # **=
    r"\<\<\=",  # <<=
    r"\>\>\=",  # >>=
    r"\=\=",    # ==
    r"\!\=",    # !=
    r"\<\=",    # <=
    r"\>\=",    # >=
    r"\/\/",    # //
    r"\*\*",    # **
    r"\<\<",    # <<
    r"\>\>",    # >>
    r"\r\+",    # r+
    r"\r\-",    # r-
    r"\r\*",    # r*
    r"\r\/",    # r/
    r"\r\%",    # r%
    r"\r\&",    # r&
    r"\r\|",    # r|
    r"\r\^",    # r^
    r"\+\=",    # +=
    r"\-\=",    # -=
    r"\*\=",    # *=
    r"\/\=",    # /=
    r"\%\=",    # %=
    r"\&\=",    # &=
    r"\|\=",    # |=
    r"\^\=",    # ^=
    r"\=\=",    # ==
    r"\=\>",    # =>
    r"\@\=",    # @=
    r"\-\>",    # ->
    r"\<\-",    # <-
    r"\<\=",    # <=
    r"\>\=",    # >=
    r"\&\&",    # &&
    r"\-\-",    # --
    r"\:\:",    # ::
    r"\|\|",    # ||
    r"\+\+",    # ++
    r"\_\_",    # __
    r"\?\?",    # ??
    r"\?\:",    # ?:
    r"\?\=",    # ?=
]

@enum.unique
class ERROR_CODES(enum.Enum):
    # Command-Line Interface Errors
    CLI_ARGUMENT_INVALID = (
        "HEX-001",
        "Invalid command-line argument: {argument}",
        ValueError,
    )
    CLI_FILE_NOT_FOUND = (
        "HEX-002",
        "Input file not found: {filename}",
        FileNotFoundError,
    )
    CLI_OPTION_UNSUPPORTED = (
        "HEX-003",
        "Unsupported command-line option: {option}",
        ValueError,
    )

    # Syntax Errors
    SYNTAX_UNEXPECTED_TOKEN = (
        "HEX-100",
        "Unexpected token in source code: {token}",
        SyntaxError,
    )
    SYNTAX_INVALID_SYNTAX = (
        "HEX-101",
        "Syntax error: {location}",
        SyntaxError,
    )
    SYNTAX_MISSING_SEMICOLON = (
        "HEX-102",
        "Missing semicolon at end of statement",
        SyntaxError,
    )
    SYNTAX_UNBALANCED_PARENTHESIS = (
        "HEX-103",
        "Unbalanced parenthesis",
        SyntaxError,
    )
    SYNTAX_INVALID_LITERAL = (
        "HEX-104",
        "Invalid literal: {literal}",
        ValueError,
    )
    SYNTAX_UNSUPPORTED_SYNTAX = (
        "HEX-105",
        "Unsupported syntax in Helix: {syntax}",
        SyntaxError,
    )
    SYNTAX_MISSING_EXCEPTED_TOKEN = (
        "HEX-106",
        "Missing expected token: {token}",
        SyntaxError,
    )
    
    # Type and Declaration Errors
    TYPE_INVALID_CAST = (
        "HEX-200",
        "Invalid type cast: {details}",
        TypeError,
    )
    
    TYPE_UNDECLARED_VARIABLE = (
        "HEX-201",
        "Use of undeclared variable: {variable}",
        NameError,
    )
    TYPE_MISMATCH = (
        "HEX-202",
        "Type mismatch in expression: {expression}",
        TypeError,
    )
    TYPE_REDECLARATION = (
        "HEX-203",
        "Redeclaration of a variable or function: {identifier}",
        SyntaxError,
    )
    TYPE_UNDECLARED = (
        "HEX-204",
        "Type for {identifier} is undeclared",
        TypeError,
    )
    TYPE_INVALID_TYPE_IN_CONTEXT = (
        "HEX-205",
        "Invalid type used in this location: {type}",
        TypeError,
    )
    
    # Semantic Errors
    SEMANTIC_UNRESOLVED_REFERENCE = (
        "HEX-300",
        "Unresolved reference: {reference}",
        NameError,
    )
    SEMANTIC_ARGUMENT_MISMATCH = (
        "HEX-301",
        "Function argument mismatch in {function}",
        TypeError,
    )
    SEMANTIC_INFINITE_LOOP_DETECTED = (
        "HEX-302",
        "Potential infinite loop detected",
        RuntimeError,
    )
    SEMANTIC_INVALID_OPERATION = (
        "HEX-303",
        "Invalid operation: {operation}",
        ValueError,
    )

    # Linking and Dependency Errors
    LINKING_FAILED = (
        "HEX-400",
        "Linking failed: {details}",
        ImportError,
    )
    DEPENDENCY_NOT_FOUND = (
        "HEX-401",
        "Dependency not found: {dependency}",
        ImportError,
    )
    DEPENDENCY_CONFLICT = (
        "HEX-402",
        "Dependency version conflict: {details}",
        ImportError,
    )

    # File and I/O Errors
    FILE_READ_ERROR = (
        "HEX-500",
        "Error reading file: {filename}",
        IOError,
    )
    FILE_WRITE_ERROR = (
        "HEX-501",
        "Error writing file: {filename}",
        IOError,
    )
    FILE_FORMAT_UNSUPPORTED = (
        "HEX-502",
        "Unsupported file format: {format}",
        ValueError,
    )
    IO_PERMISSION_DENIED = (
        "HEX-503",
        "Permission denied for file operation: {filename}",
        PermissionError,
    )

    # Resource and Memory Errors
    RESOURCE_LIMIT_EXCEEDED = (
        "HEX-600",
        "Resource limit exceeded: {resource}",
        MemoryError,
    )
    MEMORY_ALLOCATION_ERROR = (
        "HEX-601",
        "Memory allocation error",
        MemoryError,
    )
    RESOURCE_LEAK_DETECTED = (
        "HEX-602",
        "Resource leak detected: {resource}",
        ResourceWarning,
    )

    # Environment and System Errors
    SYSTEM_ERROR = (
        "HEX-700",
        "System error encountered: {details}",
        SystemError,
    )
    ENVIRONMENT_VARIABLE_NOT_FOUND = (
        "HEX-701",
        "Environment variable not found: {variable}",
        EnvironmentError,
    )
    UNSUPPORTED_PLATFORM = (
        "HEX-702",
        "Unsupported operating system or platform: {platform}",
        OSError,
    )

    # Miscellaneous Errors
    INTERNAL_COMPILER_ERROR = (
        "HEX-800",
        "Internal compiler error: {details}",
        RuntimeError,
    )
    FEATURE_NOT_IMPLEMENTED = (
        "HEX-801",
        "Feature not yet implemented: {feature}",
        NotImplementedError,
    )
    UNEXPECTED_ERROR = (
        "HEX-802",
        "Unexpected error occurred: {details}",
        RuntimeError,
    )

    # Specific Errors
    OPERATOR_OVERLOADING_OUTSIDE_CLASS = (
        "HEX-900",
        "Operator cannot be overloaded outside a class",
        SyntaxError,
    )
    FUNCTION_STATIC_OUTSIDE_CLASS = (
        "HEX-901",
        "Static function cannot be declared outside a class",
        SyntaxError,
    )
    FUNCTION_FINAL_OUTSIDE_CLASS = (
        "HEX-902",
        "Final function cannot be declared outside a class",
        SyntaxError,
    )
    FUNCTION_INVALID_MODIFIERS = (
        "HEX-903",
        "Invalid modifiers for function: {modifiers}",
        SyntaxError,
    )
    def __init__(self, code: str, template: str, py_exception: type[BaseException]) -> None:
        self.code = code
        self.template = template
        self.py_exception = py_exception
        self.formatted: bool = False

    def format(self, *args, **kwargs) -> ERROR_CODES:
        """Format the error message with provided arguments."""
        if args:
            pattern = r"\{([^{}]*)\}"
            vars = re.findall(pattern, self.template)
            raise ValueError(
                "\u001b[31m\n"
                f"Error message '{self.template}' has {len(vars)} variables, but {len(args)} were provided.\n"
                "did i mean\n\t" + ", ".join([f"{var}={arg}" for var, arg in zip(vars, args)]) +
                "\u001b[0m"
            )

        _prefix = kwargs.pop("_prefix", False)
        if not _prefix:
            kwargs = {key: ('\"' + str(value) + '\"') if value is not None else '' for key, value in kwargs.items()}
        else:
            # add the prefix to the first key
            kwargs[list(kwargs.keys())[0]] = _prefix + kwargs[list(kwargs.keys())[0]]
            kwargs = {key: (str(value)) if value is not None else '' for key, value in kwargs.items()}
            
        try:
            formatted_message = self.template.format(**kwargs)
        except KeyError:
            pattern = r"\{([^{}]*)\}"
            vars = re.findall(pattern, self.template)
            if len(vars) == len(kwargs):
                raise ValueError(
                    "\u001b[31m\n"
                    f"Error message '{self.template}' has {len(vars)} variables, but {len(kwargs)} were provided.\n"
                    "did i mean\n\t" + ", ".join([f"{var}={arg}" for var, arg in zip(vars, kwargs.values())]) +
                    "\u001b[0m"
                )
            raise ValueError(
                "\u001b[31m\n"
                f"Error message '{self.template}' has {len(vars)} variables, but {len(kwargs)} were provided.\n"
                "did i mean\n\t" + ", ".join([f"{var}={arg}" for var, arg in zip(vars, kwargs.values())]) +
                "\u001b[0m"
            )
        
        self.template = formatted_message
        self.formatted = True
        return self

    def panic(self, *args, **kwargs) -> NoReturn:
        if not self.formatted and ('{' in self.template and '}' in self.template):
            raise ValueError(
                "Error message not formatted before panic",
                "requirements: " + ", ".join(re.findall(r"\{([^{}]*)\}", self.template))
            )
        
        panic(self.py_exception(self.template), *args, **kwargs, _code = self.code)
        sys.exit(1)
        
    
IGNORE_TYPES_MAP: tuple[str, ...] = ("Callable",)

PRIMITIVES_MAP: map[str, tuple[str, str]] = map(
    {
        # helix type : (python type, helix ir type)
        "int": ("int", "hx_int"),
        "string": ("str", "hx_string"),
        "float": ("float", "hx_float"),
        "double": ("double", "hx_double"),
        "map": ("dict", "hx_map"),
        "list": ("list", "hx_list"),
        "bool": ("bool", "hx_bool"),
        "char": ("str", "hx_char"),
        "void": ("NoneType", "hx_void"),
        "tuple": ("tuple", "hx_tuple"),
        "array": ("array", "hx_array"),
        "set": ("set", "hx_set"),
        "unknown": ("Any", "hx_unknown"),
        "Int": ("int", "hx_int"),
        "String": ("str", "hx_string"),
        "Float": ("float", "hx_float"),
        "Double": ("double", "hx_double"),
        "Map": ("dict", "hx_map"),
        "List": ("list", "hx_list"),
        "Bool": ("bool", "hx_bool"),
        "Char": ("str", "hx_char"),
        "Void": ("NoneType", "hx_void"),
        "Tuple": ("tuple", "hx_tuple"),
        "Array": ("array", "hx_array"),
        "Set": ("set", "hx_set"),
        "Unknown": ("Any", "hx_unknown"),
    }
)

RESERVED_KEYWORDS: tuple[str, ...] = (
    "__dict__",
    "__setattr__",
    "__init__",
)

EARLY_REPLACEMENTS: map[str, str] = map(
    {  # These are replaced as soon as the tokenization is done (before normalization and transpilation)
        "...": "None",
        "true": "True",
        "false": "False",
        "null": "None",
        "none": "None",
        "await": "_await",
        "&&": "and",
        "||": "or",
        "!": "not",
        "===": "is",
        "!==": "is not",
        "stop": "break",
        "::": ".",
        "new": "__init__",
        "delete": "__del__",
        "enter": "__enter__",
        "exit": "__exit__",
        "u8": "hx_u8",
        "u16": "hx_u16",
        "u32": "hx_u32",
        "u64": "hx_u64",
        "u128": "hx_u128",
        "i8": "hx_i8",
        "i16": "hx_i16",
        "i32": "hx_i32",
        "i64": "hx_i64",
        "i128": "hx_i128",
        "f32": "hx_f32",
        "f64": "hx_f64",
        "f128": "hx_f128",
    }
)

KEYWORDS: map[str, map[str, str | bool | Callable[..., Processed_Line]]] = map({
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
    "try"          : map({"internal_name": "TRY"       , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
    "catch"        : map({"internal_name": "CATCH"     , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
    "except"        : map({"internal_name": "EXCEPT"   , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
    "finally"      : map({"internal_name": "FINALLY"   , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
    "throw"        : map({"internal_name": "THROW"     , "parser":  dummy        , "scoped": False, "body_required": False, "keyword_type": "error_handling"}),

    # Core
    "break"        : map({"internal_name": "BREAK"     , "parser":  _no_change   , "scoped": False, "body_required": False, "keyword_type": "core"}),
    "delegate"     : map({"internal_name": "DELEGATE"  , "parser":  dummy        , "scoped": False, "body_required": False, "keyword_type": "core"}),
    "with"         : map({"internal_name": "WITH"      , "parser":  _no_change   , "scoped": False, "body_required": True , "keyword_type": "core"}),
    
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

BODY_REQUIRED_KEYWORDS: map[str, str] = map(
    {
        keyword: str(KEYWORDS[keyword]["internal_name"])
        for keyword in KEYWORDS.keys()
        if KEYWORDS[keyword]["body_required"]
    }
)

NAMESPACED_KEYWORD: map[str, str] = map(
    {
        keyword: str(KEYWORDS[keyword]["internal_name"])
        for keyword in KEYWORDS.keys()
        if KEYWORDS[keyword]["scoped"]
    }
)


from src.core.utils import (
    multi_split,
    replace_primitive,
    find_keyword,
    ASYNC
)



# print(highlight_code("""
# fn main() {
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
# }
# """))
# exit()
