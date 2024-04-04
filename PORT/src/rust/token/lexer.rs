use core::str::Chars;
use smallvec::{smallvec, SmallVec};
use std::{
    iter::Peekable,
    ops::{ControlFlow, Index},
    slice,
};

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

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct TokenIR<'a> {
    token: &'a str,
    column: usize,
    row: usize,
    complete: bool,
}

impl<'a> TokenIR<'a> {
    pub fn new(token: &'a [u8], column: usize, row: usize, complete: bool) -> Self {
        TokenIR {
            // safe as we only have valid utf8 tokens
            token: unsafe {std::str::from_utf8(token).unwrap_unchecked()},
            // FIXME: more testing is needed to determine if this is the
            // correct way to calculate the column since the +1 is
            // a hack to fix the column being off by one.
            column: column.saturating_sub(token.len()), // + (1);,
            row,
            complete,
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
    *b"===", *b"!==", *b"...", *b"r//", *b"r**", *b"r<<", *b"r>>", *b"//=", *b"**=", *b"<<=",
    *b">>=", *b"??\0", *b"|:\0", *b"==\0", *b"!=\0", *b"<=\0", *b">=\0", *b"//\0", *b"**\0",
    *b"<<\0", *b">>\0", *b"r+\0", *b"r-\0", *b"r*\0", *b"r/\0", *b"r%\0", *b"r&\0", *b"r|\0",
    *b"r^\0", *b"+=\0", *b"-=\0", *b"*=\0", *b"/=\0", *b"%=\0", *b"&=\0", *b"|=\0", *b"^=\0",
    *b"==\0", *b"=>\0", *b"@=\0", *b"->\0", *b"<-\0", *b"<=\0", *b">=\0", *b"&&\0", *b"--\0",
    *b"::\0", *b"||\0", *b"++\0", *b"__\0", *b"?=\0",
];

//const OPERATOR_PREFIXES: [u8; 4] = [b'r', b'b', b'u', b'f'];
//}
// const TWO_CHAR_OPERATORS: [ [u8; 2]; 40] = [

// ];

const ALLOWED_STRING_PREFIXES: [u8; 4] = [b'r', b'b', b'u', b'f'];

// TODO USE BYTES CRATE IF ITS FASTER TO ITERATE OVER BYTES

macro_rules! increment_token {
    ($self:ident,$upper_bound:ident) => {
        // make unchecked?
        //$self.chars.next().unwrap();
        $self.increment_token()
    };
}
#[derive(Debug, Clone)]
pub struct Tokenizer<'a> {
    chars: &'a [u8],
    column: usize,
    row: usize,
    // used for iterator to avoid reallocation
    cursor: usize,
    upper_bound: usize,
    lower_bound: usize,
    token: &'a [u8],
    // if a token is complete
    complete: bool,
}

impl<'a> Tokenizer<'a> {
    pub fn new(content: &'a str) -> Self {
        Tokenizer {
            chars: content.as_bytes(),
            cursor: 0,
            column: 0,
            lower_bound: 0,
            upper_bound: 0,
            row: 0,
            token: &content.as_bytes()[0..0],
            complete: true,
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

    // TODO: impl peakable for this

    #[inline(always)]
    fn peak_char(&self) -> Option<&u8> {
        self.chars.get(self.cursor)
    }

    #[inline(always)]
    fn peak_next(&self) -> Option<&u8> {
        self.chars.get(self.cursor + 1)
    }
    
    #[inline(always)]
    fn peak_to(&self, to: usize) -> Option<&[u8]> {
        self.chars.get(self.cursor..to)
    }

    #[inline(always)]
    fn peak_back(&self) -> Option<&u8> {
        self.chars.get(self.cursor - 1)
    }

    #[inline(always)]
    fn peak_back_to(&self, to: usize) -> Option<&[u8]> {
        self.chars.get(self.cursor - to..self.cursor)
    }

    #[inline(always)]
    fn increment_char(&mut self) {
        self.upper_bound += 1;
        self.increment_cursor();
        self.increment_column();
    }

    #[inline(always)]
    fn skip_char(&mut self) {
        self.increment_cursor();
        self.increment_column();
    }

    #[inline(always)]
    fn increment_cursor(&mut self) {
        self.cursor += 1;
    }

    #[inline(always)]
    fn increment_token(&mut self) -> &'a [u8] {
        let old_lower_bound = self.lower_bound;
        self.upper_bound += 1;
        self.lower_bound = self.upper_bound;


        unsafe {
            self.chars
                .get(old_lower_bound..=self.upper_bound)
                .unwrap_unchecked()
        }
    }

    fn process_char(&mut self, ch: &u8) -> ControlFlow<()> {
        print!("l");

        match self.peak_char() {
            Some(b'\'') | Some(b'"') if ALLOWED_STRING_PREFIXES.contains(ch) => {
                print!("m");

                self.increment_char();

                return ControlFlow::Break(());
            }

            _ => {}
        }

        print!("n");

        self.increment_column();
        // if theres a string prefix like r, b, u, f and a " or ' then we need to handle it

        ControlFlow::Continue(())
    }

    #[inline(always)]
    fn increment_column(&mut self) {
        self.column += 1;
    }

    #[inline(always)]
    fn increment_row(&mut self) {
        self.row += 1;
        self.reset_column();
        self.increment_cursor();
    }



    #[inline(always)]
    fn process_delimiter(&mut self) -> ControlFlow<()> {
        print!("j");
        if self.is_empty() {
            print!("k");
            self.increment_char();
        }

        return ControlFlow::Break(());
    }
    #[inline(always)]

    fn last_char(&self) -> Option<&u8> {
        self.chars.get(self.cursor - 1)
    }
    #[inline(always)]

    fn is_empty(&self) -> bool {
        self.cursor == self.lower_bound
    }

    #[inline(always)]
    fn match_slice(&self, slice: &[u8]) -> bool {
        self.peak_to(slice.len()) == Some(slice)
    }
    #[inline(always)]

    fn reset_column(&mut self) {
        self.column = 0;
    }
    #[inline(always)]

    fn token(&'a self) -> &'a [u8] {
        // cache the token but

        self.chars.get(self.lower_bound..=self.upper_bound).unwrap()
    }

    #[inline(always)]
    fn process_string(&mut self, ch: &u8) -> ControlFlow<()> {
        // if string is not complete it should return a type
        print!("d");

        if !self.is_empty()// TODO REMOVE to_owned
            & !ALLOWED_STRING_PREFIXES.contains(unsafe {self.last_char().unwrap_unchecked()})
        {
            print!("e");

            return ControlFlow::Break(());
        }

        // if ALLOWED_STRING_PREFIXES.contains(&ch) && (*self.chars.peek().unwrap() == '"' || *self.chars.peek().unwrap() == '\'') {
        //     token.push(ch as u8);
        //     self.increment_column();
        //     return ControlFlow::Break(());
        // }
        // make a macro for this

        self.increment_char();

        let mut is_escaped = false;
        // Push the starting quote
        while let Some(c) = self.peak_char() {
            // peak should error or something
            match c {
                b'\n' => {
                    print!("f");
                    self.increment_row(); // does this need reset colum?
                }
                b'\\' if !is_escaped => {
                    print!("g");
                    is_escaped = true;
                    self.increment_char();
                    continue;
                }
                c if (c == ch) & !is_escaped => {
                    print!("h");
                    self.increment_char();
                    break;
                }
                _ => {
                    print!("i");
                }
            }

            is_escaped = false;

            self.increment_char();
        }
        ControlFlow::Continue(())
    }
   
}

impl<'a> Iterator for Tokenizer<'a> {
    type Item = TokenIR<'a>;
    #[inline(always)]
    fn next(&mut self) -> Option<Self::Item> {
        // is a vec needed here or can we return a slice of the content

        // slice the slices and split them into smaller slice parts




        for ch in self.chars.index(self.cursor..self.chars.len()) {

            print!("\n {}: 1",* ch as char);
            if ch.is_ascii_whitespace() {
                print!("2");
                match ch {
                    b'\n' => {
                        print!("3");
                        self.increment_row();
                        self.reset_column();
                    }
                    _ => self.skip_char(),
                }
                print!("4");
                self.increment_char();
                if !self.is_empty() {
                    print!("5");
                    break;
                }
                continue;
            }
            print!("6");

            // this should obtain a slice of the next few characters and then match on it, or iterate over each part of the multiline ops
            // use a chain?
            // Check if the next characters are a multi-character operator
            if MULTI_CHAR_OPERATOR
                .iter()
                .any(|operator| operator[0] == *ch)
            {
                print!("7");
                // if let Some(operator) = MULTI_CHAR_OPERATOR
                //     .iter()
                //     .find(|&operator| self.peak_to(operator.len()).unwrap() == operator)
                // {
                //     // TODO: need a better way to handle this

                //     let op_len = if operator[2] == b'\0' { 2 } else { 3 };

                //     for _ in 0..op_len {
                //         self.increment_char();
                //     }

                //     break; // Break out of "while let Some(&ch) = self.chars.peek() { ... }"
                // }

                for operator in MULTI_CHAR_OPERATOR.iter() {
                    // this is temp until we can figure out a better way to handle this
                    let op_len = if operator[2] == b'\0' { 2 } else { 3 };
                    // TODO: need better solution for Some(&operator[0..op_len])

                    // this gets the next few characters and then checks if they are equal to the operator
                    if self.peak_to(op_len) == Some(&operator[0..op_len]) {
                        for _ in 0..op_len {
                            self.increment_char();
                        }

                        break; // Break out of "while let Some(&ch) = self.chars.peek() { ... }"
                    }
                }
            }

            print!("9");
            // Handle single character tokens
            match ch {
                b'{' | b'}' | b'(' | b')' | b';' | b'!' | b'=' | b'|' => {
                    print!("a");
                    if self.process_delimiter().is_break() {
                        break;
                    }
                }
                // strings should not be allowed to be ' '
                b'\'' | b'"' => {
                    if self.process_string(ch).is_break() {
                        print!("b");
                        break;
                    }
                }

                _ if self.process_char(ch).is_break() => {
                    print!("c");
                    continue;
                }
                _ => {}
            }
        }


        //println!("\nTOKEN FINISH: {}", std::str::from_utf8(&token).unwrap());

        Some(TokenIR::new(
            self.increment_token(),
            self.column,
            self.row,
            self.complete,
        ))
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
                "\nr:{} c:{} t:{} e:{:?}",
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
