use std::{
    ffi::OsStr,
    ops::Range,
    ptr::{self, addr_of_mut, slice_from_raw_parts},
    slice::SliceIndex,
    sync::atomic::{AtomicPtr, Ordering},
};

use cxx::{memory::SharedPtrTarget, SharedPtr};

use crate::rust::debug_counter::dbg_trace;

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

// this is a struct that is managed in rust that communicates with cpp, should be under a shared ptr,

#[derive(Debug)]
pub struct Token<'cxx> {
    //file: AtomicPtr<super::super::shared::file_data::File<'cxx>>,
    chars: &'cxx [u8],
    column: usize,
    row: usize,

    complete: bool,
    lifetime: std::marker::PhantomData<&'cxx u8>,
} // something is needed to signal to cpp that a reference was made and one

impl<'cxx> Token<'cxx> /*<'cxx>*/ {
    const TOKEN_ORDERING: Ordering = Ordering::Relaxed;

    pub fn new(
        chars: &'cxx [u8],
        /*file:AtomicPtr<super::super::shared::file_data::File>, */
        column: usize,
        row: usize,
        complete: bool,
    ) -> Self {
        Token {
            //file,
            chars,
            column,
            row,
            complete,
            lifetime: std::marker::PhantomData,
        }
    }

    // fn increnment_references(&self) {
    //     self.file.load(Self::TOKEN_ORDERING).read().increment_references();
    // }

    // pub fn file_ptr(&self) -> &AtomicPtr<super::super::shared::file_data::File<'cxx>> {
    //     self.file.load(TOKEN_ORDERING)
    //     self.file.store(ptr, order)
    // }

    #[inline(always)]
    pub fn as_str(&self) -> &'cxx str {
        // Safe as we only have valid utf8 tokens
        unsafe { std::str::from_utf8_unchecked(self.chars) }
    }

    #[inline(always)]
    pub fn as_slice(&self) -> &'cxx [u8] {
        self.chars
    }
}

// impl<'cxx> Drop for Token<'cxx> {
//     fn drop(&mut self) {
//         unsafe { self.file.load(Self::TOKEN_ORDERING).read().decrement_references()};
//     }
// }
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

                (first) => {
                    helix_proc::get_first_char_pattern!($patten)
                };

                (u16$phantom:literal) => {
                    helix_proc::convert_bytes_to_u16!($patten)
                };

                (match $ch:expr) => {
                    matches!($ch, $name!())
                };


                (raw$phantom:literal) => {
                    helix_proc::raw!($patten)
                };

                (u16 match $ch:expr) => {
                    matches!($ch, $name!(u16 ""))
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

// todo: formatter should be able to format macros, a macro can define what formatting to use
token_patterns! {

    delimiters: b'{' | b'}' | b'(' | b')' | b';' | b'!' | b'=' | b'|',

    newline: b'\n',
    other_whitespace: b'\t' | b'\n' | b'\x0C' | b'\r' | b' ',

    whitespace: other_whitespace!() | newline!(),




    string_quotes: b'"',
    char_quotes: b'\'',

    quotes: string_quotes!() | char_quotes!(),

    backslash: b'\\',

    // raw | binary | unicode | formatted
    quote_prefixes: b'r'|b'b'| b'u'| b'f',

    // escape sequences
    // should we include regexp escape sequences in helix?
    // newline | carriage return | tab | null | hex | unicode | unicode extended | single quote
    escape_sequences: b"\\n" | b"\\r" | b"\\t" | b"\\0" | b"\\x" | b"\\u" | b"\\U" | b"\\'",


    two_char_operators: b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
    b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
    b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
    b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
    b"::" | b"||" | b"++" | b"__" | b"?=",



    three_char_operators: b"===" | b"!==" | b"..." | b"r//" | b"r**" | b"r<<" | b"r>>" | b"//=" | b"**=" | b"<<=" |
    b">>=" | b"??" | b"|:",

    // hex: numeric!() | b'a'..=b'f' | b'A'..=b'F',


    // method_call: b'.',
    // static_method_call: b"::",
    // method_error: b'?',


    // fn_definition_error_suffix: b'?',
    // fn_definition_suffixes: fn_definition_error_suffix!(),


    // fn_definition: b"fn",

    // // used for match statements
    // implies: b"=>",

    // fn_error: b'?',
    // // idk abt this copiolet gave this : fn_error_eq: b"?=",

    // fn_return: b"->",

    // fn_param_start: b'(',
    // fn_param_end: b')',

    // scope_start: b'{',
    // scope_end: b'}',

    // array_start: b'[',
    // array_end: b']',

    // tuple_start: b'(',
    // tuple_end: b')',

    // // make thing that does this

    // // numeric_prefix : {
    // //     // all of these patterns are in numeric prefix and also their own patterns that  can be used...
    // //     ordinal: b'o',
    // // }


    // // idk about big O
    // ordinal_numeric:b'o' ,

    // // little b is
    // binary_numeric: b'b',

    // // u is unicode. u4u32 would make it into the respective type from that char to the number
    // unicode_numeric: b'u',
    // numeric_hex: b'x' | b"0x",

    // big_endian: b'b',
    // little_endian: b'l',
    // native_endian: b'n',

    // numeric_endian_infixes: big_endian!() | little_endian!() | native_endian!(),
    // numeric_prefixes: ordinal!() |  binary_numeric!(),

    underscore: b'_',
    uppercase: b'A'..=b'Z',
    lowercase: b'a'..=b'z',
    numeric: b'0'..=b'9',

    alphanumeric: lowercase!() | uppercase!() | numeric!(),

    identifier_first_char: lower_case!() | uppercase!() | underscore!(),

    identifier: identifier_first_char!() | numeric!(),

    punctuation: b'!'..=b'/'|b':'..=b'@'|b'['..=b'`'|b'{'..=b'~',

    //TODO: make work -> operators: two_char_operators!() | three_char_operators!()

    operators:  b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
    b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
    b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
    b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
    b"::" | b"||" | b"++" | b"__" | b"?=" | b"===" | b"!==" | b"..." | b"r//" | b"r**" | b"r<<" | b"r>>" | b"//=" | b"**=" | b"<<=" |
    b">>=" | b"??" | b"|:"



}

//
//const ALLOWED_STRING_PREFIXES: [u8; 4] = [];

// TODO USE BYTES CRATE IF ITS FASTER TO ITERATE OVER BYTES

#[derive(Debug, Clone)]
pub struct Tokenizer<'cxx> {
    slice_head: *const u8,
    column: usize,
    row: usize,

    window_tail: *const u8,
    window_head: *const u8,

    // if a token is complete
    // or store last token type
    // last_token: *const Token<'cxx>,
    token_column: usize,
    token_row: isize,

    slice_tail: *const u8,
    lifetime: std::marker::PhantomData<&'cxx u8>,
}

impl<'cxx> Tokenizer<'cxx> {
    const DEFAULT_COLUMN: usize = 0;
    const DEFAULT_ROW: isize = -1;
    const DEFAULT_CHAR: u8 = b'\0';
    const DEFAULT_LAST_TYPE: TokenType = TokenType::None;

    // cpp could straight up pass in a u8 slice instead of a string slice
    pub fn new(chars: &'cxx [u8]) -> Self {
        Tokenizer {
            slice_head: chars.as_ptr(),
            slice_tail: unsafe { chars.as_ptr().add(chars.len()) },
            window_head: chars.as_ptr(),
            window_tail: chars.as_ptr(),
            row: Self::DEFAULT_ROW,
            column: Self::DEFAULT_COLUMN,
            token_column: Self::DEFAULT_COLUMN,
            token_row: Self::DEFAULT_ROW,
            // points to the location after the last char
            lifetime: std::marker::PhantomData,
        }
    }

    #[inline(always)]
    /// Allows the tokenizer to be reset with new content without reallocation,
    pub fn reset(&mut self, content: &'cxx [u8]) {
        self.slice_head = content.as_ptr();
        self.slice_tail = unsafe { content.as_ptr().add(content.len()) };
        self.window_tail = content.as_ptr();
        self.window_head = content.as_ptr();
        self.row = Self::DEFAULT_ROW;
        self.reset_column();
    }

    /// A dirty estimate of the number of tokens in the content
    pub fn fast_estimate_number_of_tokens(content: &str) -> usize {
        let mut count = 0;
        let mut in_string = false;
        let mut prev_char = b'\0';

        for c in content.as_bytes() {
            match c {
                quotes!() if in_string & (prev_char != backslash!(raw "")) => {
                    // Handle string closure and escape character
                    in_string = false;
                }
                quotes!() => {
                    // Handle string opening
                    in_string = true;
                    count += 1; // Count the entire string as one token
                }
                alphanumeric!() | punctuation!() | underscore!() => count += 1,

                _ => {}
            }
            prev_char = *c;
        }
        count
    }

    // there is prob a trait for this

    pub fn gather_all_tokens(&mut self, content: &str) -> Vec<Token> {
        let mut tokens = Vec::with_capacity(Self::fast_estimate_number_of_tokens(content));

        while let Some(token) = self.next() {
            tokens.push(token);
        }

        tokens
    }

    fn window_len(&self) -> usize {
        unsafe { self.window_tail as usize - self.window_head as usize }
    }

    // nested inlining do not inline: feature for helix

    #[inline(always)]
    fn peek_ahead_n(&self, n: usize) -> u8 {
        unsafe { *self.window_tail.add(n) }
    }

    fn peek_ahead(&self) -> u8 {
        self.peek_ahead_n(1)
    }

    #[inline(always)]
    fn get_slice_from_tail_window(&self, to: usize) -> &[u8] {
        unsafe { &*slice_from_raw_parts(self.window_tail, to) }
    }

    //  #[inline(always)]
    //     fn peek_behind_slice(&self, to: usize) -> &[u8] {
    //         return if self.in_bounds(to) {
    //             unsafe { &*slice_from_raw_parts(self.window_tail.add(1), to) }

    //             Self::DEFAULT_CHAR
    //         } else {
    //             &[]
    //         };
    //     }

    #[inline(always)]
    fn peek_behind(&self) -> u8 {
        // check if the window is empty so it does not go out of bounds
        return if self.window_is_empty() {
            Self::DEFAULT_CHAR
        } else {
            unsafe { self.window_tail.sub(1).read() }
        };
    }

    // Head methods

    #[inline(always)]
    fn increment_window_tail(&mut self) {
        self.increment_window_tail_n(1);
    }

    #[inline(always)]
    fn increment_cursor(&mut self) {
        self.increment_window_tail();
        self.increment_column();
    }

    #[inline(always)]
    fn increment_cursor_n(&mut self, n: usize) {
        self.increment_window_tail_n(n);
        self.increment_column_n(n);
    }

    // Column and head methods

    #[inline(always)]
    fn increment_window_tail_n(&mut self, n: usize) {
        self.window_tail = unsafe { self.window_tail.add(n) };
    }

    #[inline(always)]
    fn increment_column_n(&mut self, n: usize) {
        self.column += n;
    }

    // Tail methods

    #[inline(always)]
    fn increment_head(&mut self) {
        self.increment_head_n(1);
    }

    #[inline(always)]
    fn increment_head_n(&mut self, n: usize) {
        unsafe { self.window_head.add(n) };
    }

    // #[inline(always)]
    // fn increment_window_n(&mut self, n: usize) {
    //     // Move the head
    //     self.increment_tail_n(n);
    //     self.increment_peek_head_n(n);

    //     // Set the tail to the old head
    // }

    // #[inline(always)]
    // fn increment_window(&mut self) {
    //     self.increment_window_n(1);
    // }

    #[inline(always)]
    fn at_end(&self) -> bool {
        std::ptr::addr_eq(self.window_tail, self.slice_tail)
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

    // not needed prob slow
    #[inline(always)]
    fn match_slice(&self, slice: &[u8]) -> bool {
        self.get_slice_from_tail_window(slice.len()) == slice
    }

    #[inline(always)]
    fn reset_column(&mut self) {
        self.column = Self::DEFAULT_COLUMN;
    }

    #[inline(always)]
    fn window_is_empty(&self) -> bool {
        std::ptr::addr_eq(self.window_head, self.window_tail)
    }

    #[inline(always)]
    fn peek_behind_char(&self) -> char {
        self.peek_behind() as char
    }
    #[inline(always)]

    fn window_tail_char(&self) -> char {
        self.window_tail() as char
    }
    #[inline(always)]

    fn peek_ahead_char(&self) -> char {
        self.peek_ahead() as char
    }
    #[inline(always)]

    fn tail_pretty(&self) -> char {
        self.window_tail() as char
    }
    #[inline(always)]

    fn head_pretty(&self) -> char {
        self.window_head() as char
    }
    #[inline(always)]

    fn char_head_pretty(&self) -> char {
        self.window_head() as char
    }
    #[inline(always)]
    fn window_head(&self) -> u8 {
        unsafe { self.window_head.read() }
    }

    #[inline(always)]
    fn window_head_pretty(&self) -> char {
        self.window_head() as char
    }

    #[inline(always)]
    fn window_tail(&self) -> u8 {
        unsafe { self.window_tail.read() }
    }
    #[inline(always)]

    fn window_tail_pretty(&self) -> char {
        self.window_tail() as char
    }
    #[inline(always)]
    fn in_bounds(&self, n: usize) -> bool {
        self.window_tail as usize + n <= self.slice_tail as usize
    }

    fn window_head_index(&self) -> usize {
        self.window_head as usize - self.slice_head as usize
    }

    fn window_tail_index(&self) -> usize {
        self.window_tail as usize - self.slice_head as usize
    }

    fn reset_window_head(&mut self) {
        self.window_head = self.window_tail
    }
    #[inline(always)]
    fn make_token(&self, complete: bool) -> Token<'cxx> {
        Token::new(
            unsafe { &*slice_from_raw_parts(self.window_head as *const u8, self.window_len()) }, //TODO: unchecked
            self.token_column,
            self.token_row,
            complete, // TODO: if its incomplete return somewhere else
        )
    }

    #[inline(always)]
    fn skip_one(&mut self) {
        self.increment_cursor();
        self.reset_window_head();
    }
}

impl<'cxx> Iterator for Tokenizer<'cxx> {
    type Item = Token<'cxx>;

    #[inline(always)]
    fn next(&mut self) -> Option<Self::Item> {
        'outer: loop {
            // if the tail is at the end of the input return None
            if self.at_end() {
                return if self.window_is_empty() {
                    None
                } else {
                    Some(self.make_token(false))
                };
            };

            // if peek fails the end of the input has been reached, so there is no need to check.

            dbg_trace!(
                "(l '{}' c '{}' p '{}' h {} t {}: ",
                self.peek_behind_char(),
                self.window_tail_char(),
                self.peek_ahead_char(),
                self.window_head_index(),
                self.window_tail_index(),
            );

            dbg_trace!("0");

            // peeks the next char, could not use peek method due to
            match self.window_tail() {
                // Whitespace
                whitespace @ whitespace!() => {
                    dbg_trace!("1");
                    match whitespace {
                        newline!() => {
                            dbg_trace!("2");
                            self.increment_row();
                        }
                        _ => self.increment_column(),
                    }

                    self.skip_one();
                    dbg_trace!("3");

                    #[cfg(feature = "debug-trace")]
                    print!(": skipped!)");
                }

                // Operators

                // these should peek and match indiv

                // check for the first char of an operator to avoid checking all operators
                operators!(first)
                    if {
                        dbg_trace!("4");
                        self.in_bounds(3)
                    } && {
                        dbg_trace!("5");
                        three_char_operators!(match self.get_slice_from_tail_window(3))
                    } =>
                {
                    dbg_trace!("6");
                    break self.increment_cursor_n(2);
                }

                operators!(first)
                    if {
                        dbg_trace!("7");

                        self.in_bounds(2)
                    } && two_char_operators!(u16 match unsafe {

                    dbg_trace!("8");
                    (self.window_tail as *const u16).read()
                    }) =>
                {
                    dbg_trace!("9");
                    break self.increment_cursor_n(1);
                }

                // Delimiters
                delimiters!() => {
                    dbg_trace!("a");
                    // self.decrement_head(); // change later

                    if !self.window_is_empty() {
                        dbg_trace!("b");
                        self.increment_cursor();
                    }

                    break;
                }

                // Single char operators

                // Characters
                // TODO: Finish this
                // char_quotes!() => {
                //     dbg_trace!("c");
                // }

                // change this macro from string quotes to char

                // Strings
                // quote @ string_quotes!() => {
                quote @ quotes!() => {
                    // if string is not complete it should return a type
                    dbg_trace!("d");

                    if !self.window_is_empty() & !quote_prefixes!(match self.peek_behind()) {
                        dbg_trace!("e");
                        break;
                    }

                    self.increment_cursor();

                    // Push the starting quote
                    loop {
                        // Bounds check the ptr
                        if self.at_end() {
                            return Some(self.make_token(false));
                        }

                        // todo make ptr look up table for all match statements

                        // peak should error or something
                        match self.window_tail() {
                            // Newline
                            newline!() => {
                                dbg_trace!("f");
                                self.increment_row()
                            }

                            // Backslash
                            backslash!() if self.in_bounds(1) && (self.peek_ahead() == quote) => {
                                self.increment_cursor();
                                dbg_trace!("g");
                            }

                            // idk if this arm is correct
                            c if (c == quote) => {
                                dbg_trace!("h");
                                break 'outer;
                            }

                            _ => {
                                dbg_trace!("i");
                            }
                        }

                        self.increment_cursor();
                    }
                }

                // Characters
                _ => {
                    dbg_trace!("j");

                    // Check for string pre fix
                    match self.peek_ahead() {
                        // TODO Remove this part
                        quotes!() if quote_prefixes!(match self.window_tail()) => {
                            dbg_trace!("k");
                            self.increment_cursor();
                        }
                        // TODO: Remove this part and simplify it
                        whitespace!() | delimiters!() => {
                            dbg_trace!("l");
                            break;
                        }

                        _ => self.increment_cursor(),
                    }

                    dbg_trace!("m");
                }
            }
        }

        #[cfg(feature = "debug-trace")]
        println!(
            " :h {} t {})",
            self.window_head_index(),
            self.window_tail_index(),
        );

        //println!("\nTOKEN FINISH: {}", std::str::from_utf8(&token).unwrap());

        self.increment_window_tail();
        let token = Some(self.make_token(true));

        // Reset the last token column and row to the current column and row
        self.token_column = self.column;
        self.token_row = self.row;

        // Set the tail to the head to clear the window
        self.reset_window_head();

        token
    }
}

// TODO: make a macro that converts the patten matching of rust to simd instructions
// so it looks like pattrn matching when using it in code, but its actually using simd instructions

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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_determine_tokens() {
        let content = //std::hint::black_box(
            "fn ===main() {
            println!(\"Hello, \\u{32}\n\\nworld!\");\"Hello; \\\" world!\"
            if true != false {
                let xyz_99_yoMama = 5 | b\"some\" | 'c'| b\'s\';
            }
        }"; 
        // TODO: fix the issue when this is added to the end of the thing
        // \"2

        //);
        let mut tokenizer = Tokenizer::new(content.as_bytes());

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
            "\"Hello, \\u{32}\n\\nworld!\"",
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
            "|",
            "b\'s\'",
            ";",
            "}",
            "}",
        ];

        let mut instant = crate::PrimedInstant::new();

        instant.prime();

        for index in 0..expected.len() {
            instant.start();
            let token = match tokenizer.next() {
                Some(token) => token,
                None => break,
            };
            instant.end();
            println!(
                "\nr:{} c:{} t:'{}' e:{:?}",
                token.row,
                token.column,
                token.as_str(),
                instant.elapsed
            );
            assert_eq!(token.as_str(), expected[index]);
        }

        tokenizer = Tokenizer::new(content.as_bytes());

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

//                 break;
//             };
//         }
//     };
// }

// make these better based on the other macro and or a proc macro
// match_operator!(two,2,"8");
// match_operator!(three,3,"9");
