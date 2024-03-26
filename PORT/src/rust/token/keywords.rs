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

use super::TokenError;
use paste::paste;
use std::panic::panic_any;

#[repr(C)]
#[derive(Debug, PartialEq, Eq, Hash)]
pub struct Keyword {
    pub ident: &'static str,
    pub scoped: bool,
    pub body_required: bool, // deprecate this field
}

/// Counts the number of elements passed to it,
/// [credit](https://stackoverflow.com/a/34324856)
macro_rules! count {
    () => (0usize);
    ( $input:tt $($element:tt)* ) => (1usize + count!($($element)*));
}

// TODO: Add a comment generator for the keywords, like a field called description or something and it is applied to #[doc = ...]
macro_rules! define_keywords {
    // use paste to convert the cases
    {$($name:ident { scoped: $scoped:literal, body_required: $body_required:literal}),*} => {
        paste!{
            // For every keyword, create a constant with the keyword name
            $(
                #[doc = "The " $name " keyword"]
                const [<$name:snake:upper>]: Keyword = Keyword {
                    ident:         stringify!($name),
                    scoped:        $scoped,
                    body_required: $body_required,
                };
            )*

            // Creates the KEYWORD ARRAY

            pub const KEYWORDS: [Keyword; count!($($name)*)] = [$([<$name:snake:upper>],)*];

            // Creates a function to get the keyword by name
            #[doc = "Get a keyword by its identifier"]
            pub fn get_keyword(ident: &str) -> &Keyword {
                // This is faster than using a for loop
                match ident {
                    // For every keyword, return the constant
                    $(
                        stringify!($name) => &[<$name:snake:upper>],
                    )*
                    _ => panic_any(TokenError::InvalidKeyword(Box::from(ident)))
                }
            }
            
        }
    }
}



define_keywords! {
    // Control Flow
    if        { scoped: false, body_required: true  },
    unless    { scoped: false, body_required: true  },
    else      { scoped: false, body_required: true  },
    
    // Loops
    while     { scoped: false, body_required: true  },
    for       { scoped: true , body_required: true  },
    
    // Loop Control
    continue  { scoped: false, body_required: false },
    break     { scoped: false, body_required: false },    
    // in        { scoped: false, body_required: false },

    // Pattern Matching
    match     { scoped: false, body_required: false },
    switch    { scoped: false, body_required: false },
    case      { scoped: false, body_required: true  },
    default   { scoped: false, body_required: true  },

    // Function Declaration
    fn         { scoped: true , body_required: true  },
    lambda     { scoped: false, body_required: false },
    thread     { scoped: true , body_required: true  },
    macro      { scoped: true , body_required: true  },

    // Function Modifier
    async      { scoped: false, body_required: false }, // Denotes an asynchronous function
    delegate   { scoped: false, body_required: false }, 
    inline     { scoped: false, body_required: false }, // Denotes an inline function

    // Function Control
    return     { scoped: false, body_required: false }, // Returns a value from a function
    
    // Data Structures
    class      { scoped: true , body_required: true  },
    struct     { scoped: true , body_required: true  }, // A type structure without methods
    enum       { scoped: true , body_required: true  }, // An enum
    union      { scoped: true , body_required: true  }, // A union

    // Type Declaration
    abstract   { scoped: true , body_required: true  }, // An interface with default methods
    type       { scoped: false, body_required: false }, // A type alias
    interface  { scoped: true , body_required: true  }, // An interface without default methods
    
    
    // Type Handing
    typeof     { scoped: false, body_required: false }, // Returns the type of a variable
    sizeof     { scoped: false, body_required: false }, // Returns the size of a type in bytes
    instanceof { scoped: false, body_required: false }, // Checks if a variable is an instance of a type

    // Error Handling
    try       { scoped: false, body_required: true  }, 
    catch     { scoped: false, body_required: true  },
    except    { scoped: false, body_required: true  },
    finally   { scoped: false, body_required: true  }, 
    throw     { scoped: false, body_required: false }, // Throws an error

    // Core
    with      { scoped: false, body_required: true  },

    // Access Modifier
    private   { scoped: false, body_required: false }, // Accessible from the class only
    protected { scoped: false, body_required: false }, // Accessible from the class and subclasses
    public    { scoped: false, body_required: false }, // Accessible from anywhere
    const     { scoped: false, body_required: false }, // A compile time constant, 
    final     { scoped: false, body_required: false }, // A runtime constant, once set cannot be changed 
    static    { scoped: false, body_required: false }, // A denotes interior mutability 
    unsafe    { scoped: false, body_required: false }, // Notates Undefined Behavior
    
    
    // Variable Declaration
    let       { scoped: false, body_required: false }, // A mutable variable
    var       { scoped: false, body_required: false }, 
    auto      { scoped: false, body_required: false }, // A variable with automatic type inference 

    // Module Import
    include   { scoped: false, body_required: false }, // Includes a file
    import    { scoped: false, body_required: false }, // Imports a module
    using     { scoped: false, body_required: false }, // Uses a module
    from      { scoped: false, body_required: false }, // Imports a module from a package
    
    // Asynchronous Control
    yield     { scoped: false, body_required: false },
    await     { scoped: false, body_required: false }
}
