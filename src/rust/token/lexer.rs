#![allow(unused_macros)]
#![warn(unreachable_patterns)]
use std::{
    fmt::Debug,
    ptr::slice_from_raw_parts,
    sync::atomic::{Ordering},
};

#[derive(Debug)]
pub struct Token<'cxx> {
    sub_tokens: &'cxx [u8],
    column: usize,
    row: isize,
}

impl<'cxx> Token<'cxx> {
    //const TOKEN_ORDERING: Ordering = Ordering::Relaxed;
    // FIXME: this was unused
    pub fn new(chars: &'cxx [u8], row: isize, column: usize) -> Self {
        Token {
            //file,
            sub_tokens: chars,
            column,
            row,
        }
    }

    #[inline(always)]
    pub fn as_str(&self) -> &'cxx str {
        // Safe as we only have valid utf8 tokens
        unsafe { std::str::from_utf8_unchecked(self.sub_tokens) }
    }

    #[inline(always)]
    pub fn as_slice(&self) -> &'cxx [u8] {
        self.sub_tokens
    }

    pub fn row(&self) -> isize {
        self.row
    }

    pub fn column(&self) -> usize {
        self.column
    }

    pub fn len(&self) -> usize {
        self.sub_tokens.len()
    }

    pub fn extend(&mut self, other: Token<'cxx>) {
        self.sub_tokens = unsafe {
            &*slice_from_raw_parts(
                self.sub_tokens.as_ptr(),
                self.sub_tokens.len() + other.sub_tokens.len(),
            )
        };
    }
}

macro_rules! token_patterns {
    ($($name:ident:  $pattern:pat),*) => {
        $(
            macro_rules! $name {
                () => {
                    $pattern
                };

                (first_char) => {
                    helix_proc::get_first_char_pattern!($pattern)
                };

                (u16$phantom:literal) => {
                    helix_proc::convert_bytes_to_u16!($pattern)
                };

                (contains $ch:expr) => { matches!($ch, $name!()) };

                (raw$phantom:literal) => {helix_proc::raw!($pattern)};
                (contains u16 $ch:expr ) => {
                    matches!($ch, $name!(u16 ""))
                };
            }
        )*
    }

}

token_patterns! {

    // b'>' and b'<' are also delimiters for generics, that will be solved later
    delimiters: b'{' | b'}' | b'(' | b')' | b'[' | b']',

    list_separator: b',',

    scope_separator: b';',

    empty_call: b"()",

    type_separator: b':',

    static_access: b"::",
    instance_access: b'.',

    newline: b'\n',
    other_whitespace: b'\t' | b'\x0C' | b'\r' | b' ',

    whitespace: other_whitespace!() | newline!(),

    string_quotes: b'"',
    char_quotes: b'\'',

    quotes: string_quotes!() | char_quotes!(),

    backslash: b'\\',

    // raw | binary | unicode | formatted
    quote_prefixes: b'r'|b'b'| b'u'| b'f',

    operators_1: b'?' | b'!' | b'='| b'<'|b'>'|b'&'| b'|' | b'+'|b'-'|b'*'|b'/'|b'%'|b'^'|b'@',

    operators_2: b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |b".."|
    b"<<" | b">>" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
    b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
    b"||" | b"++" | b"?="|b"|:" |b"??"
    | b"::" |"()", // TODO: Use static_access!() instead of b"::" and empty_call!() instead of "()" when fixed

    operators_3: b"===" | b"!==" | b"..."  | b"//=" | b"**=" | b"<<=" | b">>="|b"..=",

    uppercase: b'A'..=b'Z',
    lowercase: b'a'..=b'z',
    numeric: b'0'..=b'9',

    alpha: lowercase!() | uppercase!(),

    alphanumeric: alpha!() | numeric!(),

    punctuation: b'!'..=b'/'|b':'..=b'@'|b'['..=b'`'|b'{'..=b'~',

    operators: operator_1!() | operator_2!() | operator_3!()

}

#[derive(Debug, Clone)]
pub struct Tokenizer<'cxx> {
    sub_tokens: &'cxx [u8],
    sub_tokens_start: *const u8,
    sub_tokens_end: *const u8,

    // The window head is the start of the current token
    head: *const u8,
    tail: *const u8,
    incomplete: bool,
    row: isize,

    last_row_index: usize,
}

#[allow(dead_code)]
impl<'cxx> Tokenizer<'cxx> {
    pub const FIRST_ROW: isize = -1;
    pub const DEFAULT_CHAR: u8 = 0;

    pub fn new(chars: &'cxx [u8], starting_row: isize) -> Self {
        Tokenizer {
            sub_tokens: chars,
            sub_tokens_start: chars.as_ptr(),
            sub_tokens_end: unsafe { chars.as_ptr().add(chars.len()) },
            head: chars.as_ptr(),
            tail: chars.as_ptr(),
            row: starting_row,
            incomplete: false,
            last_row_index: 0,
        }
    }

    /// Allows the tokenizer to be reset with new content without reallocation,
    pub fn reset(&mut self, content: &'cxx [u8], starting_row: isize) {
        self.sub_tokens = content;
        self.sub_tokens_start = self.sub_tokens.as_ptr();
        self.sub_tokens_end = unsafe { self.sub_tokens.as_ptr().add(content.len()) };
        self.tail = content.as_ptr();
        self.head = content.as_ptr();
        self.row = starting_row;
        self.incomplete = false;
        self.last_row_index = 0;
    }

    /// A dirty estimate of the number of tokens in the content
    pub fn fast_estimate_number_of_tokens(&self) -> usize {
        let mut count = 0;
        let mut in_string = false;
        let mut prev_char = b'\0';

        for c in self.sub_tokens.iter() {
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
                alphanumeric!() | punctuation!() => count += 1,
                _ => {}
            }
            prev_char = *c;
        }
        count
    }

    // There might be a trait for this.
    pub fn gather_all_tokens(&mut self) -> Vec<Token> {
        let mut tokens = Vec::with_capacity(self.fast_estimate_number_of_tokens());

        while !self.is_empty() {
            tokens.push(self.next_token());
        }

        tokens
    }

    // Window methods - These methods are used to move the window head and tail
    #[inline(always)]
    fn window(&self) -> &'cxx [u8] {
        unsafe { &*slice_from_raw_parts(self.head as *const u8, self.window_len()) }
    }

    /// Returns the value of the window head
    #[inline(always)]
    fn window_head(&self) -> u8 {
        unsafe { self.head.read() }
    }

    /// Increments the window head by one
    #[inline(always)]
    pub fn window_head_increment(&mut self) {
        self.window_head_increment_n(1)
    }

    /// Increments the window head by n
    #[inline(always)]
    pub fn window_head_increment_n(&mut self, n: usize) {
        self.head = unsafe { self.head.add(n) }
    }

    /// Returns the index of the window head in the slice
    #[inline(always)]
    fn window_head_index(&self) -> usize {
        self.head as usize - self.sub_tokens_start as usize
    }

    /// Resets the window head to the window tail
    #[inline(always)]
    fn window_head_reset(&mut self) {
        self.head = self.tail
    }

    /// Returns the index of the window head in the slice
    #[inline(always)]
    fn window_tail<T>(&self) -> T {
        unsafe { (self.tail as *const T).read() }
    }

    /// Increments the window tail by one
    #[inline(always)]
    pub fn increment_tail(&mut self) {
        self.increment_tail_window_n(1);
    }

    /// Increments the window tail by n
    #[inline(always)]
    pub fn increment_tail_window_n(&mut self, n: usize) {
        self.tail = unsafe { self.tail.add(n) };
    }

    /// Returns the index of the window tail in the slice
    #[inline(always)]
    fn window_tail_index(&self) -> usize {
        self.tail as usize - self.sub_tokens_start as usize
    }

    /// Returns a slice from the window tail to the given index
    #[inline(always)]
    fn window_tail_slice(&self, to: usize) -> &[u8] {
        unsafe { &*slice_from_raw_parts(self.tail, to) }
    }

    /// Returns the length of the window
    #[inline(always)]
    fn window_len(&self) -> usize {
        self.tail as usize - self.head as usize
    }

    /// Checks if the window tail is within the bounds of the slice
    #[inline(always)]
    fn is_window_in_bounds(&self, n: usize) -> bool {
        self.tail as usize + n <= self.sub_tokens_end as usize
    }

    /// Checks if the window is empty
    #[inline(always)]
    pub fn is_window_empty(&self) -> bool {
        std::ptr::addr_eq(self.head, self.tail)
    }

    /// Returns the value one character ahead of the window tail
    #[inline(always)]
    fn peek_ahead_window(&self) -> u8 {
        self.peek_ahead_n(1)
    }

    #[inline(always)]
    /// Returns the value n characters ahead of the window tail
    fn peek_ahead_n(&self, n: usize) -> u8 {
        unsafe { self.tail.add(n).read() }
    }

    /// Returns the value one character behind the window tail
    #[inline(always)]
    fn peek_behind_tail(&self) -> u8 {
        // check if the window is empty so it does not go out of bounds
        return if self.is_window_empty() {
            Self::DEFAULT_CHAR
        } else {
            unsafe { self.tail.sub(1).read() }
        };
    }

    /// Skips the current sub token
    #[inline(always)]
    fn skip_sub_token(&mut self) {
        self.increment_tail();
        self.window_head_reset();
    }

    /// Checks if the slice is empty
    #[inline(always)]
    pub fn is_empty(&self) -> bool {
        std::ptr::addr_eq(self.tail, self.sub_tokens_end)
    }

    // Row methods - These methods are used to move the row

    /// Increments the row by one
    #[inline(always)]
    pub fn increment_row(&mut self) {
        // Simplified from:
        self.last_row_index = self.window_head_index() - self.window_len();
        self.row += 1;
    }

    #[inline(always)]
    fn slice_from_head_to(&self, to: usize) -> &'cxx [u8] {
        unsafe { &*slice_from_raw_parts(self.head, to) }
    }

    /// Creates a new token from the current window
    #[inline(always)]
    fn create_next_token(&mut self) -> Token<'cxx> {
        //dbg!((self.window_head_index(), self.last_row_index));

        let token = Token::new(
            self.window(),
            self.row,
            self.window_head_index() - self.last_row_index,
        );

        self.window_head_reset();
        token
    }

    fn next_token(&mut self) -> Token<'cxx> {
        'outer: loop {
            match self.window_tail::<u8>() {
                // Whitespace
                whitespace @ whitespace!() => {
                    self.skip_sub_token();
                    
                    if whitespace == newline!(raw "") {
                        self.increment_row();
                    }
                }

                // Operators

                // Two character operators

                // Three character operators
                operators_3!(first_char)
                    if self.is_window_in_bounds(3)
                        && operators_3!(contains self.window_tail_slice(3)) =>
                {
                    break self.increment_tail_window_n(2);
                }

                operators_2!(first_char)
                    if self.is_window_in_bounds(2)
                        && operators_2!(contains u16 self.window_tail::<u16>() ) =>
                {
                    break self.increment_tail_window_n(1);
                }

                // Delimiters and one len ops
                delimiters!()
                | operators_1!()
                | scope_separator!()
                | type_separator!()
                | instance_access!()
                | list_separator!() => {
                    if !self.is_window_empty() {
                        self.increment_tail()
                    }
                    break;
                }
                // Quotes
                quote @ quotes!() => {
                    while !self.is_empty() {
                        self.increment_tail();
                        match self.window_tail::<u8>() {
                            newline!() => {
                                self.increment_row();
                                // Temp fix for newlines in strings
                                // as this fixes the column calculation
                                self.last_row_index -= 2;
                            }
                            backslash!()
                                if self.is_window_in_bounds(1)
                                    && self.peek_ahead_window() == quote =>
                            {
                                self.increment_tail()
                            }
                            char if char == quote => break 'outer,
                            _ => {}
                        }
                    }
                    self.incomplete = true;
                    return self.create_next_token();
                } // End of quotes

                // TODO: parse this out as it
                // identifier @ alphanumeric!()| => {
                //     loop {
                //         if self.is_slice_empty() {
                //             return Some(self.next_token(false));
                //         }

                //         match self.window_tail::<u8>() {
                //             alphanumeric!() => self.increment_cursor(),
                //             _ => break,
                //         }
                //     }
                // }

                // Characters
                _ => match self.peek_ahead_window() {
                    quotes!() if quote_prefixes!(contains self.peek_behind_tail()) => {
                        self.increment_tail()
                    },
                    whitespace!()
                    | delimiters!()
                    // TODO: add this back when it is fixed --- operators!(first_char)
                    | operators_1!(first_char) // TODO: Remove when fixed
                    | operators_2!(first_char) // TODO: Remove when fixed
                    | operators_3!(first_char) // TODO: Remove when fixed
                    | scope_separator!()
                    | type_separator!()
                    | instance_access!()
                    | list_separator!()  => break,

                    _ => self.increment_tail(),
                },
            }
        }
        self.increment_tail();

        self.create_next_token()
    }
}

#[cfg(test)]
mod tests {
    use std::{hint::black_box, slice::Iter};

    use super::*;

    #[test]
    fn test_determine_tokens_small() {
        use crate::tests::tokenizer::small_test::{CONTENT, EXPECTED};

        determine_tokens(CONTENT, EXPECTED.into_iter());
    }

    #[test]
    fn test_determine_tokens_large() {
        use crate::tests::tokenizer::large_test::{CONTENT, EXPECTED};

        determine_tokens(CONTENT, EXPECTED.into_iter());
    }

    fn determine_tokens<'a>(content: &'a str, mut expected: Iter<'a, &'a str>) {
        let mut tokenizer = Tokenizer::new(black_box(content.as_bytes()), Tokenizer::FIRST_ROW);

        let mut instant = crate::PrimedInstant::new();

        instant.prime();

        while !tokenizer.is_empty() {
            let start = std::time::Instant::now();
            let token = tokenizer.next_token();
            let end = start.elapsed();
            println!(
                "\nr:{} c:{} t:'{}' e:{:?} {}",
                token.row,
                token.column,
                token.as_str(),
                end,
                if tokenizer.incomplete {
                    "incomplete"
                } else {
                    ""
                }
            );

            assert_eq!(
                token.as_str().to_owned(),
                expected.next().unwrap().to_owned()
            );
        }

        tokenizer = Tokenizer::new(content.as_bytes(), Tokenizer::FIRST_ROW);

        let start = std::time::Instant::now();

        tokenizer.reset(content.as_bytes(), Tokenizer::FIRST_ROW);

        let tokens = tokenizer.gather_all_tokens();

        let elapsed = start.elapsed();

        //println!("Tokens: {:?}", tokens);
        println!("Total Time to gather: {:?}", elapsed);
    }
}
