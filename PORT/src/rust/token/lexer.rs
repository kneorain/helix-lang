use std::{iter::Peekable, ops::ControlFlow, slice};
use smallvec::{smallvec, SmallVec};
use core::str::Chars;

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

#[derive(Debug, Clone)]
pub struct Tokenizer {
    chars: Peekable<Chars<'static>>,
    column: usize,
    row: usize,
    tokens: SmallVec<[String; 32]>,
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct TokenIR {
    token: &'static str,
    column: usize,
    row: usize,
}

impl TokenIR {
    pub fn new(token: &[u8], column: usize, row: usize) -> Self {
        let column = column.saturating_sub(token.len()); // + (1);
            // FIXME: more testing is needed to determine if this is the
            // correct way to calculate the column since the +1 is
            // a hack to fix the column being off by one.
        let ptr = token.as_ptr() as *const u8;
        let token = std::str::from_utf8(unsafe { slice::from_raw_parts(ptr, token.len()) }).unwrap();

        TokenIR {
            token,
            column,
            row,
        }
    }
}

lazy_static::lazy_static! {
    static ref MULTI_CHAR_OPERATORS: SmallVec<[SmallVec<[char; 0]>; 0]> = smallvec![
        smallvec!['=', '=', '='],
        smallvec!['!', '=', '='],
        smallvec!['.', '.', '.'],
        smallvec!['r', '/', '/'],
        smallvec!['r', '*', '*'],
        smallvec!['r', '<', '<'],
        smallvec!['r', '>', '>'],
        smallvec!['/', '/', '='],
        smallvec!['*', '*', '='],
        smallvec!['<', '<', '='],
        smallvec!['>', '>', '='],
        smallvec!['?', '?',],
        smallvec!['|', ':',],
        smallvec!['=', '=',],
        smallvec!['!', '=',],
        smallvec!['<', '=',],
        smallvec!['>', '=',],
        smallvec!['/', '/',],
        smallvec!['*', '*',],
        smallvec!['<', '<',],
        smallvec!['>', '>',],
        smallvec!['r', '+',],
        smallvec!['r', '-',],
        smallvec!['r', '*',],
        smallvec!['r', '/',],
        smallvec!['r', '%',],
        smallvec!['r', '&',],
        smallvec!['r', '|',],
        smallvec!['r', '^',],
        smallvec!['+', '=',],
        smallvec!['-', '=',],
        smallvec!['*', '=',],
        smallvec!['/', '=',],
        smallvec!['%', '=',],
        smallvec!['&', '=',],
        smallvec!['|', '=',],
        smallvec!['^', '=',],
        smallvec!['=', '=',],
        smallvec!['=', '>',],
        smallvec!['@', '=',],
        smallvec!['-', '>',],
        smallvec!['<', '-',],
        smallvec!['<', '=',],
        smallvec!['>', '=',],
        smallvec!['&', '&',],
        smallvec!['-', '-',],
        smallvec![':', ':',],
        smallvec!['|', '|',],
        smallvec!['+', '+',],
        smallvec!['_', '_',],
        smallvec!['?', '=',],
    ];

    static ref ALLOWED_STRING_PREFIXES: SmallVec<[char; 4]> = smallvec!['r', 'b', 'u', 'f'];
}

impl Tokenizer {
    pub fn new(content: &'static str) -> Self {
        Tokenizer {
            chars: content.chars().peekable(),
            column: 0,
            row: 0,
            tokens: SmallVec::new(),
        }
    }

    /// dirty estimate of the number of tokens in the content
    pub fn fast_estimate_number_of_tokens(content: &str) -> usize {
        let mut count = 0;
        let mut in_string = false;
        let mut prev_char = '\0';

        for c in content.chars() {
            if in_string {
                if c == '"' && prev_char != '\\' {  // Handle string closure and escape character
                    in_string = false;
                }
            } else {
                if c == '"' {  // Handle string opening
                    in_string = true;
                    count += 1; // Count the entire string as one token
                } else if c.is_alphanumeric() || c == '_' || c.is_ascii_punctuation() {
                    count += 1;
                }
            }
            prev_char = c;
        }
        count
    }

    pub fn gather_all_tokens(tokenizer: &mut Self, _content: &str) -> Vec<TokenIR> {
        let mut tokens = Vec::new();

        loop {
            let token = tokenizer.next();
            if !token.token.is_empty() {
                tokens.push(token);
            } else {
                break;
            }
        }

        tokens
    }

    #[inline]
    pub fn next(&mut self) -> TokenIR {
        let mut token: Vec<u8> = Vec::new();
        
        while let Some(&ch) = self.chars.peek() {
            if ch.is_whitespace() {
                if ch == '\n' {
                    self.row += 1;
                    self.column = 0;
                } else {
                    self.column += 1;
                }

                self.chars.next();
                if !token.is_empty() {
                    break;
                }
                continue;
            }

            // Check if the next characters are a multi-character operator
            if MULTI_CHAR_OPERATORS.iter().any(|operator| operator[0] == ch) {
                if let Some(operator) = MULTI_CHAR_OPERATORS.iter().find(|&operator| {
                    operator.iter().enumerate().all(|(i, &c)| {
                        if let Some(ch) = self.chars.clone().nth(i) {
                            c == ch
                        } else {
                            false
                        }
                    })
                }) {
                    for _ in 0..operator.len() {
                        token.push(self.chars.next().unwrap() as u8);
                        self.column += 1;
                    }
                    break; // Break out of "while let Some(&ch) = self.chars.peek() { ... }"
                }
            }
            
            // Handle single character tokens
            match ch {
                '{' | '}' | '(' | ')' | ';' | '!' | '=' | '|' => {
                    if let ControlFlow::Break(_) = self.process_delimiter(&mut token) {
                        break;
                    }
                }
                '\'' | '"' => {
                    if let ControlFlow::Break(_) = self.process_string(&mut token, ch) {
                        break;
                    }
                }
                _ => {
                    if let ControlFlow::Break(_) = self.process_char(ch, &mut token) {
                        continue;
                    }
                }
            }
        }
    
        let return_val = TokenIR::new(
            &token,
            self.column,
            self.row);
        return_val
    }

    fn process_char(&mut self, ch: char, token: &mut Vec<u8>) -> ControlFlow<()> {
        if ALLOWED_STRING_PREFIXES.contains(&ch) && (*self.chars.peek().unwrap() == '"' || *self.chars.peek().unwrap() == '\'') {
            token.push(ch as u8);
            self.column += 1;
            return ControlFlow::Break(());
        }
        token.push(self.chars.next().unwrap() as u8);
        self.column += 1;
        // if theres a string prefix like r, b, u, f and a " or ' then we need to handle it
    
    
        ControlFlow::Continue(())
    }
    
    fn process_delimiter(&mut self, token: &mut Vec<u8>) -> ControlFlow<()> {
        if token.is_empty() {
            token.push(self.chars.next().unwrap() as u8);
            self.column += 1;
        }
        return ControlFlow::Break(());
    }
    
    #[inline]
    fn process_string(&mut self, token: &mut Vec<u8>, ch: char) -> ControlFlow<()> {
        if !token.is_empty() && !(token.ends_with(&[ALLOWED_STRING_PREFIXES[0] as u8]) || token.ends_with(&[ALLOWED_STRING_PREFIXES[1] as u8]) || token.ends_with(&[ALLOWED_STRING_PREFIXES[2] as u8]) || token.ends_with(&[ALLOWED_STRING_PREFIXES[3] as u8])) {
            return ControlFlow::Break(());
        }
        let quote_char = ch;
        token.push(self.chars.next().unwrap() as u8);
        self.column += 1;
        let mut is_escaped = false;
        // Push the starting quote
        while let Some(&c) = self.chars.peek() {
            if c == '\n' {
                self.row += 1;
            }
    
            if c == '\\' && !is_escaped {
                is_escaped = true;
                token.push(self.chars.next().unwrap() as u8);
                self.column += 1;
                continue;
            }
            if c == quote_char && !is_escaped {
                token.push(self.chars.next().unwrap() as u8);
                self.column += 1;
                break;
            }
            is_escaped = false;
            token.push(self.chars.next().unwrap() as u8);
            self.column += 1;
        }
        ControlFlow::Continue(())
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_determine_tokens() {
        let content =
"fn === main() {
            println!(\"Hello,
            world!\");
            \"Hello; \\\" world!\"
            if true != false {
                let xyz_99_yoMama = 5 | b\"some\" | 'c';
            }
        }";

        let mut tokenizer = Tokenizer::new(content);

        let excepeted = [
            "fn",
            "===",
            "main",
            "(",
            ")",
            "{",
            "println",
            "!",
            "(",
            "\"Hello,\n            world!\"",
            ")",
            ";",
            "\"Hello; \\\" world!\"",
            "if",
            "true",
            "!=",
            "false",
            "{",
            "let",
            "xyz_99_yoMama",
            "=",
            "5",
            "|",
            "b\"some\"",
            "|",
            "'c'",
            ";",
            "}",
            "}",
        ];

        for index in 0..excepeted.len() {
            
            let start = std::time::Instant::now();
            let token = tokenizer.next();
            let elapsed = start.elapsed();
            println!("r:{} c:{} t:{} e:{:?}", token.row, token.column, token.token, elapsed);
            assert_eq!(token.token, excepeted[index]);
        
        }

        tokenizer = Tokenizer::new(content);
         
        let start = std::time::Instant::now();
        let tokens = Tokenizer::gather_all_tokens(&mut tokenizer, content);
        
        let elapsed = start.elapsed();

        println!("{:?}", tokens);
        println!("{:?}", elapsed);
    }
}