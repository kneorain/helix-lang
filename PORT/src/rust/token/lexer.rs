use core::str::Chars;
use smallvec::{smallvec, SmallVec};
use std::{
    iter::Peekable,
    ops::{ControlFlow, Index},
    slice,
};

use std::sync::atomic::Ordering;
use std::sync::atomic::{AtomicU8, AtomicUsize};
use std::sync::OnceLock;

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
            token: unsafe { std::str::from_utf8(token).unwrap_unchecked() },
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

#[derive(Debug, Clone)]
enum COLORS {
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightBlue = 94,
    BrightMagenta = 95,
    BrightCyan = 96,
}

const COLORS: [COLORS; 12] = [
    COLORS::RED,
    COLORS::GREEN,
    COLORS::YELLOW,
    COLORS::MAGENTA,
    COLORS::BLUE,
    COLORS::CYAN,
    COLORS::BrightRed,
    COLORS::BrightGreen,
    COLORS::BrightYellow,
    COLORS::BrightBlue,
    COLORS::BrightMagenta,
    COLORS::BrightCyan,
];

struct DebugCounter {
    color_count: AtomicU8,
    char_count: AtomicUsize,
}

impl DebugCounter {
    /// println! style usage,
    /// so a message and format args
    fn new() -> Self {
        return DebugCounter {
            color_count: AtomicU8::new(0),
            char_count: AtomicUsize::new(0),
        };
    }

    const CHARS: [char; 62] = [
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    ];

    pub fn print(&mut self, line_number: u32) {
        self.char_count.fetch_add(1, Ordering::SeqCst);
        print!(
            "\u{001b}[{}m({}|{})\u{001b}[0m|",
            self.color(),
            self.char(),
            line_number
        );
    }

    fn color(&mut self) -> u8 {
        let color_count = self.color_count.load(Ordering::SeqCst);
        self.color_count
            .store((color_count + 1) % (COLORS.len() as u8), Ordering::SeqCst);
        return COLORS[color_count as usize].clone() as u8;
    }

    fn char(&mut self) -> char {
        let char = self.char_count.load(Ordering::SeqCst);
        self.char_count
            .store((char + 1) % (Self::CHARS.len() as usize), Ordering::SeqCst);
        return Self::CHARS[char as usize];
    }

    pub fn reset(&mut self) {
        self.color_count.store(0, Ordering::SeqCst);
        self.char_count.store(0, Ordering::SeqCst);
    }

    pub fn print_char(&mut self, c: &str) {
        self.char_count.fetch_add(1, Ordering::SeqCst);
        print!("\u{001b}[{}m{}\u{001b}[0m", self.color(), c);
    }
}

static mut DBG: OnceLock<DebugCounter> = OnceLock::new();
macro_rules! dbg_trace {
    () => {
        #[cfg(feature = "debug-trace")]
        unsafe {DBG.get_mut().unwrap().print(line!());}
    };
    ($literal:literal) => {
        #[cfg(feature = "debug-trace")]
        unsafe {DBG.get_mut().unwrap().print_char($literal.into());}
    };
    ($($arg:tt)*) => { // dbg_trace(reset, "hello we start trace {}", "hello we start trace {})

    #[cfg(feature = "debug-trace")]
    unsafe{

            println!();
            print!($($arg)*);
            DBG.get_or_init(|| DebugCounter::new());
            DBG.get_mut().unwrap().reset()
        }
    };

}

#[derive(Debug, Clone)]
pub struct Tokenizer<'a> {
    chars: &'a [u8],
    column: usize,
    row: usize,
    // used for iterator to avoid reallocation
    cursor_head: usize,

    cursor_tail: usize,
    token: &'a [u8],
    // if a token is complete
    complete: bool,
}

impl<'a> Tokenizer<'a> {
    // cpp could straight up pass in a u8 slice instead of a string slice
    pub fn new(content: &'a str) -> Self {
        Tokenizer {
            chars: content.as_bytes(),
            cursor_head: 0,
            column: 0,
            cursor_tail: 0,
            row: 1,
            token: &[],
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
    pub fn gather_all_tokens(&mut self, _content: &str) -> Vec<TokenIR<'a>> {
        let mut tokens = Vec::new();

        loop {
            let token = unsafe { self.next().unwrap_unchecked() };
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
        self.chars.get(self.cursor_head + 1)
    }

    #[inline(always)]
    fn peak_to(&self, to: usize) -> Option<&[u8]> {
        self.chars.get(self.cursor_head..self.cursor_head + to)
    }

    #[inline(always)]
    fn peak_back(&self) -> Option<&u8> {
        self.chars.get(self.cursor_head - 1)
    }

    #[inline(always)]
    fn peak_back_to(&self, to: usize) -> Option<&[u8]> {
        self.chars.get(self.cursor_head - to..self.cursor_head)
    }

    // Head methods

    #[inline(always)]
    fn head(&self) -> usize {
        self.cursor_head
    }
    #[inline(always)]
    fn set_head(&mut self, head: usize) {
        self.cursor_head = head;
    }

    #[inline(always)]
    fn increment_head(&mut self) {
        self.cursor_head += 1;
        self.increment_column();
    }

    // Column and head methods

    
    #[inline(always)]
    fn increment_head_n(&mut self, n: usize) {
        self.cursor_head += n;
        self.column += n;
    }


    // Tail methods

    #[inline(always)]
    fn increment_tail(&mut self) {
        self.cursor_tail += 1;
    }

    #[inline(always)]
    fn set_tail(&mut self, tail: usize) {
        self.cursor_tail = tail;
    }

    #[inline(always)]
    fn increment_window(&mut self) {
        // Move the head       
        self.increment_tail();
        self.increment_head();
        self.increment_column(); // is this needed?
        

        // Set the tail to the old head
    }

    #[inline(always)]
    fn cut_token(&mut self)-> &'a [u8]{
        

        //self.increment_window();
         // Cut the token
            let token = unsafe {
            // TODO: make unchecked
            self.get_token().unwrap()
        };
        self.increment_head();
        self.set_tail(self.head());

        token
    }

    #[inline(always)]
    fn get_token(&mut self) -> Option<&'a [u8]> {
        // cache this... and update it only when called

        self.chars.get(self.cursor_tail..self.cursor_head)
    }

    #[inline(always)]
    fn increment_column(&mut self) {
        self.column += 1;
    }

    #[inline(always)]
    fn increment_row(&mut self) {
        self.row += 1;
        self.reset_column();
    }

    #[inline(always)]
    fn last_char(&self) -> Option<&u8> {
        self.chars.get(self.cursor_head)
    }

    #[inline(always)]
    fn is_cut_empty(&self) -> bool {
        self.cursor_head == self.cursor_tail
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
    fn process_delimiter(&mut self) -> ControlFlow<()> {
        dbg_trace!("b");

        if self.is_cut_empty() {
            dbg_trace!("c");
            self.increment_head();
            return ControlFlow::Continue(());
        }

        return ControlFlow::Break(());
    }

    #[inline(always)]
    fn process_string(&mut self, ch: &u8) -> ControlFlow<()> {
        // if string is not complete it should return a type
        dbg_trace!("f");

        if !self.is_cut_empty() & // TODO REMOVE to_owned
            !ALLOWED_STRING_PREFIXES.contains(unsafe { self.last_char().unwrap_unchecked() })
        {
            dbg_trace!("g");

            return ControlFlow::Break(());
        }

        self.increment_head();

        let mut is_escaped = false;
        // Push the starting quote
        while let Some(c) = self.peak_char() {
            // peak should error or something
            match c {
                // Newline
                b'\n' => {
                    dbg_trace!("h");
                    self.increment_row(); // does this need reset colum?
                }

                // Escaped Backslash
                b'\\' if !is_escaped => {
                    dbg_trace!("i");
                    is_escaped = true;
                    self.increment_head();
                    continue;
                }

                c if (c == ch) & !is_escaped => {
                    dbg_trace!("j");
                    self.increment_head();
                    break;
                }
                _ => {
                    dbg_trace!("k");
                }
            }

            is_escaped = false;

            // The closing quote
            self.increment_head();
        }
        ControlFlow::Continue(())
    }

    fn process_char(&mut self, ch: &u8) -> ControlFlow<()> {
        dbg_trace!("m");

        match self.peak_char() {
            Some(b'\'') | Some(b'"') if ALLOWED_STRING_PREFIXES.contains(ch) => {
                dbg_trace!("n");

                self.increment_head();

                return ControlFlow::Break(());
            }

            _ => {}
        }

        dbg_trace!("o");

        self.increment_head();
        // if theres a string prefix like r, b, u, f and a " or ' then we need to handle it

        ControlFlow::Continue(())
    }
}

impl<'a> Iterator for Tokenizer<'a> {
    type Item = TokenIR<'a>;
    #[inline(always)]
    fn next(&mut self) -> Option<Self::Item> {
        // is a vec needed here or can we return a slice of the content

        // slice the slices and split them into smaller slice parts
        self.increment_head();

        'peek: for ch in self.chars.index(self.cursor_head..self.chars.len()) {
            dbg_trace!("('{}' t {} h {}: ", *ch as char, self.cursor_tail, self.cursor_head);
            dbg_trace!("0");

            // Handle whitespace

            if ch.is_ascii_whitespace() {
                dbg_trace!("1");
                match ch {
                    b'\n' => {
                        dbg_trace!("2");
                        self.increment_row();
                    }
                    _ => self.increment_column(),
                }
                dbg_trace!("3");
                

                // //dbg!(self.is_cut_empty());

                if !self.is_cut_empty() {
                    dbg_trace!("4");
                    break;
                }

                continue;
            }
            

            // Handle Operators

            dbg_trace!("5");
            // this should obtain a slice of the next few characters and then match on it, or iterate over each part of the multiline ops
            // use a chain?
            // Check if the next characters are a multi-character operator
            if MULTI_CHAR_OPERATOR
                .iter()
                .any(|operator| operator[0] == *ch)
            {
                dbg_trace!("6");
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
                    dbg_trace!("7");
                    //dbg!(std::str::from_utf8(&self.peak_to(op_len).unwrap()).unwrap());

                    // this gets the next few characters and then checks if they are equal to the operator
                    if self.peak_to(op_len) == Some(&operator[0..op_len]) {
                        dbg_trace!("8");

                        // Move the head to the end of the operator
                        self.increment_head_n(op_len);

                        break 'peek;
                    }
                }
            }

            dbg_trace!("9");

            // Handle single character tokens
            match ch {
                b'{' | b'}' | b'(' | b')' | b';' | b'!' | b'=' | b'|' => {
                    dbg_trace!("a");
                    if self.process_delimiter().is_break() {
                        dbg_trace!("d");
                        break;
                    }
                }
                // strings should not be allowed to be ' '
                b'\'' | b'"' => {
                    dbg_trace!("e");
                    if self.process_string(ch).is_break() {
                        dbg_trace!("l");
                        break;
                    }
                }

                _ if self.process_char(ch).is_break() => {
                    dbg_trace!("p");
                    break;
                }
                _ => {}
            }
        }
        println!(" :t {} h {})",self.cursor_tail, self.cursor_head);

        //println!("\nTOKEN FINISH: {}", std::str::from_utf8(&token).unwrap());

        Some(TokenIR::new(
            self.cut_token(),
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
                "\nr:{} c:{} t:'{}' e:{:?}",
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
