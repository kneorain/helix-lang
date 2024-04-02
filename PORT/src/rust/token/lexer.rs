use super::Token;

// lazy_static::lazy_static! {
//     static ref STRING_RE: Regex = Regex::new(r#"([fbur]*"[^"\\]*(?:\\.[^"\\]*)*")"#).unwrap();
//     static ref CHARACTER_RE: Regex = Regex::new(r#"([fbur]*'[^'\\]*(?:\\.[^'\\]*)*')"#).unwrap();
//     static ref NUMERIC_RE: Regex = Regex::new(r#"(\b\d+\.\d+\b|\b\d+[fdui]?\b)"#).unwrap();
//     static ref IDENTIFIER_RE: Regex = Regex::new(r#"(\b[a-zA-Z][a-zA-Z0-9_]*\b)"#).unwrap();
//     static ref DELIMITER_RE: Regex = Regex::new(r#"([\(\)\{\}\[\];,])"#).unwrap();
//     static ref OPERATOR_RE: Regex = Regex::new(r#"([+\-*/%=&|!<>^])"#).unwrap();
//     static ref COMMENT_RE: Regex = Regex::new(r#"((?://[^\n]*)|(/\*[\s\S]*?\*/))"#).unwrap();
// }

// make an interface for a lexer

pub trait Lexer {
    fn lexer    (&self, file:    &str) -> Vec<Token>;
    fn lexer_str(&self, content: &str) -> Vec<Token>;
}

trait Tokenizer {
    fn determine_size(&self, content: &str) -> usize;
}