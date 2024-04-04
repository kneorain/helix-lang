use core::str::Chars;
use smallvec::{smallvec, SmallVec};
use std::{iter::Peekable, ops::ControlFlow, slice};

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
    fn lexer(&self, file: &str) -> Vec<Token>;
    fn lexer_str(&self, content: &str) -> Vec<Token>;
}

#[derive(Debug, Clone)]
pub struct Tokenizer<'a> {
    chars: Peekable<slice::Iter<'a, u8>>,
    cursor: usize,
    column: usize,
    row: usize,
    tokens: SmallVec<[String; 32]>,
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct TokenIR<'a> {
    token: &'a str,
    column: usize,
    row: usize,
}

impl<'a> TokenIR<'a> {
    pub fn new(token: Vec<u8>, column: usize, row: usize) -> Self {
        TokenIR {
            token: unsafe {
                std::str::from_utf8(slice::from_raw_parts((&token).as_ptr(), token.len()))
                    .unwrap_unchecked()
            },
            // FIXME: more testing is needed to determine if this is the
            // correct way to calculate the column since the +1 is
            // a hack to fix the column being off by one.
            column: column.saturating_sub(token.len()), // + (1);,
            row,
        }
    }
}
// macro_rules! no_format {
//     {$ex:block} => {
// $ex

//     };
// }

// TODO: make this a flat buffer
//no_format! {
// fix formatting
const MULTI_CHAR_OPERATOR: [[u8; 3]; 51] = [
    *b"===", *b"!==", *b"...", *b"r//", *b"r**", *b"r<<",
    *b"r>>", *b"//=", *b"**=", *b"<<=", *b">>=",
    
    *b"??\0", *b"|:\0", *b"==\0", *b"!=\0", *b"<=\0", *b">=\0", *b"//\0",
    *b"**\0", *b"<<\0", *b">>\0", *b"r+\0", *b"r-\0", *b"r*\0", *b"r/\0",
    *b"r%\0", *b"r&\0", *b"r|\0", *b"r^\0", *b"+=\0", *b"-=\0", *b"*=\0",
    *b"/=\0", *b"%=\0", *b"&=\0", *b"|=\0", *b"^=\0", *b"==\0", *b"=>\0",
    *b"@=\0", *b"->\0", *b"<-\0", *b"<=\0", *b">=\0", *b"&&\0", *b"--\0",
    *b"::\0", *b"||\0", *b"++\0", *b"__\0", *b"?=\0",
];

//const OPERATOR_PREFIXES: [u8; 4] = [b'r', b'b', b'u', b'f'];
//}
// const TWO_CHAR_OPERATORS: [ [u8; 2]; 40] = [

// ];

const ALLOWED_STRING_PREFIXES: [u8; 4] = [b'r', b'b', b'u', b'f'];

impl<'a> Tokenizer<'a> {
    pub fn new(content: &'a str) -> Self {
        Tokenizer {
            chars: content.as_bytes().iter().peekable(),
            cursor: 0,
            column: 0,
            row: 0,
            tokens: SmallVec::new(),
        }
    }

    /// dirty estimate of the number of tokens in the content
    pub fn fast_estimate_number_of_tokens(content: &str) -> usize {
        let mut count = 0;
        let mut in_string = false;
        let mut prev_char = b'\0';

        for c in content.as_bytes() {
            match c {
                b'"' if in_string & (prev_char != b'\\') => {
                    // Handle string closure and escape character
                    in_string = false;
                }
                b'"' => {
                    // Handle string opening
                    in_string = true;
                    count += 1; // Count the entire string as one token
                }
                c if c.is_ascii_alphanumeric() || *c == b'_' || c.is_ascii_punctuation() => {
                    count += 1;
                }
                _ => {}
            }
            prev_char = *c;
        }
        count
    }

    // there is prob a trait for this

    // does this need to return a vec or not
    pub fn gather_all_tokens(tokenizer: &mut Self, _content: &str) -> Vec<TokenIR<'a>> {
        let mut tokens = Vec::new();

        loop {
            let token = unsafe { tokenizer.next().unwrap_unchecked() };

            if !token.token.is_empty() {
                tokens.push(token);
            } else {
                break;
            }
        }

        tokens
    }

    fn process_char(&mut self, ch: u8, token: &mut Vec<u8>) -> ControlFlow<()> {
        //print!("l");

        match unsafe { *self.chars.peek().unwrap_unchecked() } {
            b'\'' | b'"' if ALLOWED_STRING_PREFIXES.contains(&ch) => {
                //print!("m");
                token.push(ch);
                self.column += 1;
                return ControlFlow::Break(());
            }

            _ => {}
        }

        //print!("n");

        token.push(*self.chars.next().unwrap());
        self.column += 1;
        // if theres a string prefix like r, b, u, f and a " or ' then we need to handle it

        ControlFlow::Continue(())
    }

    fn process_delimiter(&mut self, token: &mut Vec<u8>) -> ControlFlow<()> {
        //print!("j");
        if token.is_empty() {
            //print!("k");
            token.push(*self.chars.next().unwrap());
            self.column += 1;
        }

        return ControlFlow::Break(());
    }

    #[inline(always)]
    fn process_string(&mut self, token: &mut Vec<u8>, ch: u8) -> ControlFlow<()> {
        //print!("d");

        if !token.is_empty()
            && !ALLOWED_STRING_PREFIXES.contains(unsafe { token.last().unwrap_unchecked() })
        {
            //print!("e");
            
            return ControlFlow::Break(());
        }
       

        
        // if ALLOWED_STRING_PREFIXES.contains(&ch) && (*self.chars.peek().unwrap() == '"' || *self.chars.peek().unwrap() == '\'') {
        //     token.push(ch as u8);
        //     self.column += 1;
        //     return ControlFlow::Break(());
        // }
        // make a macro for this

        token.push(*self.chars.next().unwrap());

        self.column += 1;

        let mut is_escaped = false;
        // Push the starting quote
        while let Some(&c) = self.chars.peek() {
            match c {
                b'\n' => {
                    //print!("f");
                    self.row += 1
                }
                b'\\' if !is_escaped => {
                    //print!("g");
                    is_escaped = true;
                    token.push(*self.chars.next().unwrap());
                    self.column += 1;
                    continue;
                }
                c if (*c == ch) & !is_escaped => {
                    //print!("h");
                    token.push(*self.chars.next().unwrap());
                    self.column += 1;
                    break;
                }
                _ => {
                    //print!("i");
                }
            }

            is_escaped = false;

            token.push(*self.chars.next().unwrap());
            self.column += 1;
        }
        ControlFlow::Continue(())
    }
}

impl<'a> Iterator for Tokenizer<'a> {
    type Item = TokenIR<'a>;
    #[inline(always)]
    fn next(&mut self) -> Option<Self::Item> {
        // is a vec needed here or can we return a slice of the content

        let mut token = Vec::new();

        // slice the slices and split them into smaller slice parts

        let mut token_slice: &[u8];

        let lower_bound = self.chars.len() + 1;

        let mut upper_bound = lower_bound;

        while let Some(&ch) = self.chars.peek() {
            //print!("\n1");
            if ch.is_ascii_whitespace() {
                //print!("2");
                match ch {
                    b'\n' => {
                        //print!("3");
                        self.row += 1;
                        self.column = 0;
                    }
                    _ => self.column += 1,
                }
                //print!("4");
                self.chars.next();
                if !token.is_empty() {
                    //print!("5");
                    break;
                }
                continue;
            }
            //print!("6");

            // this should obtain a slice of the next few characters and then match on it, or iterate over each part of the multiline ops

            // Check if the next characters are a multi-character operator
            if MULTI_CHAR_OPERATOR
                .iter()
                .any(|operator| operator[0] == *ch)
            {
                //print!("7");
                if let Some(operator) = MULTI_CHAR_OPERATOR.iter().find(|&operator| {
                    operator.iter().enumerate().all(|(i, c)| {
                        // TODO: make this more optimal
                        if c == &b'\0' {
                            //print!("*");
                            return true;
                        }

                        // fix clone
                        match self.chars.clone().nth(i) {
                            Some(ch) => {
                                //print!("9");

                                ch == c
                            }
                            None => false,
                        }
                    })
                }) {
                    // TODO: need a better way to handle this

                    let op_len = if operator[2] == b'\0' { 2 } else { 3 };

                    for _ in 0..op_len {
                        token.push(*self.chars.next().unwrap());
                        self.column += 1;
                    }

                    break; // Break out of "while let Some(&ch) = self.chars.peek() { ... }"
                }
            }
            //print!("9");
            // Handle single character tokens
            match ch {
                b'{' | b'}' | b'(' | b')' | b';' | b'!' | b'=' | b'|' => {
                    //print!("a");
                    if self.process_delimiter(&mut token).is_break() {
                        break;
                    }
                }
                // strings should not be allowed to be ' '
                b'\'' | b'"' => {
                    if self.process_string(&mut token, *ch).is_break() {
                        //print!("b");
                        break;
                    }
                }

                _ if self.process_char(*ch, &mut token).is_break() => {
                    //print!("c");
                    continue;
                }
                _ => {}
            }
        }
        //println!("\nTOKEN FINISH: {}", std::str::from_utf8(&token).unwrap());

        TokenIR::new(token, self.column, self.row).into()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_determine_tokens() {
        let content = "fn === main() {
            println!(\"Hello,
            world!\");
            \"Hello; \\\" world!\"
            if true != false {
                let xyz_99_yoMama = 5 | b\"some\" | 'c';
            }
        }";

        let mut tokenizer = Tokenizer::new(content);

        let expected = [
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

        for index in 0..expected.len() {
            let start = std::time::Instant::now();
            let token = tokenizer.next().unwrap();
            let elapsed = start.elapsed();
            println!(
                "r:{} c:{} t:{} e:{:?}",
                token.row, token.column, token.token, elapsed
            );
            assert_eq!(token.token, expected[index]);
        }

        tokenizer = Tokenizer::new(content);

        let start = std::time::Instant::now();
        let tokens = Tokenizer::gather_all_tokens(&mut tokenizer, content);

        let elapsed = start.elapsed();

        println!("{:?}", tokens);
        println!("{:?}", elapsed);
    }
}
