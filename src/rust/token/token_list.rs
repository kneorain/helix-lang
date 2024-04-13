#[deprecated = "This module is not required when using an AST and a lexer/parser."]
/// # Deprecated
/// This module is marked as deprecated because it is not required when using an AST and a
/// lexer/parser. This is a remnant of the old codebase and will not be used in
/// the current implementation.

use super::token::Token;
use pyo3::prelude::*;
use std::hash::Hash;
use std::sync::Arc;

// TODO: use super::Label;

/*
ported from python to rust ---------
def __init__(self, tokens: list[Token], indent_level: int, file: str):
def __str__(self):
def __iter__(self) -> Iterator[Token]:
def __hash__(self) -> int:
def __eq__(self, other) -> bool:
def __len__(self) -> int:
def __repr__(self) -> str:
def __getitem__(self, index: int) -> Token:
def __setitem__(self, index: int, value: Token) -> None:
def remove(self, __value: str) -> None:
def index(self, __value: str) -> int:
def find_line_number(self, token: str) -> int:
def __contains__(self, __key: object | Iterable[Token_List]) -> bool:
def contains_from(self, __key: object | Iterable[Token_List]) -> str:
def full_line(self) -> str:
def get_all_after(self, token: str) -> list[Token]:
def get_all_before(self, token: str) -> list[Token]:
def get_between(self, start: str, end: str) -> list[Token]:
def copy(self) -> 'Token_List':
def count(self, __value: str) -> int:
def split(self, __value: str) -> list['Token_List']:
def splice(self, start: int = 0, end: Optional[int] = None) -> 'Token_List':
def append(self, __value: Token | str) -> None:
def replace(self, __old: str, __new: str) -> 'Token_List':
*/

#[pyclass]
#[repr(C)]
#[derive(Clone, Debug, Hash, PartialEq, Eq)]
#[deprecated]
pub struct TokenList {
    line:         Vec<Token>,
    indent_level: Arc<u16>,
    file:         Arc<str>,
}

#[allow(dead_code)]
#[deprecated = "This module is not required when using an AST and a lexer/parser."]
impl TokenList {
    /// Creates a new `TokenList` with the given line, indent level, and file.
    #[deprecated = "This module is not required when using an AST and a lexer/parser."]
    pub fn new(line: Vec<Token>, indent_level: Arc<u16>, file: Arc<str>) -> Self {
        Self {
            line,
            indent_level,
            file,
        }
    }

    /// Returns a reference to the line of tokens in the `TokenList`.
    pub fn line(&self) -> &[Token] {
        &self.line
    }

    /// Returns a reference to the indent level of the `TokenList`.
    pub fn indent_level(&self) -> &u16 {
        self.indent_level.as_ref()
    }

    /// Returns a reference to the file of the `TokenList`.
    pub fn file(&self) -> &str {
        self.file.as_ref()
    }

    /// Checks if the `TokenList` contains a token with the given key.
    pub fn contains_str(&self, key: &str) -> bool {
        self.line.iter().any(|token| key == token.token())
    }

    /// Returns the full line of tokens as a string.
    pub fn full_line(&self) -> String {
        let mut found = false;
        self.line
            .iter()
            .map(|token| token.token())
            .fold(String::new(), |acc, token| {
                match found {
                    true => acc,
                    false if token == "\n" => {
                        found = true;
                        acc
                    }
                    false => acc + token + " ",
                }
            })
    }

    /// Returns all tokens after the given token.
    pub fn get_all_after(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                match found {
                    true => return Some(line.clone()),
                    false if token == line.token() => {
                        found = true;
                        None
                    }
                    _ => None
                }
            })
            .collect()
    }

    /// Returns all tokens before the given token.
    pub fn get_all_before(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                match found {
                    true => Some(line.clone()),
                    false if token == line.token() => {
                        found = true;
                        return None;
                    }
                    false => None,
                }
            })
            .collect()
    }

    /// Returns all tokens between the start and end tokens.
    pub fn get_between(&self, start: &str, end: &str) -> Vec<Token> {
        let mut start_index = 0;
        let mut end_index = 0;
        let mut count = 0;

        self.line
            .iter()
            .enumerate()
            .filter_map(|(i, line)| {
                if start == line.token() && count == 0 {
                    start_index = i;
                    count += 1;
                } else if start == line.token() && count > 0 {
                    count += 1;
                }

                if end == line.token() {
                    count -= 1;
                    if count == 0 {
                        end_index = i;
                        return Some(line.clone());
                    }
                }
                None
            })
            .collect()
    }

    /// Returns the number of occurrences of the given value in the `TokenList`.
    pub fn count(&self, value: &str) -> usize {
        let mut count = 0;
        for token in &self.line {
            if value == token.token() {
                count += 1;
            }
        }
        count
    }

    /// Splits the `TokenList` into multiple `TokenList` instances based on the given value.
    pub fn split(&self, value: &str) -> Vec<TokenList> {
        let temp = self.clone();
        let mut split = Vec::new();
        let mut start = 0;

        for (i, token) in temp.line.iter().enumerate() {
            if value == token.token() {
                split.push(temp.splice(start, Some(i)));
                start = i + 1;
            }
        }

        split.push(temp.splice(start, None));
        split
    }

    /// Splits the `TokenList` into multiple `Token` instances based on the given value.
    pub fn split_line(&self, value: &str) -> Vec<Token> {
        let temp = self.clone();
        let mut split = Vec::new();
        let mut start = 0;

        for (i, token) in temp.line.iter().enumerate() {
            if value == token.token() {
                split.extend(temp.splice(start, Some(i)).line);
                start = i + 1;
            }
        }

        split.extend(temp.splice(start, None).line);
        split
    }

    /// Removes a range of tokens from the `TokenList` and returns them as a new `TokenList`.
    pub fn splice(&self, start: usize, end: Option<usize>) -> TokenList {
        let mut temp = self.clone();
        temp.line = temp.line[start..end.unwrap_or(temp.line.len())].to_vec();
        temp
    }

    /// Removes a range of tokens from the `TokenList` and returns them as a vector of `Token`.
    pub fn splice_line(&self, start: usize, end: Option<usize>) -> Vec<Token> {
        self.splice(start, end).line
    }

    /// Appends a token to the end of the `TokenList`.
    pub fn append(&mut self, value: Token) {
        self.line.push(value);
    }

    /// Replaces all occurrences of the old token with the new token.
    pub fn replace(&mut self, old: &str, new: &str) {
        self.line.iter_mut().for_each(|token| {
            if old == token.token() {
                token.set_token(new.to_string());
            }
        });
    }

    /// Removes all occurrences of the given token from the `TokenList`.
    pub fn remove(&mut self, value: &str) {
        self.line.retain(|token| value != token.token());
    }

    /// Returns the index of the first occurrence of the given token in the `TokenList`.
    pub fn index(&self, value: &str) -> usize {
        self.line
            .iter()
            .position(|token| value == token.token())
            .unwrap()
    }

    /// Returns the number of tokens in the `TokenList`.
    pub fn len(&self) -> usize {
        self.line.len()
    }

    /// Returns the token at the given index in the `TokenList`.
    pub fn get(&self, index: usize) -> Token {
        self.line[index].clone()
    }

    /// Sets the token at the given index in the `TokenList`.
    pub fn set(&mut self, index: usize, value: Token) {
        self.line[index] = value;
    }

    /// Returns an iterator over the tokens in the `TokenList`.
    pub fn iter(&self) -> std::slice::Iter<Token> {
        self.line.iter()
    }

    /// Returns a mutable iterator over the tokens in the `TokenList`.
    pub fn iter_mut(&mut self) -> std::slice::IterMut<Token> {
        self.line.iter_mut()
    }
}

impl IntoIterator for TokenList {
    type Item = Token;
    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        self.line.into_iter()
    }
}
