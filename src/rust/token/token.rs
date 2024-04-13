use pyo3::prelude::*;
use std::hash::Hash;
use std::panic::panic_any;
use std::sync::Arc;
use std::fmt::Display;

// TODO: use super::Label;

#[repr(C)]
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum Ident {
    Keyword,
    Identifier,
}

#[pyclass]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct TokenList {
    tokens:    Vec<Token>,
    file_name: Arc<str>,
}

#[pyclass]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct Token {
    // ------- Meta about the token ------- //
    // Removed original_line since we are storing row and col
    // hence we can get the line from the file
    // original_line: Arc<str>,
    row: i32,
    col: u16,

    // ------- Information about the token ------- //
    identifier: Ident,
    token:     String,

    // ------- Parsed at a later stage ------- //
    attributes:  Option<Vec<(String, String)>>, // TODO: Make the keys into an enum
    scope_depth: Option<u16>,
}

impl Token {
    pub fn new(
        row:           i32,
        col:           u16,
        token:         String,
        identifier:    Ident,
    ) -> Self {
        Self {
            row, // changed from NonZero since the tokenizer will be a lexer and not a parser
            col, // changed from NonZero since the tokenizer will be a lexer and not a parser
            token,
            identifier,
            scope_depth: None,
            attributes:  None,
        }
    }

    // ========= Getters ========= //

    pub fn row(&self) -> i32 {
        self.row
    }

    pub fn col(&self) -> u16 {
        self.col
    }

    pub fn identifier(&self) -> &Ident {
        &self.identifier
    }

    pub fn token(&self) -> &String {
        &self.token
    }

    pub fn get_attr(&self, key: &str) -> Option<&str> {
        if let Some(attributes) = &self.attributes {
            for (k, v) in attributes.iter() {
                if k == key {
                    return Some(v);
                }
            }
        } else {
            panic_any(TokenError::IllegalAccess);
        }
        return None;
    }

    pub fn scope_depth(&self) -> u16 {
        if let Some(scope_depth) = self.scope_depth {
            return scope_depth
        } else {
            panic_any(TokenError::IllegalAccess);
        }
    }

    // ========= Setters ========= //
    pub fn set_scope_depth(&mut self, scope_depth: u16) {
        self.scope_depth = Some(scope_depth);
    }

    pub fn set_attr(&mut self, key: String, token: String) {
        if self.attributes.is_none() {
            self.attributes = Some(Vec::new());
        }

        let attributes = self.attributes.as_mut().unwrap();

        for (k, v) in attributes.iter_mut() {
            if *k == key {
                *v = token;
                return;
            }
        }
        attributes.push((key, token));
    }

    pub fn set_token(&mut self, token: String) {
        self.token = token;
    }

    pub fn set_identifier(&mut self, identifier: Ident) {
        self.identifier = identifier;
    }

    // ========= Methods ========= //
    pub fn is_empty(&self) -> bool {
        self.token.is_empty()
    }

    pub fn equals_str(&self, other: &str) -> bool {
        self.token == other
    }

    pub fn equals_token(&self, other: &Token) -> bool {
        self.token == other.token
    }

    pub fn contains(&self, key: &str) -> bool {
        self.token.contains(key)
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
    InvalidKeyword(Box<str>),
}

impl Display for TokenError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        use TokenError::*;
        match self {
            TokenIsNotLine => write!(f, "Token is not a line"),
            IllegalAccess => write!(f, "Token has been accessed in a illegal way"),
            InvalidKeyword(s) => write!(f, "Invalid keyword {s}"),
        }
    }
}
