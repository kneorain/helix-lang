/*
"if"           : map({"internal_name": "IF"        , "parser": _unless      , "scoped": False, "has_body": True , "keyword_type": "control_flow"}),
"elif"         : map({"internal_name": "ELSE_IF"   , "parser": _unless      , "scoped": False, "has_body": True , "keyword_type": "control_flow"}),
"else"         : map({"internal_name": "ELSE"      , "parser": _unless      , "scoped": False, "has_body": True , "keyword_type": "control_flow"}),
"unless"       : map({"internal_name": "UNLESS"    , "parser": _unless      , "scoped": False, "has_body": True , "keyword_type": "control_flow"}),
"continue"     : map({"internal_name": "CONTINUE"  , "parser": _no_change   , "scoped": False, "has_body": False, "keyword_type": "loop_control"}),
"while"        : map({"internal_name": "WHILE"     , "parser": _no_change   , "scoped": False, "has_body": True , "keyword_type": "loop"}),
"for"          : map({"internal_name": "FOR"       , "parser": _for         , "scoped": True, "has_body":  True , "keyword_type": "loop"}),
"case"         : map({"internal_name": "CASE"      , "parser": dummy        , "scoped": False, "has_body": True , "keyword_type": "case_control"}),
"default"      : map({"internal_name": "DEFAULT"   , "parser": dummy        , "scoped": False, "has_body": True , "keyword_type": "case_control"}),
"switch"       : map({"internal_name": "SWITCH"    , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "case_control"}),
"match"        : map({"internal_name": "MATCH"     , "parser": dummy       , "scoped": False, "has_body": False, "keyword_type": "case_control"}),
"fn"           : map({"internal_name": "FUNCTION"  , "parser": _function    , "scoped": True , "has_body": True , "keyword_type": "function_declaration"}),
"lambda"       : map({"internal_name": "LAMBDA"    , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "function_declaration"}),
"thread"       : map({"internal_name": "THREAD"    , "parser": dummy        , "scoped": True , "has_body": True , "keyword_type": "function_declaration"}),
"macro"        : map({"internal_name": "MACRO"     , "parser": dummy        , "scoped": True , "has_body": True , "keyword_type": "function_declaration"}),
"async"        : map({"internal_name": "ASYNC"     , "parser": _function    , "scoped": False, "has_body": False, "keyword_type": "function_modifier"}),
"return"       : map({"internal_name": "RETURN"    , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "function_control"}),
"class"        : map({"internal_name": "CLASS"     , "parser": _class       , "scoped": True , "has_body": True , "keyword_type": "class_declaration"}),
"interface"    : map({"internal_name": "INTERFACE" , "parser": _class        , "scoped": True , "has_body": True , "keyword_type": "type_declaration"}),
"struct"       : map({"internal_name": "STRUCT"    , "parser": _class        , "scoped": True , "has_body": True , "keyword_type": "type_declaration"}),
"union"        : map({"internal_name": "UNION"     , "parser": _class        , "scoped": True , "has_body": True , "keyword_type": "type_declaration"}),
"enum"         : map({"internal_name": "ENUM"      , "parser": _class        , "scoped": True , "has_body": True , "keyword_type": "type_declaration"}),
"abstract"     : map({"internal_name": "ABSTRACT"  , "parser": _class        , "scoped": True , "has_body": True , "keyword_type": "class_modifier"}),
"try"          : map({"internal_name": "TRY"       , "parser":  dummy        , "scoped": False, "has_body": True , "keyword_type": "error_handling"}),
"catch"        : map({"internal_name": "CATCH"     , "parser":  dummy        , "scoped": False, "has_body": True , "keyword_type": "error_handling"}),
"except"        : map({"internal_name": "EXCEPT"   , "parser":  dummy        , "scoped": False, "has_body": True , "keyword_type": "error_handling"}),
"finally"      : map({"internal_name": "FINALLY"   , "parser":  dummy        , "scoped": False, "has_body": True , "keyword_type": "error_handling"}),
"throw"        : map({"internal_name": "THROW"     , "parser":  dummy        , "scoped": False, "has_body": False, "keyword_type": "error_handling"}),
"break"        : map({"internal_name": "BREAK"     , "parser":  _no_change   , "scoped": False, "has_body": False, "keyword_type": "core"}),
"delegate"     : map({"internal_name": "DELEGATE"  , "parser":  dummy        , "scoped": False, "has_body": False, "keyword_type": "core"}),
"with"         : map({"internal_name": "WITH"      , "parser":  _no_change   , "scoped": False, "has_body": True , "keyword_type": "core"}),
"private"      : map({"internal_name": "PRIVATE"   , "parser":  _function   , "scoped": False, "has_body": False, "keyword_type": "access_modifier"}),
"protected"    : map({"internal_name": "PROTECTED" , "parser":  _function   , "scoped": False, "has_body": False, "keyword_type": "access_modifier"}),
"public"       : map({"internal_name": "PUBLIC"    , "parser":  _function   , "scoped": False, "has_body": False, "keyword_type": "access_modifier"}),
"final"        : map({"internal_name": "FINAL"     , "parser":  _function   , "scoped": False, "has_body": False, "keyword_type": "access_modifier"}),
"static"       : map({"internal_name": "STATIC"    , "parser":  _function   , "scoped": False, "has_body": False, "keyword_type": "access_modifier"}),
"unsafe"       : map({"internal_name": "UNSAFE"    , "parser":  _function   , "scoped": False, "has_body": False, "keyword_type": "access_modifier"}),
"let"          : map({"internal_name": "LET"       , "parser": _let         , "scoped": False, "has_body": False, "keyword_type": "variable_declaration"}),
"const"        : map({"internal_name": "CONST"     , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "variable_declaration"}),
"var"          : map({"internal_name": "VAR"       , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "variable_declaration"}),
"include"      : map({"internal_name": "IMPORT"    , "parser": _include     , "scoped": False, "has_body": False, "keyword_type": "module_import"}),
"import"       : map({"internal_name": "IMPORT"    , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "module_import"}),
"using"        : map({"internal_name": "USING"     , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "module_import"}),
"from"         : map({"internal_name": "FROM"      , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "module_import"}),
"yield from"   : map({"internal_name": "YIELD_FROM", "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "asynchronous_control"}),
"yield"        : map({"internal_name": "YIELD"     , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "asynchronous_control"}),
"await"        : map({"internal_name": "AWAIT"     , "parser": dummy        , "scoped": False, "has_body": False, "keyword_type": "asynchronous_control"}),
*/

use super::TokenError;
use paste::paste;
use std::panic::panic_any;

#[repr(C)]
#[derive(Debug, PartialEq, Eq, Hash)]
pub struct Keyword {
    pub ident: &'static str,
    pub scoped: bool,
    pub has_body: bool, // deprecate this field
}


/// Counts the number of elements passed to it,
/// [credit](https://stackoverflow.com/a/34324856)
macro_rules! count {
    () => (0usize);
    ( $input:tt $($element:tt)* ) => (1usize + count!($($element)*));
}

// if something is passed in and its nothing then return the default
// option!(something, default_expr)
// option!((pretend this is blank), default_expr)
// if its something then return the something, this is for returning code
// #[macro_export]
// macro_rules! option {
//     ($option:expr, $default:expr ) => {
//         $option
//     };
//     (, $default:expr) => {
//         $default
//     };
// }

// macro_rules! unordered_struct_macro{
//     ($name:ident { $($field:ident : $value:expr),* }) => {
//         paste! {
//             struct $name {
//                 $(
//                     $field: $value,
//                 )*
//             }
//         }
//     };
// }

// make this load at compile time from a toml file or something, or even load into a dyn lib that is called on comp time...

// TODO: Add a comment generator for the keywords, like a field called description or something and it is applied to #[doc = ...]
macro_rules! define_keywords {
    // use paste to convert the cases ident: $ident:ident,
    {$($internal:ident { scoped: $scoped:literal, has_body: $has_body:literal, ident: $ident:literal, doc: $doc:literal }),*} => {
        paste!{

            // For every keyword, create a constant with the keyword name
            $(
                #[doc =$doc ]
                const $internal: Keyword = Keyword {
                    ident:    $ident,
                    scoped:   $scoped,
                    has_body: $has_body,
                };
            )*

            // Creates the KEYWORD ARRAY
            #[doc = "An array of all the keywords"]
            pub const KEYWORDS: [Keyword; count!($($internal)*)] = [$($internal,)*];

            // Creates a function to get the keyword by name
            #[doc = "Get a keyword by its identifier"]
            pub fn get_keyword(ident: &str) -> Keyword {
                // This is faster than using a for loop
                match ident {
                    // For every keyword, return the constant
                    $(
                        $ident => $internal,
                    )*
                    _ => panic_any(TokenError::InvalidKeyword(Box::from(ident)))
                }
            }
        }
    };
}

// make a macro that deals with optionals within macro definitions

// TODO: make a way to define aliases for keywords

// make a separate keyword for header only keywords
// every thing at comp time has to be header only
// so if they use custom meta within meta it has to be in the namespace of the compiler
define_keywords! {
    // Control Flow
    IF                 {  scoped: false, has_body: true  ,ident:"if", doc:"The if keyword"                   },
    UNLESS             { scoped: false, has_body: true , ident:"elif"     , doc: "The unless keyword, like elif" },
    ELSE               { scoped: false, has_body: true , ident:"else"     , doc: "The else keyword"              },

    // Loops
    WHILE              { scoped: false, has_body: true , ident:"while"    , doc: "The while keyword"             },
    FOR                { scoped: true , has_body: true , ident:"for"      , doc: "The for keyword"               },
    //LOOP      { scoped: false, has_body: true, ident:"loop" , doc: "An endless loop" },
    // post test loop needed


    // Pattern Matching
    CASE               { scoped: false, has_body: true , ident:"case"     , doc: "The case keyword" },
    DEFAULT            { scoped: false, has_body: true , ident:"default"  , doc: "The default keyword" },
    MATCH              { scoped: false, has_body: false, ident:"match"    , doc: "The match keyword" },
    SWITCH             { scoped: false, has_body: false, ident:"switch"   , doc: "The switch keyword" },

    // Loop Control
    BREAK              { scoped: false, has_body: false, ident:"break"   , doc: "The break keyword"          },
    CONTINUE           { scoped: false, has_body: false, ident:"continue", doc: "The continue keyword"       },

    // Function Declaration
    FUNCTION           { scoped: true , has_body: true , ident:"fn"       , doc: "The function keyword" },
    ANONYMOUS_FUNCTION { scoped: true , has_body: true , ident:"lambda"   , doc: "The lambda keyword" },

    // Threading
    THREAD             { scoped: true , has_body: true , ident:"thread"   , doc: "The thread keyword" },

    // Meta Programming
    MACRO              { scoped: true , has_body: true, ident:"macro"    , doc: "The macro keyword" },
    OPERATOR           { scoped: true , has_body: true, ident:"operator" , doc: "The operator keyword" },


    // Function Modifier
    ASYNC              { scoped: false, has_body: false, ident:"async"    , doc: "Denotes an asynchronous function" },
    DELEGATE           { scoped: false, has_body: false, ident:"delegate" , doc: "The delegate keyword" },
    //INLINE             { scoped: false, has_body: false, ident:"inline"   , doc: "Denotes an inline function" },

    // Function Control
    RETURN             { scoped: false, has_body: false, ident:"return"   , doc: "Returns a value from a function" },

    // Data Structures
    CLASS              { scoped: true , has_body: true , ident:"class"     , doc: "The class keyword" },
    STRUCT             { scoped: true , has_body: true , ident:"struct"    , doc: "A type structure without methods" },
    ENUM               { scoped: true , has_body: true , ident:"enum"      , doc: "An enum" },
    UNION              { scoped: true , has_body: true , ident:"union"     , doc: "A union" },


    // Type Declarations
    INTERFACE          { scoped: true , has_body: true , ident:"interface", doc: "An interface without default methods" },
    ABSTRACT           { scoped: true , has_body: true , ident:"abstract" , doc: "An interface with default methods" },
    TYPE               { scoped: false, has_body: false, ident:"type"     , doc: "A type alias" },

    // Type Handling
    TYPEOF             { scoped: false, has_body: false, ident:"typeof"    , doc: "Returns the type of a variable" },
    SIZEOF             { scoped: false, has_body: false, ident:"sizeof"    , doc: "Returns the size of a type in bytes" },
    INSTANCEOF         { scoped: false, has_body: false, ident:"instanceof", doc: "Checks if a variable is an instance of a type" }, // not sure about this


    // Error Handling

    TRY                { scoped: false, has_body: true , ident:"try"      , doc: "The try keyword" },
    CATCH              { scoped: false, has_body: true , ident:"catch"    , doc: "The catch keyword" },
    EXCEPT             { scoped: false, has_body: true , ident:"except"   , doc: "The except keyword" },
    FINALLY            { scoped: false, has_body: true , ident:"finally"  , doc: "The finally keyword" },
    THROW              { scoped: false, has_body: false, ident:"throw"    , doc: "Throws an error" },

    // // Core
    // with      { scoped: false, has_body: true  },

    // Access Modifier
    PRIVATE            { scoped: false, has_body: false, ident:"private"  , doc: "Accessible from a data structure only" },
    PROTECTED          { scoped: false, has_body: false, ident:"protected", doc: "Accessible from a data structure and its children" },
    PUBLIC             { scoped: false, has_body: false, ident:"public"   , doc: "Accessible from anywhere" },
    CONST              { scoped: false, has_body: false, ident:"const"    , doc: "A compile time constant" },
    FINAL              { scoped: false, has_body: false, ident:"final"    , doc: "A runtime constant, once set cannot be changed" },
    STATIC             { scoped: false, has_body: false, ident:"static"   , doc: "Denotes interior mutability" },
    UNSAFE             { scoped: false, has_body: false, ident:"unsafe"   , doc: "Notates Undefined Behavior" },

    // Variable Declaration
    LET                { scoped: false, has_body: false, ident:"let"      , doc: "A mutable variable" }, // should use let mut ...
    VAR                { scoped: false, has_body: false, ident:"var"      , doc: "The var keyword" },
    AUTO               { scoped: false, has_body: false, ident:"auto"     , doc: "A variable with automatic type inference" }, // could be let auto x = 3;

    // Module Import
    IMPORT             { scoped: false, has_body: false, ident:"import"   , doc: "Imports a module" },
    INCLUDE            { scoped: false, has_body: false, ident:"include"  , doc: "Includes a file" },
    USING              { scoped: false, has_body: false, ident:"using"    , doc: "Uses a module" },
    FROM               { scoped: false, has_body: false, ident:"from"     , doc: "Imports a module from a package" },

    // Asynchronous Control
    YIELD              { scoped: false, has_body: false, ident:"yield"    , doc: "Yields a value from a generator" },
    AWAIT              { scoped: false, has_body: false, ident:"await"    , doc: "Waits for an asynchronous function to complete" }
    // should be a modifier like let await 3= ...
    // and .await

}
