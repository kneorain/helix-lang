use std::fmt::Display;
use std::hash::Hash;

// TODO: use super::Label;


#[derive(Clone, Debug, Hash)]
pub enum TokenValue {
    Line(Vec<String>),
    Token(String),
}
impl TokenValue {
    pub fn new_line(line: Vec<String>) -> Self {
        return Self::Line(line);
    }

    pub fn new_token(token: String) -> Self {
        return Self::Token(token);
    }

    pub fn get_line(&self) -> &Vec<String> {
        match self {
            Self::Line(line) => line,
            _ => panic!("Token has been accessed in a illegal way"),
        }
    }

    pub fn get_token(&self) -> &String {
        match self {
            Self::Token(token) => token,
            _ => panic!("Token has been accessed in a illegal way"),
        }
    }

    pub fn set_line(&mut self, line: Vec<String>) {
        *self = Self::Line(line);
    }

    pub fn set_token(&mut self, token: String) {
        *self = Self::Token(token);
    }

    pub fn is_line(&self) -> bool {
        match self {
            Self::Line(_) => true,
            _ => false,
        }
    }

    pub fn is_token(&self) -> bool {
        match self {
            Self::Token(_) => true,
            _ => false,
        }
    }
}
impl PartialEq for TokenValue {
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (Self::Line(line1), Self::Line(line2)) => line1 == line2,
            (Self::Token(token1), Self::Token(token2)) => token1 == token2,
            _ => false,
        }
    }
}
impl Eq for TokenValue {}
impl Display for TokenValue {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            Self::Line(line) => write!(f, "Line({:?})", line),
            Self::Token(token) => write!(f, "Token({:?})", token),
        }
    }
}
