use core::str::Chars;
use std::borrow::{Borrow, BorrowMut};
use smallvec::{smallvec, SmallVec};
use std::ops::Index;
use std::{iter::Peekable, ops::ControlFlow::*, ops::Range};

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




//const OPERATOR_PREFIXES: [u8; 4] = [b'r', b'b', b'u', b'f'];
//}
// const TWO_CHAR_OPERATORS: [ [u8; 2]; 40] = [

// ];

//

// make a macro that makes these macros 

macro_rules! token_patterns {
    ($($name:ident:  $patten:pat),*) => {
        $(
            macro_rules! $name {
                () => {
                    $patten            
                };
            
                (match $ch:expr) => {
                    matches!($ch, $name!()) 
                };

                (trie_match $ch:expr) => {
                    trie_match::trie_match!{  
                        match $ch {
                            $patten => true,
                        _ => false
                    }}
                };
            }
        )*
    }

}



token_patterns! {
    
    delimiters: b'{' | b'}' | b'(' | b')' | b';' | b'!' | b'=' | b'|',
    whitespace: b'\t' | b'\n' | b'\x0C' | b'\r' | b' ',
    quotes: b'\'' | b'"',
    string_prefixes: b'r'|b'b'| b'u'| b'f',
    two_char_operators:helix_proc::convert_bytes_to_u16!( b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
    b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
    b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
    b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
    b"::" | b"||" | b"++" | b"__" | b"?="),
    
    three_char_operators: b"===" | b"!==" | b"..." | b"r//" | b"r**" | b"r<<" | b"r>>" | b"//=" | b"**=" | b"<<=" |
    b">>=" | b"??" | b"|:",
    
    operators_first_char:helix_proc::get_first_char_pattern!(two_char_operators!()|three_char_operators!())
}





//const ALLOWED_STRING_PREFIXES: [u8; 4] = [];

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
    char: u8,
    next_char: u8,
    column: usize,
    row: usize,
    two_char_operator: [u8; 2],
    // used for iterator to avoid reallocation
    cursor: Range<usize>,
    // if a token is complete
    complete: bool,
    last_type: TokenType,
    last_token_column: usize,
    last_token_row: usize,

    // rename
    chars_len:usize,
}

type ControlFlow = std::ops::ControlFlow<()>;
const BREAK: ControlFlow = ControlFlow::Break(());
const CONTINUE: ControlFlow = ControlFlow::Continue(());




impl<'a> Tokenizer<'a> {

    const DEFAULT_RANGE: Range<usize> = 0..0;
    const DEFAULT_COLUMN: usize = 0;
    const DEFAULT_ROW: usize = 1;
    const DEFAULT_CHAR: u8 = b'\0';
    const DEFAULT_CURSOR: Range<usize> = 0..1;
    const DEFAULT_COMPLETE: bool = true;
    const DEFAULT_LAST_TYPE: TokenType = TokenType::None;

    // cpp could straight up pass in a u8 slice instead of a string slice
    pub fn new(content: &'a str) -> Self {
    
        let chars = content.as_bytes();
    
        Tokenizer {
            chars,
            next_char: Self::DEFAULT_CHAR,
            cursor: Self::DEFAULT_CURSOR,
            column: Self::DEFAULT_COLUMN,
            char: Self::DEFAULT_CHAR,
            row: Self::DEFAULT_ROW,
            two_char_operator: [Self::DEFAULT_CHAR; 2],
            complete: Self::DEFAULT_COMPLETE,
            last_type: Self::DEFAULT_LAST_TYPE,
            last_token_column: Self::DEFAULT_COLUMN,
            last_token_row: Self::DEFAULT_ROW,
            chars_len: chars.len(),
        }
    }

    #[inline(always)]
    /// Allows the tokenizer to be reset with new content without reallocation,
    pub fn reset(&mut self, content: &'a str) {
        self.chars = content.as_bytes();
        self.reset_column();
        self.row = Self::DEFAULT_ROW;
        self.cursor = Self::DEFAULT_CURSOR;
        self.complete = Self::DEFAULT_COMPLETE;
        self.last_token_column = Self::DEFAULT_COLUMN;
        self.last_token_row = Self::DEFAULT_ROW;
        self.chars_len = self.chars.len();
    }

    /// A dirty estimate of the number of tokens in the content
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

    pub fn gather_all_tokens(&'a mut self, content: &str) -> Vec<TokenIR<'a>> {
        let mut tokens = Vec::with_capacity(Self::fast_estimate_number_of_tokens(content));

        while let Some(token) = self.next() {
            tokens.push(token);
        }

        tokens
    }

    // nested inlining do not inline: feature for helix

    #[inline(always)]
    fn peek_char(&self) -> Option<&u8> {
        self.peek_char_n(1)
    }

    #[inline(always)]
    fn peek_char_n(&self, n: usize) -> Option<&u8> {
        self.chars.get(self.head() + n)
    }

    #[inline(always)]
    fn head(&self) -> usize {
        self.cursor.start
    }

    #[inline(always)]
    fn tail(&self) -> usize {
        self.cursor.end
    }

    #[inline(always)]
    fn peek_slice(&self, to: usize) -> Option<&[u8]> {
        self.chars.get(self.head()..self.head() + to)
    }

    #[inline(always)]
    fn peek_behind(&self) -> Option<&u8> {
        self.chars.get(self.tail() - 1)
    }

    #[inline(always)]
    fn peak_behind_slice(&self, back_to: usize) -> Option<&[u8]> {
        self.chars.get(self.tail() - back_to..self.tail())
    }

    // Head methods

    #[inline(always)]
    fn increment_head(&mut self) {
        self.increment_head_n(1);
    }

    #[inline(always)]
    fn increment_cursor(&mut self) {
        self.increment_head();
        self.increment_column();
    }

    #[inline(always)]
    fn increment_cursor_n(&mut self, n: usize) {
        self.increment_head_n(n);
        self.increment_column_n(n);
    }

    // Column and head methods

    #[inline(always)]
    fn increment_head_n(&mut self, n: usize) {
        self.cursor.start += n;
    }

    #[inline(always)]
    fn increment_column_n(&mut self, n: usize) {
        self.column += n;
    }

    // Tail methods

    #[inline(always)]
    fn increment_tail(&mut self) {
        self.increment_tail_n(1);
    }

    #[inline(always)]
    fn increment_tail_n(&mut self, n: usize) {
        self.cursor.end += n;
    }

    #[inline(always)]
    fn set_tail(&mut self, tail: usize) {
        println!("tail: {}", tail);
        self.cursor.end = tail;
    }

    #[inline(always)]
    fn increment_window_n(&mut self, n: usize) {
        // Move the head
        self.increment_tail_n(n);
        self.increment_head_n(n);

        // Set the tail to the old head
    }

    #[inline(always)]
    fn increment_window(&mut self) {
        self.increment_window_n(1);
    }

    // removes the cut token
    #[inline(always)]
    fn cut_reset(&mut self) {
        self.last_token_column = self.column;
        self.last_token_row = self.row;
        self.set_tail(self.head());
    }

    #[inline(always)]
    fn cut_current(&mut self) -> Option<&'a [u8]> {
        // cache this... and update it only when called
        self.chars.get(self.cursor.clone())
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
        self.chars.get(self.head())
    }

    #[inline(always)]
    fn cut_index(&self, idx: usize) -> Option<&u8> {
        self.chars.get(idx)
    }

    

    #[inline(always)]
    fn match_slice(&self, slice: &[u8]) -> bool {
        self.peek_slice(slice.len()) == Some(slice)
    }

    #[inline(always)]
    fn reset_column(&mut self) {
        self.column = Self::DEFAULT_COLUMN;
    }

    /// Processing methods

    #[inline(always)]
    fn process_whitespace(&mut self) -> ControlFlow {
        dbg_trace!("1");
        match self.char {
            b'\n' => {
                dbg_trace!("2");
                self.increment_row();
            }
            _ => self.increment_column(),
        }

        dbg_trace!("3");
        // //dbg!(self.is_cut_empty());

        if !self.cursor.is_empty() {
            BREAK
        } else {
            CONTINUE           
        }
    }

    #[inline(always)]
    fn process_operator(&mut self) -> ControlFlow {
        dbg_trace!("6");

        if let Some(slice)= self.peek_slice(3) {

            if three_char_operators!(trie_match slice) {
                dbg_trace!("7");

                self.increment_cursor_n(3);

                return BREAK;
            }
        }

        
        // this is safe as the peak for 3 is checked so 2 is always valid
        
        // we convert the slice to a u16 to compare it the two char operators which are already u16
        // this should be faster than comparing two slices* untested
        if two_char_operators!(match unsafe {             
            
            //TODO: Figure out a way to do this without copying
            std::ptr::copy_nonoverlapping(self.peek_slice(2).unwrap_unchecked().as_ptr(), self.two_char_operator.as_mut_ptr(), 2);

            std::mem::transmute::<[u8;2], u16>(self.two_char_operator)
        
        }) {
            dbg_trace!("8");

            self.increment_cursor_n(2);

            return BREAK;
        };

        CONTINUE
    }


    #[inline(always)]
    fn process_delimiter(&mut self) -> ControlFlow {
        dbg_trace!("b");
        // self.decrement_head(); // change later

        return BREAK;
    }

    #[inline(always)]
    fn process_quotes(&mut self) -> ControlFlow {
        // if string is not complete it should return a type
        dbg_trace!("f");

        if !self.cursor.is_empty() & 
            // If this was contains it would be O(n) instead of O(1)
            // cut last exists so this should always be true
            !string_prefixes!(match unsafe { self.last_char().unwrap_unchecked() })
        {
            dbg_trace!("g");

            return BREAK;
        }

        self.increment_cursor();

        let mut is_escaped = false;

        // Push the starting quote
        while let Some(c) = self.peek_char() { // TODO: FIX

            // peak should error or something
            match c {
                // Newline
                b'\n' => {
                    dbg_trace!("h");
                    self.increment_cursor();
                }

                // Backslash
                b'\\' if !is_escaped => {
                    dbg_trace!("i");
                    is_escaped = true;
                    self.increment_cursor();
                    continue;
                }

                c if (*c == self.char) & !is_escaped => {
                    dbg_trace!("j");
                    self.increment_cursor();
                    break;
                }

                _ => {
                    dbg_trace!("k");
                }
            }

            is_escaped = false;

            // The closing quote
            self.increment_cursor();
        }
        CONTINUE
    }

    #[inline(always)]
    fn process_char(&mut self) -> ControlFlow {
        dbg_trace!("m");

        // Check for string prefix
        match self.next_char { 
            
            quotes!()  if string_prefixes!(match self.char) => {
                dbg_trace!("n");

                self.increment_cursor();

                return BREAK;
            }

            _ => {}
        }

        dbg_trace!("o");

        self.increment_cursor();
        // if theres a string prefix like r, b, u, f and a " or ' then we need to handle it

        CONTINUE
    }

    
}

// TODO: Add this
#[derive(Debug, Clone)]
enum TokenType {
    String,
    Char,
    Numeric,
    Identifier,
    Delimiter,
    Operator,
    Comment,
    None,
}

impl<'a> Iterator for Tokenizer<'a> {
    type Item = TokenIR<'a>;

    #[inline(always)]
    fn next(&mut self) -> Option<Self::Item> {
        

        for i in self.head()..self.chars_len {
            
            self.next_char = match self.chars.get(i + 1) {
                Some(c) => *c,
                None => {
                    self.complete = false;
                    break
                },
            };
            
            // if peek fails the end of the input has been reached, so there is no need to check.
            self.char = unsafe {*self.chars.get(i).unwrap_unchecked()};

            dbg_trace!("('{}' t {} h {}: ",self.char as char,self.tail(),self.head());
            
            dbg_trace!("0");

            // peeks the next char, could not use peek method due to
            if match self.next_char {
                // Whitespace
                whitespace!() => self.process_whitespace(),
                
                // Operators
                _ if operators_first_char!(match self.char) => self.process_operator(),

                // Delimiters
                delimiters!() => self.process_delimiter(),
                
                // Quotes
                quotes!() => self.process_quotes(),

                // Characters
                _ => self.process_char(),
            // Break the loop 
            } == BREAK { break }
        }

        println!(" :t {} h {})",self.tail(), self.head(),);

        //println!("\nTOKEN FINISH: {}", std::str::from_utf8(&token).unwrap());

        let token = TokenIR::new(
            self.cut_current().unwrap(), //TODO: unchecked
            self.last_token_column,
            self.last_token_row,
            self.complete,
        );

        self.cut_reset();

        Some(token)
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
        // Two char operators
        // macro_rules! match_operator {
        //     ($word:ident,$num:literal,$dbg:literal) => {
        //         paste::paste!{
        //             if [<$word _char_operators>]!(trie_match self.peek_slice($num) ) {
        //                 dbg_trace!($dbg);
        
        //                 // Move the head to the end of the operator
        //                 self.increment_cursor_n($num);
        
        //                 return BREAK;
        //             };
        //         }
        //     };
        // }
    
        // make these better based on the other macro and or a proc macro
        // match_operator!(two,2,"8");
        // match_operator!(three,3,"9");
