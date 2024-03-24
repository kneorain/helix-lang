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
struct TokenList {
    line: Vec<Token>,
    indent_level: u16,
    file: Arc<str>,
}
// TODO: If this is all just in-place getting of betweens this can easily be all done inplace with a single iterator getting chunked up,
// all of the functions that return using .collect can return a Filter or FilterMap (depending of use case)
// as it would be more efficient and less memory intensive than collecting into a vector and then returning that vector
// leading to less unnecessary allocations and deallocations
// contains_from, full_line, get_all_after,get_all_before,get_between
// can all be converted to this format

#[allow(dead_code)]
impl TokenList {
    pub fn new(line: Vec<Token>, indent_level: u16, file: Arc<str>) -> Self {
        Self {
            line,
            indent_level,
            file,
        }
    }

    pub fn line(&self) -> &[Token] {
        &self.line
    }

    pub fn indent_level(&self) -> u16 {
        self.indent_level
    }

    pub fn file(&self) -> &str {
        self.file.as_ref()
    }

    pub fn find_line_number(&self, token: &str) -> i32 {
        for line in &self.line {
            if token == line.value().get_token() {
                return line.line_number();
            }
        }
        return -1;
    }

    pub fn contains(&self, key: &Token) -> bool {
        self.line.iter().any(|token| token.contains(key))
    }

    pub fn contains_from(&self, key: &Token) -> Vec<Token> {
        self.line
            .iter()
            .filter_map(|token| match token.contains(key) {
                true => Some(token.clone()),
                false => None,
            })
            .collect()
    }

    pub fn full_line(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                match found {
                    true=> Some(line.clone()),
                    false if token == line.value().get_token()=> {
                        found = true;
                        return Some(line.clone());
                    }
                    false => None,
                } 
            })
            .collect()
    }

    pub fn get_all_after(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                match found {
                    true => return Some(line.clone()), // find a way to return a reference
                    false if token == line.value().get_token() => {found = true;None},
                    _ => None
                }
            })
            .collect()
    }

    pub fn get_all_before(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                match found {
                    true => Some(line.clone()), // find a way to return a reference
                    false if token == line.value().get_token() => {
                        found = true;
                        return None;
                    }
                    false => None,
                }
            })
            .collect()
    }

    pub fn get_between(&self, start: &str, end: &str) -> Vec<Token> {
        let mut start_index = 0;
        let mut end_index = 0;
        let mut count = 0;

        self.line
            .iter()
            .enumerate()
            .filter_map(|(i, line)| {

                // match start == line.value().get_token() && count == 0 {
                //     true => {
                //         start_index = i;
                //         count += 1;
                //     }
                //     false if start == line.value().get_token() && count > 0 => {
                //         count += 1;
                //     }
                //     false => {}
                // }


                if start == line.value().get_token() && count == 0 {
                    start_index = i;
                    count += 1;
                } else if start == line.value().get_token() && count > 0 {
                    count += 1;
                }

                if end == line.value().get_token() {
                    count -= 1;
                    if count == 0 {
                        end_index = i;
                        return Some(line.clone());
                    }
                }
                return None;
            })
            .collect()
    }

    pub fn count(&self, value: &str) -> usize {
        let mut count = 0;
        for token in &self.line {
            if value == token.value().get_token() {
                count += 1;
            }
        }

        return count;
    }

    pub fn split(&self, value: &str) -> Vec<TokenList> {
        let mut output = Vec::new();
        let mut temp = Vec::new();
        for token in &self.line {
            if value == token.value().get_token() {
                output.push(TokenList::new(temp, self.indent_level, self.file.clone()));
                temp = Vec::new();
            } else {
                temp.push(token.clone());
            }
        }
        if !temp.is_empty() {
            output.push(TokenList::new(temp, self.indent_level, self.file.clone()));
        }
        return output;
    }

    pub fn splice(&self, start: usize, end: Option<usize>) -> TokenList {
        let mut temp = self.clone();
        temp.line = temp.line[start..end.unwrap_or(temp.line.len())].to_vec();
        return temp;
    }

    pub fn append(&mut self, value: Token) {
        self.line.push(value);
    }

    pub fn replace(&mut self, old: &str, new: &str) {
        self.line.iter_mut().for_each(|token| {
            if old == token.value().get_token() {
                token.set_token(new.to_string());
            }
        });
    }

    pub fn remove(&mut self, value: &str) {
        self.line.retain(|token| value != token.value().get_token());
    }

    pub fn index(&self, value: &str) -> usize {
        self.line
            .iter()
            .position(|token| value == token.value().get_token())
            .unwrap()
    }

    pub fn len(&self) -> usize {
        self.line.len()
    }

    pub fn get(&self, index: usize) -> Token {
        self.line[index].clone()
    }

    pub fn set(&mut self, index: usize, value: Token) {
        self.line[index] = value;
    }

    pub fn iter(&self) -> std::slice::Iter<Token> {
        self.line.iter()
    }

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
