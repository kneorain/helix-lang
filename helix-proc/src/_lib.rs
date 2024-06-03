//use proc_macro2::{Delimiter, Group, Ident, Punct, Spacing, Span, TokenStream, TokenTree};
// use quote::quote;
// use quote::ToTokens;
// use std::char;
// use std::iter;
// use std::panic;
// use syn::parse;

mod pat_lang;
// use std::ops::Add;
// example of add type bound

// gets
// two_char_operators:helix_proc::convert_bytes_to_u16!( b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
// b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
// b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
// b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
// b"::" | b"||" | b"++" | b"__" | b"?="),

//use quote::ToTokens;

#[proc_macro]
pub fn convert_bytes_to_u16(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    input
        .to_string()
        .replace("\n", "")
        .split(" | ")
        .map(|x| {
            // parse the byte string to a string
            unsafe {
                let s = x.parse::<String>().unwrap();
                
                format!("{}", (s.as_ptr().add(2) as *const u16).read())
            }
        })
        .collect::<Vec<String>>()
        .join("|")
        .parse()
        .unwrap()
}

#[proc_macro]
pub fn get_first_char_pattern(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    let mut input = input
        .to_string()
        .replace("\n", "")
        .split(" | ")
        .map(|x| format!("b'{}'", x.as_bytes()[2] as char))
        .collect::<Vec<String>>();

    // sort for dedup to work
    input.sort();
    input.dedup();

    input.join(" | ").parse().unwrap()
}
#[proc_macro]
/// Returns the input that it was given,
/// used to remove the type within a macro_rules
pub fn raw(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    input.to_string().parse().unwrap()
}
/*//use proc_macro2::{Delimiter, Group, Ident, Punct, Spacing, Span, TokenStream, TokenTree};
// use quote::quote;
// use quote::ToTokens;
// use std::char;
// use std::iter;
// use std::panic;
// use syn::parse;

// use std::ops::Add;
// example of add type bound

use std::{borrow::BorrowMut, collections};

use syn::{
    braced,
    ext::IdentExt,
    parse::{self, Parse, ParseBuffer, ParseStream, Peek},
    parse_macro_input, Arm, Ident, Pat, Token,
};

// gets
// two_char_operators:helix_proc::convert_bytes_to_u16!( b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
// b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
// b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
// b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
// b"::" | b"||" | b"++" | b"__" | b"?="),
macro_rules! pipe_split {
    () => {
        // "|" | " | " | " |"
    };
}
/*




macro_rules! token_patterns {
    ($($name:ident:  $patten:pat),*) => {
        $(
            macro_rules! $name {
                () => {
                    $patten
                };
                // convert a pattern to an expression
                ($expr:expr) => {
                    $expr
                };
                (first_char) => {
                    helix_proc::get_first_char_pattern!($patten)
                };

                (u16) => {
                    helix_proc::convert_bytes_to_u16!($patten)
                };

                (match $ch:expr) => {
                    matches!($ch, $name!())
                };

                (u16 match $ch:expr) => {
                    matches!($ch, $name!(u16))
                };

                (trie_match $ch:expr) => {
                    trie_match::trie_match!{
                        match $ch {
                            $patten => true,
                        _ => false
                    }}
                };
            }
        )*
    }

}
*/
struct LexToken {
    name: Ident,
    pattern: LexPattern,
}

impl Parse for LexToken {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let name = input.parse()?;
        input.parse::<Token![:]>()?;
        let pattern = input.parse()?;
        Ok(Self { name, pattern })
    }
}

type TokenFields = syn::punctuated::Punctuated<LexToken, syn::token::Comma>;

struct LexTokenGroup {
    name: Ident,
    tokens: TokenFields,
}

use syn::token::Brace;
impl Parse for LexTokenGroup {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let name = input.parse()?;

        input.parse::<Token![:]>()?;

        let content;
        let lex_tokens = braced!(content in input);

        Ok(Self {
            name,
            tokens: content.parse_terminated(LexToken::parse, Token![,])?,
        })
    }
}

enum LexPattern {
    TokenGroup(Box<LexTokenGroup>),
    TokenRule(Pat),
}

impl Parse for LexPattern {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        if input.peek(Brace) {
            Ok(Self::TokenGroup(Box::new(input.parse()?)))
        } else {
            patterns.push(Pat::parse_multi_with_leading_vert(input));

            Ok(Self::TokenRuleUnion(patterns))
        }
    }
}

#[proc_macro]
pub fn define_tokens(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    todo!()
    //let
}

// #[proc_macro]
// pub fn convert_pattern_to_int_pattern(input: proc_macro::TokenStream) -> proc_macro::TokenStream {

//     let pattern:Pat = parse_macro_input!(input with Pat::parse_multi);

//     match pattern.borrow_mut() {
//         Pat::Or(or) =>{

//         }
//         _ => {}
//     }

// }

// fn str_pattern_to_int_pattern(pattern: Pat) -> Pat {

// }

// #[proc_macro]
// pub fn to_byte_repr(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
//     input
//         .to_string()
//         .split(pipe_split!())
//         .map(|x| "b".to_string() + x)
//         .join("|")
//         .parse()
//         .unwrap()
// }

fn map_escape(s: &[u8]) -> &[u8] {
    match s[..1] {
        &b"\\n" => b"\n",
        &b"\\r" => b"\r",
        &b"\\t" => b"\t",
        &b"\\0" => b"\0",
        &b"\\'" => b"\'",
        &b"\\\"" => b"\"",
        &b"\\\\" => b"\\",
        &b"\\x" if s[2].is_ascii_alphanumeric() & s[3].is_ascii_alphanumeric() => unsafe {
            std::str::from_utf8_unchecked(&[s[2], s[3]])
        },
        _ => s,
    }
}



#[proc_macro]
pub fn get_first_char_pattern(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    let mut input = input
        .to_string()
        .replace('\n' | " " | '\\', "")
        .split(pipe_split!())
        .map(|x| format!("b'{}'", x.as_bytes()[2] as char))
        .collect::<Vec<String>>();

    // sort for dedup to work
    input.sort();
    input.dedup();

    input.join("|").parse().unwrap()
}

// conditional!(, const FISH: &str = "salmon" );

// #[proc_macro]
// pub fn check_if_empty(input: proc_macro::TokenStream) ->  proc_macro::TokenStream {
//     input.into_token_stream().is_empty().to_token_stream()
// }

// #[proc_macro]
// pub fn conditional_j(input: TokenStream) -> TokenStream {
//     /*
//     condition(if stringify!($has_body) == "true" { has_body: true } else { has_body: false })

//      */
//     let body: syn::ExprIf = parse(input).expect("Expected if expression");

//     match evaluate_condition(body.cond) {
//         LitValue::Bool(true) => {
//             quote! { #body.then_branch }
//         },
//         LitValue::Bool(false) => {
//             if let Some(else_branch) = body.else_branch {
//                 quote! { #else_branch }
//             } else {
//                 TokenStream::new()
//             }
//         }
//         e => panic!("Expected boolean, found the conditional evaluation: {:#?}", e),
//     }
// }

// enum LitValue {
//     Bool(bool),
//     Int(u128),
//     Float(f64),
//     Char(char),
//     Str(String),
//     BytStr(Vec<u8>),
// }

// impl From<syn::Lit> for LitValue {
//     fn from(lit: syn::Lit) -> Self {

//         use syn::Lit::*;
//         match lit {
//             Bool(lit) => LitValue::Bool(lit.value),
//             Int(lit) => LitValue::Int(lit.base10_parse().expect("Expected integer")),
//             Float(lit) => LitValue::Float(lit.base10_parse().expect("Expected float")),
//             Char(lit) => LitValue::Char(lit.value()),
//             Str(lit) => LitValue::Str(lit.value()),
//             ByteStr(lit) => LitValue::BytStr(lit.value()),
//             Byte(lit) => LitValue::Int(lit.value() as u128),
//             Verbatim(lit) => panic!("Unexpected verbatim literal{:?}", lit),
//         }
//     }
// }

// // recursive evaluation of the condition
// fn evaluate_condition(condition: Box<syn::Expr>) -> LitValue {
//     match condition {
//         syn::Expr::Binary(binary) => {
//             use syn::BinOp::*;

//             // evaluate the left and right hand side of the binary expression
//             let lhs = evaluate_condition(binary.left);
//             let rhs = evaluate_condition(binary.right);

//             // evaluate the binary operator
//             match binary.op {
//                 And(_) => lhs && rhs,
//                 Or(_) => lhs || rhs,
//                 BitAnd(_) => lhs & rhs,
//                 BitOr(_) => lhs | rhs,
//                 BitXor(_) => lhs ^ rhs,
//                 Eq(_) => lhs == rhs,
//                 Ne(_) => lhs != rhs,
//                 Lt(_) => lhs < rhs,
//                 Le(_) => lhs <= rhs,
//                 Gt(_) => lhs > rhs,
//                 _ => panic!("Expected logical operator, found {:#?}", binary.op),
//             }
//         }
//         syn::Expr::Group(group) => evaluate_condition(group.expr),
//         syn::Expr::Paren(paren) => evaluate_condition(paren.expr),
//         syn::Expr::If(if_expr) => {
//             let condition = evaluate_condition(if_expr.cond);

//             if condition {
//                 evaluate_condition(if_expr.then_branch)
//             } else {
//                 evaluate_condition(if_expr.else_branch)
//             }
//         },
//         syn::Expr::If(if_expr) => {
//             let condition = evaluate_condition(if_expr.cond);
//             if condition {
//                 evaluate_condition(if_expr.then_branch)
//             } else {
//                 evaluate_condition(if_expr.else_branch)
//             }
//         },
//         syn::Expr::Unary(unary) => {
//             if let syn::UnOp::Not(_) = unary.op {
//                 !evaluate_condition(unary.expr)
//             } else {
//                 panic!("Expected unary operator, found {:#?}", unary.op)
//             }
//         }

//         _ => {
//             panic!("Expected binary expression")
//         }
//     }
// }
 */
/*//use proc_macro2::{Delimiter, Group, Ident, Punct, Spacing, Span, TokenStream, TokenTree};
use quote::quote;
use quote::ToTokens;
use std::char;
use std::iter;
use std::panic;
use syn::parse;

use std::ops::Add;
//example of add type bound

use std::{borrow::BorrowMut, collections};

use syn::{
    braced,
    ext::IdentExt,
    parse::{Parse, ParseBuffer, ParseStream, Peek},
    parse_macro_input, Arm, Ident, Pat, Token,
};

// use std::ops::Add;
// example of add type bound

// gets
// two_char_operators:helix_proc::convert_bytes_to_u16!( b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
// b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
// b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
// b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
// b"::" | b"||" | b"++" | b"__" | b"?="),

fn clean_str_slice(s: String) -> String {
    let s = s
        .trim() // remove whitespace
        .trim_start_matches("b"); // Remove the optional byte prefix

    if s.starts_with('"') {
        s.trim_matches('"')
    } else {
        s.trim_matches('\'')
    }
    .to_string()
}

fn format_definition(s: String, arguments: &str) -> String {
    format!("{}!({arguments})", s.strip_prefix("def::").unwrap())
}

fn is_definition(s: &str) -> bool {
    s.starts_with("def::")
}

fn get_first_bytes_as_int(s: String) -> u128 {
    // 128 bit integer
    let mut array: [u8; 16] = [0; 16];

    let bytes = s.as_bytes();

    // load the string into the array
    for i in 0..bytes.len() {
        array[i] = bytes[i];
    }
    unsafe { std::mem::transmute::<[u8; 16], u128>(array) }
}

fn extract_first_char(s: String) -> String {
    unsafe { s.as_ptr().read().to_string() }
}

fn expand_range(s: String, quote: char, inclusive: bool, v: &mut Vec<String>) -> Option<String> {
    let range_split = s
        .trim_matches(quote)
        .split(&format!(
            "{quote}{}{quote}",
            if inclusive { "..=" } else { ".." }
        ))
        .collect::<Vec<&str>>();

    if range_split.len() != 2 {
        return None;
    }

    let start = get_first_bytes_as_int(range_split[0].to_string());
    let end = get_first_bytes_as_int(range_split[1].to_string());

    let mut range = start..end;

    if inclusive {
        range.end += 1;
    }

    for i in range {
        v.push(i.to_string());
    }

    None
}

fn replace_escapes(s: &str) -> String {
    s.replace("\\n", "\n")
        .replace("\\r", "\r")
        .replace("\\t", "\t")
        .replace("\\0", "\0")
        .replace("\\\'", "\'")
        .replace("\\\"", "\"")
        .replace("\\\\", "\\")
        .replace("\\x", "")
}

struct LexToken {
    name: Ident,
    pattern: LexPattern,
}

trait Operator {
    fn precedence(&self) -> u8;
}



impl Parse for LexToken {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let name = input.parse()?;
        input.parse::<Token![:]>()?;
        let pattern = input.parse()?;
        Ok(Self { name, pattern })
    }
}

type TokenFields = syn::punctuated::Punctuated<LexToken, syn::token::Comma>;

struct LexTokenGroup {
    name: Ident,
    tokens: TokenFields,
}

use syn::token::Brace;
impl Parse for LexTokenGroup {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let name = input.parse()?;

        input.parse::<Token![:]>()?;

        let content;
        let lex_tokens = braced!(content in input);

        Ok(Self {
            name,
            tokens: content.parse_terminated(LexToken::parse, Token![,])?,
        })
    }
}

enum LexPattern {
    TokenGroup(Box<LexTokenGroup>),
    TokenRule(Pat),
}

impl Parse for LexPattern {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        if input.peek(Brace) {
            Ok(Self::TokenGroup(Box::new(input.parse()?)))
        } else {
            patterns.push(Pat::parse_multi_with_leading_vert(input));

            Ok(Self::TokenRuleUnion(patterns))
        }
    }
}

#[proc_macro]
pub fn define_tokens(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    todo!()
    //let
}

// #[proc_macro]
// pub fn expand_token_pattern(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
//     let s = input.to_string();

//     dbg!(input);

//     let pat = s.split_whitespace().collect::<Vec<&str>>();

//     let name = pat[0].trim();
//     let mut range_patterns = Vec::new();

//     let mut pattern = pat[2]
//         .split_whitespace()
//         .filter(|x| *x != "|" && x.len() > 0)
//         .filter_map(|x| {
//             let s = replace_escapes(x).trim().to_string();
//             dbg!(&s);
//             return match s {
//                 _ if is_definition(x) => Some(x.to_string()),
//                 _ if s.contains("\"..=\"") => expand_range(s, '"', true, &mut range_patterns),
//                 _ if s.contains("'..='") => expand_range(s, '\'', true, &mut range_patterns),
//                 _ if x.contains("\"..\"") => expand_range(s, '"', false, &mut range_patterns),
//                 _ if x.contains("'..'") => expand_range(s, '\'', false, &mut range_patterns),
//                 _ => match clean_str_slice(s) {
//                     _ if x.len() == 0 => None,
//                     m => Some(m.to_string()),
//                 },
//             };
//         })
//         .collect::<Vec<String>>();

//     pattern.extend(range_patterns);

//     let definitions = pattern
//         .clone()
//         .into_iter()
//         .filter(|x| is_definition(x))
//         .collect::<Vec<String>>();
//     dbg!(definitions.clone());

//     let mut patterns = pattern
//         .clone()
//         .into_iter()
//         .filter(|x| !is_definition(x))
//         .collect::<Vec<String>>();
//     dbg!(patterns.clone());

//     let mut num_u16 = patterns
//         .clone()
//         .into_iter()
//         .map(get_first_bytes_as_int)
//         .map(|x| x.to_string())
//         .collect::<Vec<String>>();
//     dbg!(num_u16.clone());

//     let mut num_u16_definitions = definitions
//         .clone()
//         .into_iter()
//         .map(|x| format_definition(x, "u16"))
//         .collect::<Vec<String>>();
//     dbg!(num_u16_definitions.clone());

//     let mut first_chars = patterns
//         .clone()
//         .into_iter()
//         .map(extract_first_char)
//         .collect::<Vec<String>>();
//     dbg!(first_chars.clone());

//     let mut first_char_definitions = definitions
//         .clone()
//         .into_iter()
//         .map(|x| format_definition(x, "first_char"))
//         .collect::<Vec<String>>();

//     // dedup

//     num_u16.sort();
//     num_u16.dedup();

//     num_u16_definitions.sort();
//     num_u16_definitions.dedup();

//     first_chars.sort();
//     first_chars.dedup();

//     first_char_definitions.sort();
//     first_char_definitions.dedup();

//     num_u16.extend(num_u16_definitions);
//     first_chars.extend(first_char_definitions);

//     dbg!("dedup");

//     fn escape_escapes(s: String) -> String {
//         s.replace("\n", "\\n")
//             .replace("\r", "\\r")
//             .replace("\t", "\\t")
//             .replace("\0", "\\0")
//             .replace("\'", "\\'")
//             .replace("\"", "\\\"")
//             .replace("\\", "\\\\")
//     }

//     dbg!("escape_escapes");
//     // add the byte representation of the string and char back to the pattern

//     patterns.iter_mut().for_each(|x| match x.len() {
//         _ if x.starts_with("0x") | x.bytes().into_iter().all(|m| matches!(m, b'0'..=b'9')) => {}
//         1 => *x = format!("b'{}'", escape_escapes(x.to_string())),
//         _ => *x = format!("b\"{}\"", escape_escapes(x.to_string())),
//     });

//     dbg!(patterns.clone());

//     patterns.extend(definitions);

//     format!(
//         "macro_rules! {name} {{
//     () => {{
//         {pattern}
//     }};

//     (first_char) => {{
//         {first_char}
//     }};

//     (u16) => {{
//         {num_u16}
//     }};

//     (contains $ch:expr) => {{
//         matches!($ch, {name}!())
//     }};

//     (u16 contains $ch:expr) => {{
//         matches!($ch, {num_u16})
//     }};
// }}",
//         name = name,
//         pattern = patterns.join("|"),
//         first_char = first_chars.join("|"),
//         num_u16 = num_u16.join("|")
//     )
//     .parse()
//     .unwrap()
// }

/*//use proc_macro2::{Delimiter, Group, Ident, Punct, Spacing, Span, TokenStream, TokenTree};
// use quote::quote;
// use quote::ToTokens;
// use std::char;
// use std::iter;
// use std::panic;
// use syn::parse;

// use std::ops::Add;
// example of add type bound

use std::{borrow::BorrowMut, collections};

use syn::{
    braced,
    ext::IdentExt,
    parse::{self, Parse, ParseBuffer, ParseStream, Peek},
    parse_macro_input, Arm, Ident, Pat, Token,
};

// gets
// two_char_operators:helix_proc::convert_bytes_to_u16!( b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
// b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
// b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
// b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
// b"::" | b"||" | b"++" | b"__" | b"?="),
macro_rules! pipe_split {
    () => {
        // "|" | " | " | " |"
    };
}
/*




macro_rules! token_patterns {
    ($($name:ident:  $patten:pat),*) => {
        $(
            macro_rules! $name {
                () => {
                    $patten
                };
                // convert a pattern to an expression
                ($expr:expr) => {
                    $expr
                };
                (first_char) => {
                    helix_proc::get_first_char_pattern!($patten)
                };

                (u16) => {
                    helix_proc::convert_bytes_to_u16!($patten)
                };

                (match $ch:expr) => {
                    matches!($ch, $name!())
                };

                (u16 match $ch:expr) => {
                    matches!($ch, $name!(u16))
                };

                (trie_match $ch:expr) => {
                    trie_match::trie_match!{
                        match $ch {
                            $patten => true,
                        _ => false
                    }}
                };
            }
        )*
    }

}
*/


// #[proc_macro]
// pub fn convert_pattern_to_int_pattern(input: proc_macro::TokenStream) -> proc_macro::TokenStream {

//     let pattern:Pat = parse_macro_input!(input with Pat::parse_multi);

//     match pattern.borrow_mut() {
//         Pat::Or(or) =>{

//         }
//         _ => {}
//     }

// }

// fn str_pattern_to_int_pattern(pattern: Pat) -> Pat {

// }

// #[proc_macro]
// pub fn to_byte_repr(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
//     input
//         .to_string()
//         .split(pipe_split!())
//         .map(|x| "b".to_string() + x)
//         .join("|")
//         .parse()
//         .unwrap()
// }

fn map_escape(s: &[u8]) -> &[u8] {
    match s[..1] {
        &b"\\n" => b"\n",
        &b"\\r" => b"\r",
        &b"\\t" => b"\t",
        &b"\\0" => b"\0",
        &b"\\'" => b"\'",
        &b"\\\"" => b"\"",
        &b"\\\\" => b"\\",
        &b"\\x" if s[2].is_ascii_alphanumeric() & s[3].is_ascii_alphanumeric() => unsafe {
            std::str::from_utf8_unchecked(&[s[2], s[3]])
        },
        _ => s,
    }
}



#[proc_macro]
pub fn get_first_char_pattern(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    let mut input = input
        .to_string()
        .replace('\n' | " " | '\\', "")
        .split(pipe_split!())
        .map(|x| format!("b'{}'", x.as_bytes()[2] as char))
        .collect::<Vec<String>>();

    // sort for dedup to work
    input.sort();
    input.dedup();

    input.join("|").parse().unwrap()
}

// conditional!(, const FISH: &str = "salmon" );

// #[proc_macro]
// pub fn check_if_empty(input: proc_macro::TokenStream) ->  proc_macro::TokenStream {
//     input.into_token_stream().is_empty().to_token_stream()
// }

// #[proc_macro]
// pub fn conditional_j(input: TokenStream) -> TokenStream {
//     /*
//     condition(if stringify!($has_body) == "true" { has_body: true } else { has_body: false })

//      */
//     let body: syn::ExprIf = parse(input).expect("Expected if expression");

//     match evaluate_condition(body.cond) {
//         LitValue::Bool(true) => {
//             quote! { #body.then_branch }
//         },
//         LitValue::Bool(false) => {
//             if let Some(else_branch) = body.else_branch {
//                 quote! { #else_branch }
//             } else {
//                 TokenStream::new()
//             }
//         }
//         e => panic!("Expected boolean, found the conditional evaluation: {:#?}", e),
//     }
// }

// enum LitValue {
//     Bool(bool),
//     Int(u128),
//     Float(f64),
//     Char(char),
//     Str(String),
//     BytStr(Vec<u8>),
// }

// impl From<syn::Lit> for LitValue {
//     fn from(lit: syn::Lit) -> Self {

//         use syn::Lit::*;
//         match lit {
//             Bool(lit) => LitValue::Bool(lit.value),
//             Int(lit) => LitValue::Int(lit.base10_parse().expect("Expected integer")),
//             Float(lit) => LitValue::Float(lit.base10_parse().expect("Expected float")),
//             Char(lit) => LitValue::Char(lit.value()),
//             Str(lit) => LitValue::Str(lit.value()),
//             ByteStr(lit) => LitValue::BytStr(lit.value()),
//             Byte(lit) => LitValue::Int(lit.value() as u128),
//             Verbatim(lit) => panic!("Unexpected verbatim literal{:?}", lit),
//         }
//     }
// }

// // recursive evaluation of the condition
// fn evaluate_condition(condition: Box<syn::Expr>) -> LitValue {
//     match condition {
//         syn::Expr::Binary(binary) => {
//             use syn::BinOp::*;

//             // evaluate the left and right hand side of the binary expression
//             let lhs = evaluate_condition(binary.left);
//             let rhs = evaluate_condition(binary.right);

//             // evaluate the binary operator
//             match binary.op {
//                 And(_) => lhs && rhs,
//                 Or(_) => lhs || rhs,
//                 BitAnd(_) => lhs & rhs,
//                 BitOr(_) => lhs | rhs,
//                 BitXor(_) => lhs ^ rhs,
//                 Eq(_) => lhs == rhs,
//                 Ne(_) => lhs != rhs,
//                 Lt(_) => lhs < rhs,
//                 Le(_) => lhs <= rhs,
//                 Gt(_) => lhs > rhs,
//                 _ => panic!("Expected logical operator, found {:#?}", binary.op),
//             }
//         }
//         syn::Expr::Group(group) => evaluate_condition(group.expr),
//         syn::Expr::Paren(paren) => evaluate_condition(paren.expr),
//         syn::Expr::If(if_expr) => {
//             let condition = evaluate_condition(if_expr.cond);

//             if condition {
//                 evaluate_condition(if_expr.then_branch)
//             } else {
//                 evaluate_condition(if_expr.else_branch)
//             }
//         },
//         syn::Expr::If(if_expr) => {
//             let condition = evaluate_condition(if_expr.cond);
//             if condition {
//                 evaluate_condition(if_expr.then_branch)
//             } else {
//                 evaluate_condition(if_expr.else_branch)
//             }
//         },
//         syn::Expr::Unary(unary) => {
//             if let syn::UnOp::Not(_) = unary.op {
//                 !evaluate_condition(unary.expr)
//             } else {
//                 panic!("Expected unary operator, found {:#?}", unary.op)
//             }
//         }

//         _ => {
//             panic!("Expected binary expression")
//         }
//     }
// }
 */
 */