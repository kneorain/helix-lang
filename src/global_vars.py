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
    
    
from sys import stdout as sys_stdout

from pygments import highlight
from pygments.formatters import TerminalTrueColorFormatter, Terminal256Formatter
from pygments.lexer import RegexLexer, bygroups, include
from pygments.token import Text, Comment, String, Keyword, Name, Operator, Number, Punctuation, Literal, Whitespace
class HelixSyntaxHighlightingLexer(RegexLexer):
    name = 'Helix'
    aliases = ['Helix']
    filenames = ["*.hlx"]
    base_style = "one-dark"
    background_color = "default"
    

    tokens = {
        'root': [
            (r'\bfor\b', Keyword),
            include('comments'),
            include('block-comments'),
            include('keywords'),
            include('constants'),
            include('functions'),
            include('types'),
            include('in_line_replace'),
            include('namespaces'),
            include('punctuation'),
            include('strings'),
            include('variables'),
            include('class_reference'),
            (r'\s+', Whitespace),
        ],
        'comments': [
            (r'~~.*$', Comment.Single)
        ],
        'block-comments': [
            (r'~\*~', Comment.Multiline, 'block-comment'),
            (r'~\*', Comment.Multiline, 'block-comment')
        ],
        'block-comment': [
            (r'[^~]+', Comment.Multiline),
            (r'~\*', Comment.Multiline, '#push'),
            (r'\*~', Comment.Multiline, '#pop'),
            (r'~', Comment.Multiline)
        ],
        'constants': [
            (r'\b\d[\d_]*(\.?)[\d_]*(?:(E|e)([+-]?)([\d_]+))?(f32|f64|i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b', Number),
            (r'\b0x[\da-fA-F_]+(i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b', Number),
            (r'\b0o[0-7_]+(i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b', Number),
            (r'\b0b[01_]+(i128|i16|i32|i64|i8|isize|u128|u16|u32|u64|u8|usize)?\b', Number),
            (r'\b(true|false)\b', Literal),
        ],
        'types': [
            (r'\b(int|float|double|char|string|bool|byte|short|long)\b', Name.Builtin),
            (r'\b(array|list|tuple|map|set)\b', Name.Class),
            (r'\b(void|opt)\b', Name.Class),
            (r'\b(class|struct|enum|union)\s+([A-Z][A-Za-z0-9_]*)(<)([A-Z][A-Za-z0-9_]*)(>)\b', bygroups(Keyword, Name.Class, Punctuation, Name.Class, Punctuation)),
            (r'\b([A-Z][A-Za-z0-9_]*)\b', Name.Class),
        ],
        'keywords': [
            (r'\b(if|else|else\s+if|while|break|continue|return|switch|case|default|stop)\b', Keyword),
            (r'\b(fn|return|yield|async|for|await|lambda|delegate)\b', Keyword),
            (r'\b(class|struct|new|interface|private|protected|final)\b', Keyword),
            (r'\b(impl|abstract)\b', Keyword),
            (r'\b(try|catch|finally|throw)\b', Keyword),
            (r'\b(let|const|var|final)\b', Keyword),
            (r'\b(public|private|protected)\b', Keyword),
            (r'\b(include|import|using|from)\b', Keyword),
            (r'\b(async|await|thread|yield|yield\s+from)\b', Keyword),
            (r'\b(in|override|static|ref|type|->)\b', Keyword),
            (r'(\+|\-|\*|\/|\%|\+\+|\-\-|\+=|\-=|\*=|\/=|\%=|==|!=|>|<|>=|<=|===|!==|&&|\|\||!|&|\||\^|~|<<|>>|\.|::|\?|,|=>|@|\#)', Operator),
        ],
        'functions': [
            (r'\bfn\b', Keyword),
            (r'([A-Za-z_][A-Za-z0-9_]*)\s*(\()', bygroups(Name.Function, Punctuation)),
            (r'\b(self|super)\b', Name.Builtin.Pseudo),
        ],
        'in_line_replace': [
            (r'(([a-z_][A-Za-z0-9_]*!)|([A-Z_][A-Za-z0-9_]*!))', bygroups(Name.Function, Name.Class)),
        ],
        'namespaces': [
            (r'(?<![A-Za-z0-9_])([A-Za-z0-9_]+)(::)', bygroups(Name.Namespace, Punctuation)),
        ],
        'punctuation': [
            (r'(\(|\)|\[|\]|\{|\})', Punctuation),
            (r'(\,)', Punctuation),
            (r'(\.\.\.)', Punctuation),
        ],
        'strings': [
            # Double-quoted strings
            (r'"[^"\\]*(?:\\.[^"\\]*)*"', String),
            # Single-quoted strings
            (r"'[^'\\]*(?:\\.[^'\\]*)*'", String.Char),
        ],

        'variables': [
            (r'(?<![A-Za-z0-9_])([A-Za-z0-9_]+)(?![A-Za-z0-9_])', Name.Variable),
        ],
        'class_reference': [
            # self
            (r'\bself\b', Name.Builtin.Pseudo),
            # super
            (r'\bsuper\b', Name.Builtin.Pseudo)
        ]
    }

lexer = HelixSyntaxHighlightingLexer()
formatter = TerminalTrueColorFormatter(style='one-dark') if sys_stdout.isatty() else Terminal256Formatter(style='one-dark')
def highlight_code(code: str) -> str: return highlight(code, lexer, formatter)

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