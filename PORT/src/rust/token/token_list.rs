use std::fmt::Display;
use std::hash::Hash;
use pyo3::prelude::*;
use super::token::Token;

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
#[derive(Clone, Debug)]
struct TokenList {
    line: Vec<Token>,
    indent_level: u16,
    file: &'static str,
}
impl TokenList {
    #[allow(dead_code)] #[allow(dead_code)] pub fn new(line: Vec<Token>, indent_level: u16, file: &'static str) -> Self {
        Self {
            line: line,
            indent_level: indent_level,
            file: file,
        }
    }

    #[allow(dead_code)] pub fn line(&self) -> &Vec<Token> {
        &self.line
    }

    #[allow(dead_code)] pub fn indent_level(&self) -> u16 {
        self.indent_level
    }

    #[allow(dead_code)] pub fn file(&self) -> &'static str {
        self.file
    }

    #[allow(dead_code)] pub fn copy(&self) -> Self {
        Self {
            line: self.line.clone(),
            indent_level: self.indent_level,
            file: self.file,
        }
    }

    #[allow(dead_code)] pub fn find_line_number(&self, token: &str) -> i32 {
        for line in &self.line {
            if token == line.value().get_token() {
                return line.line_number();
            }
        }
        return -1;
    }

    #[allow(dead_code)] pub fn contains(&self, key: &Token) -> bool {
        self.line.iter().any(|token| token.contains(key))
    }

    #[allow(dead_code)] pub fn contains_from(&self, key: &Token) -> Vec<Token> {
        self.line
            .iter()
            .filter(|token| token.contains(key))
            .cloned()
            .collect()
    }

    #[allow(dead_code)] pub fn full_line(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                if token == line.value().get_token() {
                    found = true;
                }
                if found {
                    return Some(line.clone());
                }
                return None;
            })
            .collect()
    }

    #[allow(dead_code)] pub fn get_all_after(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                if found {
                    return Some(line.clone());
                }
                if token == line.value().get_token() {
                    found = true;
                }
                return None;
            })
            .collect()
    }

    #[allow(dead_code)] pub fn get_all_before(&self, token: &str) -> Vec<Token> {
        let mut found = false;
        self.line
            .iter()
            .filter_map(|line| {
                if token == line.value().get_token() {
                    found = true;
                }
                if found {
                    return Some(line.clone());
                }
                return None;
            })
            .collect()
    }

    #[allow(dead_code)] pub fn get_between(&self, start: &str, end: &str) -> Vec<Token> {
        let mut start_index = 0;
        let mut end_index = 0;
        let mut count = 0;

        self.line
            .iter()
            .enumerate()
            .filter_map(|(i, line)| {
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

    #[allow(dead_code)] pub fn count(&self, value: &str) -> usize {
        let mut count = 0;
        for token in &self.line {
            if value == token.value().get_token() {
                count += 1;
            }
        }

        return count;
    }

    #[allow(dead_code)] pub fn split(&self, value: &str) -> Vec<TokenList> {
        let mut output = Vec::new();
        let mut temp = Vec::new();
        for token in &self.line {
            if value == token.value().get_token() {
                output.push(TokenList::new(temp, self.indent_level, self.file));
                temp = Vec::new();
            } else {
                temp.push(token.clone());
            }
        }
        if !temp.is_empty() {
            output.push(TokenList::new(temp, self.indent_level, self.file));
        }
        return output;
    }

    #[allow(dead_code)] pub fn splice(&self, start: usize, end: Option<usize>) -> TokenList {
        let mut temp = self.copy();
        temp.line = temp.line[start..end.unwrap_or(temp.line.len())].to_vec();
        return temp;
    }

    #[allow(dead_code)] pub fn append(&mut self, value: Token) {
        self.line.push(value);
    }

    #[allow(dead_code)] pub fn replace(&mut self, old: &str, new: &str) {
        self.line.iter_mut().for_each(|token| {
            if old == token.value().get_token() {
                token.set_token(new.to_string());
            }
        });
    }

    #[allow(dead_code)] pub fn remove(&mut self, value: &str) {
        self.line.retain(|token| value != token.value().get_token());
    }

    #[allow(dead_code)] pub fn index(&self, value: &str) -> usize {
        self.line
            .iter()
            .position(|token| value == token.value().get_token())
            .unwrap()
    }

    #[allow(dead_code)] pub fn len(&self) -> usize {
        self.line.len()
    }

    #[allow(dead_code)] pub fn get(&self, index: usize) -> Token {
        self.line[index].clone()
    }

    #[allow(dead_code)] pub fn set(&mut self, index: usize, value: Token) {
        self.line[index] = value;
    }

    #[allow(dead_code)] pub fn iter(&self) -> std::slice::Iter<Token> {
        self.line.iter()
    }

    #[allow(dead_code)] pub fn iter_mut(&mut self) -> std::slice::IterMut<Token> {
        self.line.iter_mut()
    }
}
impl Hash for TokenList {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.line.hash(state);
        self.indent_level.hash(state);
    }
}
impl PartialEq for TokenList {
    fn eq(&self, other: &Self) -> bool {
        self.line == other.line && self.indent_level == other.indent_level
    }
}
impl Eq for TokenList {}
impl IntoIterator for TokenList {
    type Item = Token;
    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        self.line.into_iter()
    }
}
impl Display for TokenList {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            f,
            "TokenList(\n\tline\t= {:?}, \n\tindent_level\t= {:?}, \n\tfile\t= {:?}\n)",
            self.line,
            self.indent_level,
            self.file
        )
    }
}
