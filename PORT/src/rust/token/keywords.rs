/*
"if"           : map({"internal_name": "IF"        , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),
"elif"         : map({"internal_name": "ELSE_IF"   , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),
"else"         : map({"internal_name": "ELSE"      , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),
"unless"       : map({"internal_name": "UNLESS"    , "parser": _unless      , "scoped": False, "body_required": True , "keyword_type": "control_flow"}),
"continue"     : map({"internal_name": "CONTINUE"  , "parser": _no_change   , "scoped": False, "body_required": False, "keyword_type": "loop_control"}),
"while"        : map({"internal_name": "WHILE"     , "parser": _no_change   , "scoped": False, "body_required": True , "keyword_type": "loop"}),
"for"          : map({"internal_name": "FOR"       , "parser": _for         , "scoped": True, "body_required":  True , "keyword_type": "loop"}),
"case"         : map({"internal_name": "CASE"      , "parser": dummy        , "scoped": False, "body_required": True , "keyword_type": "case_control"}),
"default"      : map({"internal_name": "DEFAULT"   , "parser": dummy        , "scoped": False, "body_required": True , "keyword_type": "case_control"}),
"switch"       : map({"internal_name": "SWITCH"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "case_control"}),
"match"        : map({"internal_name": "MATCH"     , "parser": dummy       , "scoped": False, "body_required": False, "keyword_type": "case_control"}),
"fn"           : map({"internal_name": "FUNCTION"  , "parser": _function    , "scoped": True , "body_required": True , "keyword_type": "function_declaration"}),
"lambda"       : map({"internal_name": "LAMBDA"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "function_declaration"}),
"thread"       : map({"internal_name": "THREAD"    , "parser": dummy        , "scoped": True , "body_required": True , "keyword_type": "function_declaration"}),
"macro"        : map({"internal_name": "MACRO"     , "parser": dummy        , "scoped": True , "body_required": True , "keyword_type": "function_declaration"}),
"async"        : map({"internal_name": "ASYNC"     , "parser": _function    , "scoped": False, "body_required": False, "keyword_type": "function_modifier"}),
"return"       : map({"internal_name": "RETURN"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "function_control"}),
"class"        : map({"internal_name": "CLASS"     , "parser": _class       , "scoped": True , "body_required": True , "keyword_type": "class_declaration"}),
"interface"    : map({"internal_name": "INTERFACE" , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
"struct"       : map({"internal_name": "STRUCT"    , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
"union"        : map({"internal_name": "UNION"     , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
"enum"         : map({"internal_name": "ENUM"      , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "type_declaration"}),
"abstract"     : map({"internal_name": "ABSTRACT"  , "parser": _class        , "scoped": True , "body_required": True , "keyword_type": "class_modifier"}),
"try"          : map({"internal_name": "TRY"       , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
"catch"        : map({"internal_name": "CATCH"     , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
"except"        : map({"internal_name": "EXCEPT"   , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
"finally"      : map({"internal_name": "FINALLY"   , "parser":  dummy        , "scoped": False, "body_required": True , "keyword_type": "error_handling"}),
"throw"        : map({"internal_name": "THROW"     , "parser":  dummy        , "scoped": False, "body_required": False, "keyword_type": "error_handling"}),
"break"        : map({"internal_name": "BREAK"     , "parser":  _no_change   , "scoped": False, "body_required": False, "keyword_type": "core"}),
"delegate"     : map({"internal_name": "DELEGATE"  , "parser":  dummy        , "scoped": False, "body_required": False, "keyword_type": "core"}),
"with"         : map({"internal_name": "WITH"      , "parser":  _no_change   , "scoped": False, "body_required": True , "keyword_type": "core"}),
"private"      : map({"internal_name": "PRIVATE"   , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
"protected"    : map({"internal_name": "PROTECTED" , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
"public"       : map({"internal_name": "PUBLIC"    , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
"final"        : map({"internal_name": "FINAL"     , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
"static"       : map({"internal_name": "STATIC"    , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
"unsafe"       : map({"internal_name": "UNSAFE"    , "parser":  _function   , "scoped": False, "body_required": False, "keyword_type": "access_modifier"}),
"let"          : map({"internal_name": "LET"       , "parser": _let         , "scoped": False, "body_required": False, "keyword_type": "variable_declaration"}),
"const"        : map({"internal_name": "CONST"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "variable_declaration"}),
"var"          : map({"internal_name": "VAR"       , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "variable_declaration"}),
"include"      : map({"internal_name": "IMPORT"    , "parser": _include     , "scoped": False, "body_required": False, "keyword_type": "module_import"}),
"import"       : map({"internal_name": "IMPORT"    , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "module_import"}),
"using"        : map({"internal_name": "USING"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "module_import"}),
"from"         : map({"internal_name": "FROM"      , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "module_import"}),
"yield from"   : map({"internal_name": "YIELD_FROM", "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "asynchronous_control"}),
"yield"        : map({"internal_name": "YIELD"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "asynchronous_control"}),
"await"        : map({"internal_name": "AWAIT"     , "parser": dummy        , "scoped": False, "body_required": False, "keyword_type": "asynchronous_control"}),
*/

#[repr(C)]
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct Keyword {
    pub str: &'static str,
    pub scoped: bool,
    pub body_required: bool, // deprecate this field
}



const IF:           Keyword = Keyword { str: "if",        scoped: false,    body_required: true };
const ELIF:         Keyword = Keyword { str: "elif",      scoped: false,    body_required: true };
const ELSE:         Keyword = Keyword { str: "else",      scoped: false,    body_required: true };
const UNLESS:       Keyword = Keyword { str: "unless",    scoped: false,    body_required: true };
const WHILE:        Keyword = Keyword { str: "while",     scoped: false,    body_required: true };
const FOR:          Keyword = Keyword { str: "for",       scoped: true,     body_required:true };
const CASE:         Keyword = Keyword { str: "case",      scoped: false,    body_required: true };
const DEFAULT:      Keyword = Keyword { str: "default",   scoped: false,    body_required: true };
const SWITCH:       Keyword = Keyword { str: "switch",    scoped: false,    body_required: true };
const MATCH:        Keyword = Keyword { str: "match",     scoped: false,    body_required: true };
// Functions
const FN:           Keyword = Keyword { str: "fn",        scoped: true,     body_required: true };
const LAMBDA:       Keyword = Keyword { str: "lambda",    scoped: false,    body_required: true };
// Threads
const THREAD:       Keyword = Keyword { str: "thread",    scoped: true,     body_required: true };
// Macros
const MACRO:        Keyword = Keyword { str: "macro",     scoped: true,     body_required: true };
// Async
const ASYNC:        Keyword = Keyword { str: "async",     scoped: false,    body_required: true };
// Return
const RETURN:       Keyword = Keyword { str: "return",    scoped: false,    body_required: true };
// Classes
const CLASS:        Keyword = Keyword { str: "class",     scoped: true,     body_required: true };
const INTERFACE:    Keyword = Keyword { str: "interface", scoped: true,     body_required: true };
const STRUCT:       Keyword = Keyword { str: "struct",    scoped: true,     body_required: true };
const UNION:        Keyword = Keyword { str: "union",     scoped: true,     body_required: true };
const ENUM:         Keyword = Keyword { str: "enum",      scoped: true,     body_required: true };
// Abstract
const ABSTRACT:     Keyword = Keyword { str: "abstract",  scoped: true,     body_required: true };
// Error Handling
const TRY:          Keyword = Keyword { str: "try",       scoped: false,    body_required: true };
const CATCH:        Keyword = Keyword { str: "catch",     scoped: false,    body_required: true };
const EXCEPT:       Keyword = Keyword { str: "except",    scoped: false,    body_required: true };
const FINALLY:      Keyword = Keyword { str: "finally",   scoped: false,    body_required: true };
const THROW:        Keyword = Keyword { str: "throw",     scoped: false,    body_required: true };
// Loops
const BREAK:        Keyword = Keyword { str: "break",     scoped: false,    body_required: false };
const CONTINUE:     Keyword = Keyword { str: "continue",  scoped: false,    body_required: false };
// Delegate
const DELEGATE:     Keyword = Keyword { str: "delegate",  scoped: false,    body_required: false };
// With
const WITH:         Keyword = Keyword { str: "with",      scoped: false,    body_required: true };
// Access Modifiers
const PRIVATE:      Keyword = Keyword { str: "private",   scoped: false,    body_required: false };
const PROTECTED:    Keyword = Keyword { str: "protected", scoped: false,    body_required: false };
const PUBLIC:       Keyword = Keyword { str: "public",    scoped: false,    body_required: false };
const FINAL:        Keyword = Keyword { str: "final",     scoped: false,    body_required: false };
const STATIC:       Keyword = Keyword { str: "static",    scoped: false,    body_required: false };
const UNSAFE:       Keyword = Keyword { str: "unsafe",    scoped: false,    body_required: false };
// Variables
const LET:          Keyword = Keyword { str: "let",       scoped: false,    body_required: false };
const CONST:        Keyword = Keyword { str: "const",     scoped: false,    body_required: false };
const VAR:          Keyword = Keyword { str: "var",       scoped: false,    body_required: false };
// Imports
const INCLUDE:      Keyword = Keyword { str: "include",   scoped: false,    body_required: false };
const IMPORT:       Keyword = Keyword { str: "import",    scoped: false,    body_required: false };
const USING:        Keyword = Keyword { str: "using",     scoped: false,    body_required: false };
const FROM:         Keyword = Keyword { str: "from",      scoped: false,    body_required: false };
const YIELD:        Keyword = Keyword { str: "yield",     scoped: false,    body_required: false };
const AWAIT:        Keyword = Keyword { str: "await",     scoped: false,    body_required: false };

pub const KEYWORDS: [&Keyword; 42] = [
    &IF,   &ELIF,   &ELSE,   &UNLESS,   &WHILE,  &FOR,    &CASE,     &DEFAULT,
    &FN,   &LAMBDA, &THREAD, &MACRO,    &ASYNC,  &RETURN, &CLASS,    &INTERFACE,
    &TRY,  &CATCH,  &EXCEPT, &FINALLY,  &THROW,  &BREAK,  &CONTINUE, &DELEGATE,
    &LET,  &CONST,  &AWAIT,  &INCLUDE,  &IMPORT, &USING,  &FROM,     &YIELD,
    &WITH, &MATCH,  &SWITCH, &ABSTRACT, &ENUM,   &STRUCT, &PRIVATE,  &PROTECTED,
    &VAR,  &PUBLIC, &FINAL,  &STATIC,   &UNSAFE, &UNION,
];

static pub fn get_keyword(keyword: &str) -> &Keyword {
    for kw in KEYWORDS.iter() {
        if kw.str == keyword {
            return &kw;
        }
    }
    panic!("Keyword not found: {}", keyword);
}

static pub fn get_all_keywords() -> &'static [&'static Keyword] {
    &KEYWORDS
}