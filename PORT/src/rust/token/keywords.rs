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
    pub ty: KeywordType,
}
#[derive(Debug, PartialEq, Eq, Hash)]
pub enum KeywordType {
    ControlFlow,
    Loop,
    LoopControl,
    PatternMatching,
    FunctionDeclaration,
    FunctionModifier,
    FunctionControl,
    StructureDeclaration,
    TypeDeclaration,
    ClassModifier,
    ErrorHandling,
    Core,
    AccessModifier,
    VariableDeclaration,
    ModuleImport,
    AsynchronousControl,
    MetaProgramming,
    TypeHandling,
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
    {$($internal:ident { scoped: $scoped:literal, body_required: $body_required:literal, ident: $ident:ident, ty:$ty:ident, description:$description:literal }),*} => {
        paste!{
            // For every keyword, create a constant with the keyword name
            $(
                #[doc = $description]
                const $internal: Keyword = Keyword {
                    ident:         stringify!($name),
                    scoped:        $scoped,
                    body_required: $body_required,
                    ty:        KeywordType::$ty,
                };
            )*

            // Creates the KEYWORD ARRAY
            #[doc = "An array of all the keywords"]
            pub const KEYWORDS: [Keyword; count!($($internal)*)] = [$($internal,)*];

            // Creates a function to get the keyword by name
            #[doc = "Get a keyword by its identifier"]
            pub fn get_keyword(ident: &str) -> &Keyword {
                // This is faster than using a for loop
                match ident {
                    // For every keyword, return the constant
                    $(
                        stringify!($ident) => &$internal,
                    )*
                    _ => panic_any(TokenError::InvalidKeyword(Box::from(ident)))
                }
            }

        }
    }
}

// TODO: make a way to define aliases for keywords

// make a separate keyword for header only keywords
// every thing at comp time has to be header only
// so if they use custom meta within meta it has to be in the namespace of the compiler 
define_keywords! {
    // Control Flow
    IF        { scoped: false, body_required: true, ident:if       , ty:ControlFlow  , description:"The if keyword"                },
    UNLESS    { scoped: false, body_required: true, ident:elif     , ty:ControlFlow  , description:"The unless keyword, like elif" },
    ELSE      { scoped: false, body_required: true, ident:else     , ty:ControlFlow  , description:"The else keyword"              },

    // Loops
    WHILE     { scoped: false, body_required: true, ident:while    , ty:Loop        , description:"The while keyword"             },
    FOR       { scoped: true , body_required: true, ident:for      , ty:Loop        , description:"The for keyword"               },
    //LOOP      { scoped: false, body_required: true, ident:loop , ty:Loop, description:"An endless loop" },
    // post test loop needed
    
    // Pattern Matching
    CASE      { scoped: false, body_required: true, ident:case     , ty:PatternMatching, description:"The case keyword" },
    DEFAULT   { scoped: false, body_required: true, ident:default  , ty:PatternMatching, description:"The default keyword" },
    MATCH     { scoped: false, body_required: false, ident:match    , ty:PatternMatching, description:"The match keyword" },
    SWITCH    { scoped: false, body_required: false, ident:switch   , ty:PatternMatching, description:"The switch keyword" },

    // Loop Control
    BREAK     { scoped: false, body_required: false, ident:break   , ty:LoopControl, description:"The break keyword"          },
    CONTINUE  { scoped: false, body_required: false, ident:continue, ty:LoopControl, description:"The continue keyword"       },

    // Function Declaration
    FUNCTION  { scoped: true , body_required: true , ident:fn       , ty:FunctionDeclaration, description:"The function keyword" },
    ANONYMOUS_FUNCTION { scoped: true , body_required: true , ident:lambda, ty:FunctionDeclaration, description:"The lambda keyword" },

    // Threading
    THREAD    { scoped: true , body_required: true , ident:thread   , ty:FunctionDeclaration, description:"The thread keyword" },

    // Meta Programming
    MACRO     { scoped: true , body_required: true, ident:macro    , ty:MetaProgramming, description:"The macro keyword" },
    OPERATOR  { scoped: true , body_required: true, ident:operator , ty:MetaProgramming, description:"The operator keyword" },


    // Function Modifier
    ASYNC     { scoped: false, body_required: false, ident:async    , ty:FunctionModifier, description:"Denotes an asynchronous function" },
    DELEGATE  { scoped: false, body_required: false, ident:delegate , ty:FunctionModifier, description:"The delegate keyword" },
    INLINE    { scoped: false, body_required: false, ident:inline   , ty:FunctionModifier, description:"Denotes an inline function" },

    // Function Control
    RETURN    { scoped: false, body_required: false, ident:return   , ty:FunctionControl, description:"Returns a value from a function" },

    // Data Structures
    CLASS      { scoped: true , body_required: true , ident:class    , ty:StructureDeclaration, description:"The class keyword" },
    STRUCT     { scoped: true , body_required: true , ident:struct   , ty:StructureDeclaration, description:"A type structure without methods" },
    ENUM       { scoped: true , body_required: true , ident:enum     , ty:StructureDeclaration, description:"An enum" },
    UNION      { scoped: true , body_required: true , ident:union    , ty:StructureDeclaration, description:"A union" },


    // Type Declarations
    INTERFACE  { scoped: true , body_required: true , ident:interface, ty:TypeDeclaration, description:"An interface without default methods" },
    ABSTRACT   { scoped: true , body_required: true , ident:abstract , ty:TypeDeclaration, description:"An interface with default methods" },
    TYPE       { scoped: false, body_required: false, ident:type     , ty:TypeDeclaration, description:"A type alias" },

    // Type Handling
    TYPEOF     { scoped: false, body_required: false, ident:typeof    , ty:TypeHandling, description:"Returns the type of a variable" },
    SIZEOF     { scoped: false, body_required: false, ident:sizeof    , ty:TypeHandling, description:"Returns the size of a type in bytes" },
    INSTANCEOF { scoped: false, body_required: false, ident:instanceof, ty:TypeHandling, description:"Checks if a variable is an instance of a type" }, // not sure about this


    // Error Handling

    TRY       { scoped: false, body_required: true , ident:try      , ty:ErrorHandling, description:"The try keyword" },
    CATCH     { scoped: false, body_required: true , ident:catch    , ty:ErrorHandling, description:"The catch keyword" },
    EXCEPT    { scoped: false, body_required: true , ident:except   , ty:ErrorHandling, description:"The except keyword" },
    FINALLY   { scoped: false, body_required: true , ident:finally  , ty:ErrorHandling, description:"The finally keyword" },
    THROW     { scoped: false, body_required: false, ident:throw    , ty:ErrorHandling, description:"Throws an error" },

    // // Core
    // with      { scoped: false, body_required: true  },

    // Access Modifier
    PRIVATE   { scoped: false, body_required: false, ident:private  , ty:AccessModifier, description:"Accessible from a data structure only" },
    PROTECTED { scoped: false, body_required: false, ident:protected, ty:AccessModifier, description:"Accessible from a data structure and its children" },
    PUBLIC    { scoped: false, body_required: false, ident:public   , ty:AccessModifier, description:"Accessible from anywhere" },
    CONST     { scoped: false, body_required: false, ident:const    , ty:AccessModifier, description:"A compile time constant" },
    FINAL     { scoped: false, body_required: false, ident:final    , ty:AccessModifier, description:"A runtime constant, once set cannot be changed" },
    STATIC    { scoped: false, body_required: false, ident:static   , ty:AccessModifier, description:"Denotes interior mutability" },
    UNSAFE    { scoped: false, body_required: false, ident:unsafe   , ty:AccessModifier, description:"Notates Undefined Behavior" },

    // Variable Declaration 
    LET       { scoped: false, body_required: false, ident:let      , ty:VariableDeclaration, description:"A mutable variable" }, // should use let mut ...
    VAR       { scoped: false, body_required: false, ident:var      , ty:VariableDeclaration, description:"The var keyword" },
    AUTO      { scoped: false, body_required: false, ident:auto     , ty:VariableDeclaration, description:"A variable with automatic type inference" }, // could be let auto x = 3;

    // Module Import
    IMPORT    { scoped: false, body_required: false, ident:import   , ty:ModuleImport, description:"Imports a module" },
    INCLUDE   { scoped: false, body_required: false, ident:include  , ty:ModuleImport, description:"Includes a file" },
    USING     { scoped: false, body_required: false, ident:using    , ty:ModuleImport, description:"Uses a module" },
    FROM      { scoped: false, body_required: false, ident:from     , ty:ModuleImport, description:"Imports a module from a package" },

    // Asynchronous Control
    YIELD     { scoped: false, body_required: false, ident:yield    , ty:AsynchronousControl, description:"Yields a value from a generator" },
    AWAIT     { scoped: false, body_required: false, ident:await    , ty:AsynchronousControl, description:"Waits for an asynchronous function to complete" }
    // should be a modifier like let await 3= ...
    // and .await 

}
