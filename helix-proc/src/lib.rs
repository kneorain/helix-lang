/*
    group keyword {
        // Control Flow

        /// The if keyword
        statement IF:Keyword = "if";
        statement UNLESS:Keyword = "unless"; /// The unless keyword, like elif
        statement ELIF:Keyword = "elif"; /// The else keyword
        statement ELSE:Keyword = "else"; /// The else keyword

        // Loops
        statement WHILE:Keyword = "while"; /// The while keyword
        statement FOR:Keyword = "for"; /// The for keyword
        statement LOOP:Keyword = "loop"; /// An endless loop

        // Pattern Matching
        statement CASE:Keyword = "case"; ///  The case keyword
        statement DEFAULT:Keyword = "default"; /// The default keyword
        statement MATCH:Keyword = "match" /// The match keyword
        statement SWITCH:Keyword = "switch"; /// The switch keyword

        // Loop Control
        statement BREAK:Keyword = "break"; /// The break keyword
        statement CONTINUE:Keyword = "continue"; /// The continue keyword

        // Function Declaration
        statement FUNCTION:Keyword = "fn"; /// The function keyword
        statement ANONYMOUS_FUNCTION:Keyword = "lambda"; /// The lambda keyword

        // Threading
        statement THREAD:Keyword = "thread"; /// The thread keyword
        statement TENSOR:Keyword = "tensor"; /// The tensor keyword

        // Meta Programming
        statement MACRO:Keyword = "macro"; /// The macro keyword
        statement OPERATOR:Keyword = "op"; /// The operator keyword

        // Function Modifier
        statement ASYNC:Keyword = "async"; /// Denotes an asynchronous function
        statement DELEGATE:Keyword = "delegate"; /// The delegate keyword
        statement INLINE:Keyword = "inline"; /// Denotes an inline function

        // Function Control
        statement RETURN:Keyword = "return"; /// Returns a value from a function

        // Data Structures
        statement CLASS:Keyword = "class"; /// The class keyword
        statement STRUCT:Keyword = "struct"; /// A type structure without methods
        statement ENUM:Keyword = "enum"; /// An enum
        statement UNION:Keyword = "union"; /// A union

        // Type Declarations
        statement INTERFACE:Keyword = "interface"; /// An interface without default methods
        statement ABSTRACT:Keyword = "abstract"; /// An interface with default methods
        statement TYPE_ALIAS:Keyword = "type"; /// A type alias

        // Type Handling
        statement TYPEOF:Keyword = "typeof"; /// Returns the type of a variable
        statement SIZEOF:Keyword = "sizeof"; /// Returns the size of a type in bytes
        statement INSTANCE_OF:Keyword = "instance_of"; /// Checks if a variable is an instance of a type

        // Error Handling
        statement TRY:Keyword = "try"; /// The try keyword
        statement CATCH:Keyword = "catch"; /// The catch keyword
        statement EXCEPT:Keyword = "except"; /// The except keyword
        statement FINALLY:Keyword = "finally"; /// The finally keyword
        statement THROW:Keyword = "throw"; /// Throws an error

        // Core
        statement WITH:Keyword = "with"; /// The with keyword

        // Access Modifier
        statement PRIVATE:Keyword = "private"; /// Accessible from a data structure only
        statement PROTECTED:Keyword = "protected"; /// Accessible from a data structure and its children
        statement PUBLIC:Keyword = "public"; /// Accessible from anywhere
        statement CONST:Keyword = "const"; /// A compile time constant
        statement FINAL:Keyword = "final"; /// A runtime constant, once set cannot be changed
        statement STATIC:Keyword = "static"; /// Denotes interior mutability
        statement UNDEF:Keyword = "undef"; /// Notates Undefined Behavior

        // Variable Declaration
        statement LET:Keyword = "let"; /// A mutable variable
        statement VAR:Keyword = "var"; /// The var keyword
        
        // Assignment modifiers
        statement AUTO:Keyword = "auto"; /// A variable with automatic type inference, let auto x = 3;
        statement AWAIT:Keyword = "await"; /// Waits for an asynchronous future to complete when assigned to a variable, let await x = async_fn();

        // Module Import
        statement IMPORT:Keyword = "import"; /// Imports a module
        statement INCLUDE:Keyword = "include"; /// Includes a file
        statement USING:Keyword = "using"; /// Uses a module
        statement FROM:Keyword = "from"; /// Imports a module from a package

        // Asynchronous Control
        statement YIELD:Keyword = "yield"; /// Yields a value from a generator
// should be a modifier like let await 3= ...
    // and .await




    }








    // todo: goto keyword

    template Delimit(start: Literal, middle: Pattern, end?: Literal = self::start)-> Pattern {
        self::start self::middle self::end
    }

    template SquareBrackets(middle:Pattern) -> Delimit(b'[',middle,b']');
    template Parentheses(middle:Pattern) -> Delimit(b'(',middle,b')');
    template CurlyBrackets(middle:Pattern) -> Delimit(b'{',middle,b'}');
    template AngleBrackets(middle:Pattern) -> Delimit(b'<',middle,b'>');


    template SeparatedList(pattern:Pattern, separator:Pattern, optional_trailing:bool) -> Pattern {
        (self::pattern self::separator)* if optional_trailing {self::pattern?}
    }

    template CommaSeparated(pattern:Pattern,optional_trailing:bool) -> Separated(self::pattern, b',', self::optional_trailing);
    template SemicolonSeparated(pattern:Pattern,optional_trailing:bool) -> Separated(self::pattern, b';', self::optional_trailing);

    template RoundList(middle:Pattern) -> Parentheses(SeparatedList(self::middle, b',', true));
    template SquareList(middle:Pattern) -> SquareBrackets(SeparatedList(self::middle, b',', true));
    template CurlyList(middle:Pattern) -> CurlyBrackets(SeparatedList(self::middle, b',', true));
    template AngleList(middle:Pattern) -> AngleBrackets(SeparatedList(self::middle, b',', true));

    template Tuple(elements:Type) as Type -> RoundList(elements);
    template Tuple(elements:Expression) as Expression-> RoundList(elements);

    // TODO: need a way to type an array

    template Array(elements:Expression) as Expression -> SquareList(elements);

    

    pattern Identifier {

        first: Alpha | Underscore,
        rest: self::first | Numeric,
        
        Identifier() -> {
            self::first self::rest*
        }
    }

    pattern TypeGeneric {
        name: Identifier,
        generics: AngleList(Type),

        TypeGeneric() {
            self::name self::generics?
        }
    }

    pattern Type {
        name: Identifier,
        generics: TypeGeneric,

        Type() -> {
            self::name self::generics?
        }
    }


    pattern TypedAssignmentTernary {
        
        type_specifier?: if self::has_type { ':' self::type } 
        assignment?:  if self::HAS_ASSIGNMENT {'=' self::value},
        type_part?: if self::TYPE_OPTIONAL self::type_specifier? else self::type_specifier

        (name:Identifier, type:Pattern, value:Pattern, TYPE_OPTIONAL:bool; HAS_TYPE:bool, HAS_ASSIGNMENT:bool ) -> {
            self::name self::type_part self::assignment
        }
    }
    // this is later
    // pattern InlineMetaAttribute {
    //     name: Identifier,
        

    //     MetaAttribute() -> {
    //         self::name 
    //     }
    // }



    template VariableDefinition(name:Identifier, type:Type, value:Expression)-> {
        TypedAssignmentTernary(self::name, self::type, self::value, false, true)
    };



    pattern GenericDefinition {

        name: Identifier,

        generic_item: TypedAssignmentTernary<Identifier, Type, Type>,

        generics: AngleList(self::generic_item),

        GenericDefinition() {
            self::name self::generics
        }
    }

  




    pattern TypeAlias {
        keyword = Keyword(keyword::TYPE)
        name: Identifier,
        bounds: TypeGeneric,
        generics: GenericDefinition,
        setting:TypedAssignmentTernary(self::name self::generics, self::bounds, Type),

        TypeAlias() -> {
            self::keyword self::setting
        }
    } */

use proc_macro2::{Delimiter, Group, Ident, Punct, Spacing, Span, TokenStream, TokenTree};
use quote::quote;
use quote::ToTokens;
use syn::custom_keyword;
use std::char;
use std::iter;
use std::panic;
use syn::parse;


// I am making a parser for my dsl


struct PatternSequence  {

}

enum PatternSequenceItem {
    Group(Vec<PatternSequenceItem>),
    PatternLiteral(TokenTree),
    PatternVariable(Ident),
    PatternType(Ident),
    /// |
    Or,
    /// !
    Not,
    /// *
    Repeat,
    /// ?
    Optional,
    /// +
    OneOrMore,
    /// &
    And,
    

}

enum PrefixOperator {
    Not,

}
enum InfixOperator {
    Or,
    And,
}

enum PostfixOperator {
    Repeat,
    Optional,
    // + or {1,}
    OneOrMore,


}


struct PatternMembers {


}

/*   template Delimit(start: Literal, middle: Pattern, end?: Literal = self::start)-> Pattern {
        self::start self::middle self::end
    } */
struct PatternTemplate {
    name: Ident,
    args:Vec<syn::FnArg>,




    

    
}

enum PatternAssignment {

}

struct PatternStruct {

}



// turns all the patterns into a 
struct PatternRuntime {


}

mod kw {

    use syn::custom_keyword;

    custom_keyword!(pattern);
    custom_keyword!(template);
    custom_keyword!(alias);
    custom_keyword!(group);

}

kw::







#[proc_macro]
pub fn compile_pat_lang(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    
    





}