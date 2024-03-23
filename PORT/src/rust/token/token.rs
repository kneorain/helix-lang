use std::{ collections::HashMap, fmt::Display };
use std::hash::Hash;
use pyo3::prelude::*;
use super::token_value::TokenValue;

// TODO: use super::Label;

/*
ported from python to rust ---------
def __init__(self,
def original_line(self) -> str:
def original_line(self, value: str) -> None:
def line(self) -> list[str]:
def line(self, value: list[str]) -> None:
def token(self) -> str:
def token(self, value: str) -> None:
def line_number(self) -> int:
def line_number(self, value: int) -> None:
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
#[derive(Clone, Debug)]
pub struct Token {
    // ------- Information about the token itself ------- //
    // CAN be shared between tokens (doesn't mean it will ALWAYS be shared)
    original_line: Option<String>,
    line_number: i32,
    indent_level: &'static u16,
    column: u16,

    file_name: &'static str, // WILL be shared between tokens
    // (from the same origin token created by the lexer (stage 1))

    // ------- Information about the token to be used by the builder ------- //
    value: TokenValue,

    // ------- Information about the token ------- //
    identifier: String, // change to enum
    attributes: HashMap<String, String>,
}
impl Token {
    pub fn new(
        original_line: Option<String>,
        line_number: Option<i32>,
        column: Option<u16>,
        file_name: &'static str,
        value: TokenValue,
        identifier: String,
        attributes: HashMap<String, String>
    ) -> Self {
        Self {
            original_line: original_line,
            line_number: line_number.unwrap_or(-1),
            column: column.unwrap_or(0),
            file_name: file_name,
            value: value,
            identifier: identifier,
            attributes: attributes,
            indent_level: &0,
        }
    }

    pub fn original_line(&self) -> &Option<String> {
        &self.original_line
    }

    pub fn set_original_line(&mut self, original_line: Option<String>) {
        self.original_line = original_line;
    }

    pub fn line_number(&self) -> i32 {
        self.line_number
    }

    pub fn set_line_number(&mut self, line_number: i32) {
        self.line_number = line_number;
    }

    pub fn indent_level(&self) -> &u16 {
        self.indent_level
    }

    pub fn set_indent_level(&mut self, indent_level: &'static u16) {
        self.indent_level = indent_level;
    }

    pub fn column(&self) -> u16 {
        self.column
    }

    pub fn set_column(&mut self, column: u16) {
        self.column = column;
    }

    pub fn file_name(&self) -> &'static str {
        self.file_name
    }

    pub fn set_file_name(&mut self, file_name: &'static str) {
        self.file_name = file_name;
    }

    pub fn value(&self) -> &TokenValue {
        &self.value
    }

    pub fn identifier(&self) -> &String {
        &self.identifier
    }

    pub fn set_identifier(&mut self, identifier: String) {
        self.identifier = identifier;
    }

    pub fn attributes(&self) -> &HashMap<String, String> {
        &self.attributes
    }

    pub fn set_attributes(&mut self, key: String, value: String) {
        self.attributes.insert(key, value);
    }

    pub fn set_token(&mut self, token: String) {
        self.value = TokenValue::new_token(token);
    }

    pub fn set_line(&mut self, line: Vec<String>) {
        self.value = TokenValue::new_line(line);
    }

    pub fn is_empty(&self) -> bool {
        self.value.is_line() && self.value.get_line().is_empty()
    }

    pub fn copy(&self) -> Self {
        Self {
            original_line: self.original_line.clone(),
            line_number: self.line_number,
            indent_level: self.indent_level,
            column: self.column,
            file_name: self.file_name,
            value: self.value.clone(),
            identifier: self.identifier.clone(),
            attributes: self.attributes.clone(),
        }
    }

    pub fn contains(&self, key: &Token) -> bool {
        self.value == key.value
    }
}
impl PartialEq for Token {
    fn eq(&self, other: &Self) -> bool {
        self.original_line == other.original_line &&
            self.line_number == other.line_number &&
            self.indent_level == other.indent_level &&
            self.column == other.column &&
            self.file_name == other.file_name &&
            self.value == other.value &&
            self.identifier == other.identifier &&
            self.attributes == other.attributes
    }
}
impl Eq for Token {}
impl Hash for Token {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.original_line.hash(state);
        self.line_number.hash(state);
        self.indent_level.hash(state);
        self.column.hash(state);
        self.file_name.hash(state);
        self.value.hash(state);
        self.identifier.hash(state);
        // TODO: self.attributes.hash(state);
    }
}
impl Display for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            f,
            "Token(\n\toriginal_line\t= {:?}, \n\tline_number\t= {:?}, \n\tindent_level\t= {:?}, \n\tcolumn\t= {:?}, \n\tfile_name\t= {:?}, \n\tinto\t= {:?}, \n\tidentifier\t= {:?}, \n\tattributes\t= {:?}\n)",
            self.original_line,
            self.line_number,
            self.indent_level,
            self.column,
            self.file_name,
            self.value,
            self.identifier,
            self.attributes
        )
    }
}
impl IntoIterator for Token {
    type Item = String;
    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        // retuern the iter only if the token is a line else panic
        match self.value {
            TokenValue::Line(line) => line.into_iter(),
            _ => panic!("Token is not a line"),
        }
    }
}
