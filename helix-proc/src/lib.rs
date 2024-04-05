use proc_macro2::{Delimiter, Group, Ident, Punct, Spacing, Span, TokenStream, TokenTree};
use quote::quote;
use quote::ToTokens;
use std::char;
use std::iter;
use std::panic;
use syn::parse;


use std::ops::Add;
// example of add type bound 

// gets
// two_char_operators:helix_proc::convert_bytes_to_u16!( b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
// b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
// b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
// b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
// b"::" | b"||" | b"++" | b"__" | b"?="),


#[proc_macro]
pub fn convert_bytes_to_u16(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    input.to_string().replace("\n", "").split(" | ").map(|x| {
        // parse the byte string to a string
        let s = x.parse::<String>().unwrap();
        
        // remove the first and last character
        let s = s[1..s.len()-1].as_bytes();

        let s:[u8; 2] = [s[0], s[1]];

        format!("{}",unsafe { std::mem::transmute::<[u8; 2], u16>(s)})     
    }).collect::<Vec<String>>().join(" | ").parse().unwrap()
}


#[proc_macro]
pub fn get_first_char_pattern(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    let mut input = input.to_string().replace("\n", "").split(" | ").map(|x| {
        let first_char = x.chars().next().unwrap();
        format!("b'{}'", first_char)
    }).collect::<Vec<String>>();
    
    input.dedup();
    
    input.join(" | ").parse().unwrap()
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
