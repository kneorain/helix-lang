use std::fmt::Display;
use std::hash::Hash;
use std::ops::{Index, IndexMut,};

// TODO: use super::Label;

// TODO: Make into SmallVec
#[derive(Clone, Debug, Hash,PartialEq,Eq)]
pub enum TokenValue {
    Line(Vec<String>),
    Token(String),
}

use TokenValue::*;

impl TokenValue {
    pub fn new_line(line: Vec<String>) -> Self {
        return Line(line);
    }

    pub fn new_token(token: String) -> Self {
        return Token(token);
    }

    pub fn get_line(&self) -> &[String] {
        if let Line(line) = self {
            return line;
        }
        
        panic!("{}",TokenError::IllegalAccess);
    }
    
    pub fn get_line_mut(&mut self) -> &mut Vec<String> {
        if let Line(line) = self {
            return line;
        }
        
        panic!("{}",TokenError::IllegalAccess);
    }

    pub fn len (&self) -> usize {
        match self {
            Line(line) => line.len(),
            Token(s) => s.len(),
        }
    }

    pub fn get_token(&self) -> &str {
        if let Token(token) = self {
            return token;
        }
        
        panic!("{}",TokenError::IllegalAccess);
    }

    pub fn set_line(&mut self, line: Vec<String>) {
        *self = Line(line);
    }

    pub fn set_token(&mut self, token: String) {
        *self = Token(token);
    }

    pub fn is_line(&self) -> bool {
        match self {
            Line(_) => true,
            _ => false,
        }
    }

    pub fn is_token(&self) -> bool {
        match self {
            Token(_) => true,
            _ => false,
        }
    }
}

use super::TokenError;

impl Index<usize> for TokenValue {
    type Output = String;

    fn index(&self, index: usize) -> &Self::Output {
        if let Line(line) = self {
            return &line[index];
        }

        panic!("{}", TokenError::IllegalAccess);
    }
}

impl IndexMut<usize> for TokenValue {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        if let Line(line) = self {
            return &mut line[index];
        }

        panic!("{}", TokenError::IllegalAccess);
    }
}

