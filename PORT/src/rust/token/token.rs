use std::{mem, ops};
use std::num::{NonZeroI32, NonZeroU16};
use std::panic::panic_any;
use std::sync::Arc;
use std::{ collections::HashMap, fmt::Display };
use std::hash::Hash;
use pyo3::prelude::*;
use regex::Regex;
use super::keywords::{Keyword, get_all_keywords};
use crate::panic_name;

use super::token_value::TokenValue;

// TODO: use super::Label;


#[repr(C)]
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum TokenType {
    STRING,
    CHARACTER,
    NUMERIC,
    KEYWORD,
    IDENTIFIER,
    DELIMITER,
    OPERATOR,
    COMMENT,
    OTHER,
}

//impl TokenType {
//    pub fn from_str(s: &str) -> Self {
//        if let
//            Some(token) = get_all_keywords()
//            .into_iter()
//            .find(|keyword| s == keyword
//                .to_str())
//            .map(|_| TokenType::KEYWORD)
//        {
//            return token;
//        }
//
//        let string_re     = Regex::new(r#"([fbur]*"[^"\\]*(?:\\.[^"\\]*)*")"#).unwrap();
//        let character_re  = Regex::new(r#"([fbur]*'[^'\\]*(?:\\.[^'\\]*)*')"#).unwrap();
//        let numeric_re    = Regex::new(r#"(\b\d+\.\d+\b|\b\d+[fdui]?\b)"#).unwrap();
//        let identifier_re = Regex::new(r#"(\b[a-zA-Z][a-zA-Z0-9_]*\b)"#).unwrap();
//        let delimiter_re  = Regex::new(r#"([\(\)\{\}\[\];,])"#).unwrap();
//        let operator_re   = Regex::new(r#"([+\-*/%=&|!<>^])"#).unwrap();
//        let comment_re    = Regex::new(r#"((?://[^\n]*)|(/\*[\s\S]*?\*/))"#).unwrap();
//
//        if string_re.is_match(s) {
//            return TokenType::STRING;
//        } else if character_re.is_match(s) {
//            return TokenType::CHARACTER;
//        } else if numeric_re.is_match(s) {
//            return TokenType::NUMERIC;
//        } else if identifier_re.is_match(s) {
//            return TokenType::IDENTIFIER;
//        } else if delimiter_re.is_match(s) {
//            return TokenType::DELIMITER;
//        } else if operator_re.is_match(s) {
//            return TokenType::OPERATOR;
//        } else if comment_re.is_match(s) {
//            return TokenType::COMMENT;
//        } else {
//            return TokenType::OTHER;
//        }
//    }
//}

/*
ported from python to rust ---------
def __init__(self,
def original_line(self) -> str:
def original_line(self, value: str) -> None:
def line(self) -> list[str]:
def line(self, value: list[str]) -> None:
def token(self) -> str:
def token(self, value: str) -> None:
def row(self) -> int:
def row(self, value: int) -> None:
def indent_level(self) -> int:
def indent_level(self, value: int) -> None:
def set_token(self, value: str) -> 'Token':
def __hash__(self):
def __eq__(self, other: object) -> bool:
def __contains__(self, other: Iterable) -> bool:
def __str__(self) -> str:
def __repr__(self) -> str:
def __iter__(self) -> Iterator[str]:
def is_empty(self) -> bool:
*/
#[pyclass]
#[repr(C)]
#[derive(Clone, Debug,PartialEq, Eq, Hash)]
pub struct Token {
    // ------- Meta about the token ------- //
    original_line: Arc<str>,
    file_name:     Arc<str>,
    
    row:  i32,
    col:  u16,
    
    // ------- Information about the token ------- //
    identifier: TokenType,
    token:      String,
    
    // TODO: Make the keys into an enum
    // ------- Parsed at a later stage ------- //
    attributes:    Vec<(String, String)>,
    indent_level:  u16,
}

impl Token {
    pub fn new(
        original_line: Arc<str>,
        file_name:     Arc<str>,
        row:           i32,
        col:           u16,
        token:         String,
        identifier:    TokenType,
    ) -> Self {
        Self {
            original_line,
            row: row, // changed from NonZero since the tokenizer will be a lexer and not a parser
            col: col,
            file_name,
            token,
            identifier,
            indent_level: 0,
            attributes: Vec::new(),
        }
    }

    // ========= Getters ========= //
    pub fn original_line(&self) -> &str {
        return self.original_line.as_ref();
    }

    pub fn row(&self) -> i32 {
        return self.row;
    }

    pub fn file_name(&self) -> &str{
        self.file_name.as_ref()
    }

    pub fn col(&self) -> u16 {
        return self.col;
    }

    pub fn identifier(&self) -> &TokenType {
        return &self.identifier;
    }
    
    pub fn token(&self) -> &String {
        return &self.token;
    }
    
    pub fn get_attr(&self, key: &str) -> Option<&str> {
        for (k, v) in self.attributes.iter() {
            if k == key {
                return Some(v);
            }
        }
        return None;
    }

    pub fn indent_level(&self) -> u16 {
        return self.indent_level;
    }

    // ========= Setters ========= //
    pub fn set_indent_level(&mut self, indent_level: u16) {
        self.indent_level = indent_level;
    }

    pub fn set_attr(&mut self, key: String, token: String) {
        for (k, v) in self.attributes.iter_mut() {
            if *k == key {
                *v = token;
                return;
            }
        }
        self.attributes.push((key, token));
    }

    pub fn set_token(&mut self, token: String) {
        self.token = token;
    }

    pub fn set_identifier(&mut self, identifier: TokenType) {
        self.identifier = identifier;
    }

    // ========= Methods ========= //
    pub fn is_empty(&self) -> bool {
        return self.token.is_empty();
    }

    pub fn equals_str(&self, other: &str) -> bool {
        return self.token == other;
    }

    pub fn equals_token(&self, other: &Token) -> bool {
        return self.token == other.token;
    }

    pub fn contains(&self, key: &str) -> bool {
        return self.token.contains(key);
    }
}


impl IntoIterator for Token {
    type Item = String;
    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        panic_any(TokenError::TokenIsNotLine);
    }
}


#[derive(Debug)]
pub enum TokenError {
    TokenIsNotLine,
    IllegalAccess,
}

impl Display for TokenError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        use TokenError::*;
        match self {
            TokenIsNotLine => write!(f, "Token is not a line"),
            TokenIsNotToken => write!(f, "Token is not a token"),
            IllegalAccess => write!(f, "Token has been accessed in a illegal way"),
        }
    }
}

