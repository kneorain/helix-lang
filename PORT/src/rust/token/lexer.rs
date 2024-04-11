use std::{
    ptr::{self, addr_of_mut, slice_from_raw_parts},
    sync::atomic::{AtomicPtr, Ordering},
};

use crate::rust::debug_counter::dbg_trace;

#[derive(Debug)]
pub struct Token<'cxx> {
    //file: AtomicPtr<super::super::shared::file_data::File<'cxx>>,
    sub_tokens: &'cxx [u8],
    column: usize,
    row: isize,
    complete: bool,
}

impl<'cxx> Token<'cxx> {
    const TOKEN_ORDERING: Ordering = Ordering::Relaxed;

    pub fn new(
        chars: &'cxx [u8],
        /*file:AtomicPtr<super::super::shared::file_data::File>, */
        column: usize,
        row: isize,
        complete: bool,
    ) -> Self {
        Token {
            //file,
            sub_tokens: chars,
            column,
            row,
            complete,
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
        unsafe { std::str::from_utf8_unchecked(self.sub_tokens) }
    }

    #[inline(always)]
    pub fn as_slice(&self) -> &'cxx [u8] {
        self.sub_tokens
    }

    pub fn is_complete(&self) -> bool {
        self.complete
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

    pub fn complete(&mut self, other: Token<'cxx>) {
        self.sub_tokens = unsafe {
            &*slice_from_raw_parts(
                self.sub_tokens.as_ptr(),
                self.sub_tokens.len() + other.sub_tokens.len(),
            )
        };
        self.complete = true;
    }
}

macro_rules! token_patterns {
    ($($name:ident:  $patten:pat),*) => {
        $(
            macro_rules! $name {
                () => {
                    $patten
                };

                (first_char) => {
                    helix_proc::get_first_char_pattern!($patten)
                };

                (u16$phantom:literal) => {
                    helix_proc::convert_bytes_to_u16!($patten)
                };

                (contains $ch:expr) => {
                    matches!($ch, $name!())
                };


                (raw$phantom:literal) => {
                    helix_proc::raw!($patten)
                };

                (contains $ch:expr as u16) => {
                    matches!($ch, $name!(u16 ""))
                };
            }
        )*
    }

}

token_patterns! {

    delimiters: b'{' | b'}' | b'(' | b')' | b';' | b'!' | b'=' | b'|',

    newline: b'\n',
    other_whitespace: b'\t' | b'\x0C' | b'\r' | b' ',

    whitespace: other_whitespace!() | newline!(),

    string_quotes: b'"',
    char_quotes: b'\'',

    quotes: string_quotes!() | char_quotes!(),

    backslash: b'\\',

    // raw | binary | unicode | formatted
    quote_prefixes: b'r'|b'b'| b'u'| b'f',

    two_len_ops: b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
    b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
    b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
    b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
    b"::" | b"||" | b"++" | b"__" | b"?=",



    three_len_ops: b"===" | b"!==" | b"..." | b"r//" | b"r**" | b"r<<" | b"r>>" | b"//=" | b"**=" | b"<<=" |
    b">>=" | b"??" | b"|:",

    uppercase: b'A'..=b'Z',
    lowercase: b'a'..=b'z',
    numeric: b'0'..=b'9',

    alphanumeric: lowercase!() | uppercase!() | numeric!(),

    punctuation: b'!'..=b'/'|b':'..=b'@'|b'['..=b'`'|b'{'..=b'~',

    operators:  b"==" | b"!=" | b"<=" | b">=" | b"//" | b"**" |
    b"<<" | b">>" | b"r+" | b"r-"| b"r*" | b"r/" | b"r%" | b"r&" | b"r|" |
    b"r^" | b"+=" | b"-=" | b"*=" | b"/=" | b"%=" | b"&=" | b"|=" | b"^=" |
    b"=>" | b"@=" | b"->" | b"<-" | b"<=" | b">=" | b"&&" | b"--" |
    b"::" | b"||" | b"++" | b"?=" | b"===" | b"!==" | b"..." | b"r//" | b"r**" | b"r<<" | b"r>>" | b"//=" | b"**=" | b"<<=" |
    b">>=" | b"??" | b"|:"

}

#[derive(Debug, Clone)]
pub struct Tokenizer<'cxx> {
    //
    slice_head: *const u8,
    slice_tail: *const u8,

    // The window head is the start of the current token
    window_head: *const u8,
    window_tail: *const u8,

    row: isize,
    column: usize,

    token_row: isize,
    token_column: usize,

    /// Used to mark the lifetime and nothing else.
    lifetime: std::marker::PhantomData<&'cxx u8>,
}

impl<'cxx> Tokenizer<'cxx> {
    const DEFAULT_COLUMN: usize = 0;
    const DEFAULT_ROW: isize = -1;
    const DEFAULT_CHAR: u8 = b'\0';

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
        self.lifetime = std::marker::PhantomData;
        self.column_reset();
    }

    /// A dirty estimate of the number of tokens in the content
    pub fn fast_estimate_number_of_tokens(content: &'cxx str) -> usize {
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
                alphanumeric!() | punctuation!() => count += 1,

                _ => {}
            }
            prev_char = *c;
        }
        count
    }

    // There might be a trait for this.
    pub fn gather_all_tokens(&mut self, content: &'cxx str) -> Vec<Token> {
        let mut tokens = Vec::with_capacity(Self::fast_estimate_number_of_tokens(content));

        while let Some(token) = self.next() {
            tokens.push(token);
        }

        tokens
    }

    // Window methods - These methods are used to move the window head and tail

    fn window(&self) -> &'cxx [u8] {
        unsafe { &*slice_from_raw_parts(self.window_head as *const u8, self.window_len()) }
    }

    #[inline(always)]
    /// Returns the value of the window head
    fn window_head(&self) -> u8 {
        unsafe { self.window_head.read() }
    }

    #[inline(always)]
    /// Increments the window head by one
    pub fn window_head_increment(&mut self) {
        self.window_head_increment_n(1)
    }

    #[inline(always)]
    /// Increments the window head by n
    pub fn window_head_increment_n(&mut self, n: usize) {
        self.window_head = unsafe { self.window_head.add(n) }
    }

    #[inline(always)]
    /// Returns the index of the window head in the slice
    fn window_head_index(&self) -> usize {
        self.window_head as usize - self.slice_head as usize
    }

    #[inline(always)]
    /// Resets the window head to the window tail
    fn window_head_reset(&mut self) {
        self.window_head = self.window_tail
    }

    #[inline(always)]
    /// Returns the index of the window head in the slice
    fn window_tail<T>(&self) -> T {
        unsafe { (self.window_tail as *const T).read() }
    }

    #[inline(always)]
    /// Increments the window tail by one
    pub fn window_tail_increment(&mut self) {
        self.window_tail_increment_n(1);
    }

    #[inline(always)]
    /// Increments the window tail by n
    pub fn window_tail_increment_n(&mut self, n: usize) {
        self.window_tail = unsafe { self.window_tail.add(n) };
    }

    #[inline(always)]
    /// Returns the index of the window tail in the slice
    fn window_tail_index(&self) -> usize {
        self.window_tail as usize - self.slice_head as usize
    }

    #[inline(always)]
    /// Returns a slice from the window tail to the given index
    fn window_tail_slice(&self, to: usize) -> &[u8] {
        unsafe { &*slice_from_raw_parts(self.window_tail, to) }
    }

    #[inline(always)]
    /// Returns the length of the window
    fn window_len(&self) -> usize {
        self.window_tail as usize - self.window_head as usize
    }

    #[inline(always)]
    /// Checks if the window tail is within the bounds of the slice
    fn is_window_in_bounds(&self, n: usize) -> bool {
        self.window_tail as usize + n <= self.slice_tail as usize
    }

    #[inline(always)]
    /// Checks if the window is empty
    pub fn is_window_empty(&self) -> bool {
        std::ptr::addr_eq(self.window_head, self.window_tail)
    }

    // Cursor methods - These methods are used to move the window tail and column

    #[inline(always)]
    /// Increments the window tail and column by one
    pub fn increment_cursor(&mut self) {
        self.window_tail_increment();
        self.column_increment();
    }

    #[inline(always)]
    /// Increments the window tail and column by n
    pub fn increment_cursor_by_n(&mut self, n: usize) {
        self.window_tail_increment_n(n);
        self.column_increment_n(n);
    }

    #[inline(always)]
    /// Returns the value one character ahead of the window tail
    fn peek_ahead_window(&self) -> u8 {
        self.peek_ahead_n(1)
    }

    #[inline(always)]
    /// Returns the value n characters ahead of the window tail
    fn peek_ahead_n(&self, n: usize) -> u8 {
        unsafe { *self.window_tail.add(n) }
    }

    #[inline(always)]
    /// Returns the value one character behind the window tail
    fn peek_behind_tail(&self) -> u8 {
        // check if the window is empty so it does not go out of bounds
        return if self.is_window_empty() {
            Self::DEFAULT_CHAR
        } else {
            unsafe { self.window_tail.sub(1).read() }
        };
    }

    #[inline(always)]
    /// Skips the current sub token
    fn skip_sub_token(&mut self) {
        self.increment_cursor();
        self.window_head_reset();
    }

    #[inline(always)]
    /// Checks if the slice is empty
    pub fn is_slice_empty(&self) -> bool {
        std::ptr::addr_eq(self.window_tail, self.slice_tail)
    }

    // Column methods - These methods are used to move the column

    // TODO: Fix column and row increments.
    #[inline(always)]
    /// Increments the column by one
    pub fn column_increment(&mut self) {
        self.column += 1;
    }

    #[inline(always)]
    pub fn column_increment_n(&mut self, n: usize) {
        self.column += n;
    }

    #[inline(always)]
    /// Resets the column to the default column
    pub fn column_reset(&mut self) {
        self.column = Self::DEFAULT_COLUMN;
    }

    // Row methods - These methods are used to move the row

    #[inline(always)]
    /// Increments the row by one
    pub fn increment_row(&mut self) {
        self.row_increment_n(1)
    }

    #[inline(always)]
    /// Resets the row to the default row and increments the row by one
    pub fn row_increment_n(&mut self, n: isize) {
        self.row += n;
        self.column_reset();
    }

    #[inline(always)]
    /// Creates a new token from the current window
    fn next_token(&mut self, complete: bool) -> Token<'cxx> {
        let token = Token::new(self.window(), self.token_column, self.token_row, complete);
        self.window_head_reset();
        token
    }
}

impl<'cxx> Iterator for Tokenizer<'cxx> {
    type Item = Token<'cxx>;

    #[inline(always)]
    fn next(&mut self) -> Option<Self::Item> {
        'outer: loop {
            if self.is_slice_empty() {
                return if self.is_window_empty() {
                    None
                } else {
                    Some(self.next_token(false))
                };
            };

            match self.window_tail::<u8>() {
                // Whitespace
                whitespace @ whitespace!() => {
                    match whitespace {
                        newline!() => self.increment_row(),
                        _ => self.column_increment(),
                    }
                    self.skip_sub_token();
                }

                // Operators

                // Three character operators
                operators!(first_char)
                    if self.is_window_in_bounds(3)
                        && three_len_ops!(contains self.window_tail_slice(3)) =>
                {
                    break self.increment_cursor_by_n(2)
                }

                // Two character operators
                operators!(first_char)
                    if self.is_window_in_bounds(2)
                        && two_len_ops!(contains self.window_tail::<u16>() as u16) =>
                {
                    break self.increment_cursor_by_n(1);
                }

                // Delimiters
                delimiters!() => {
                    if !self.is_window_empty() {
                        self.increment_cursor();
                    }
                    break;
                }

                // Quotes
                quote @ quotes!() => {
                    if !self.is_window_empty() & !quote_prefixes!(contains self.peek_behind_tail()) {
                        break;
                    }

                    self.increment_cursor();

                    loop {
                        if self.is_slice_empty() {
                            return Some(self.next_token(false));
                        }

                        match self.window_tail::<u8>() {
                            newline!() => self.increment_row(),

                            backslash!()
                                if self.is_window_in_bounds(1)
                                    && self.peek_ahead_window() == quote =>
                            {
                                self.increment_cursor()
                            }

                            char if char == quote => break 'outer,

                            _ => {}
                        }

                        self.increment_cursor();
                    }
                }

                // Characters
                _ => {
                    match self.peek_ahead_window() {
                        // TODO Remove this part
                        quotes!() if quote_prefixes!(contains self.window_tail::<u8>()) => {
                            self.increment_cursor();
                        }

                        // TODO: Remove this part and simplify it
                        whitespace!() | delimiters!() => break,

                        _ => self.increment_cursor(),
                    }
                }
            }
        }

        self.increment_cursor();

        let token = Some(self.next_token(true));

        // Reset the last token column and row to the current column and row
        self.token_column = self.column;
        self.token_row = self.row;

        // Set the tail to the head to clear the window
        self.window_head_reset();

        token
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_determine_tokens_small() {
        use crate::tests::tokenizer::small_test::{CONTENT, EXPECTED};

        determine_tokens(CONTENT, EXPECTED);
    }

    #[test]
    fn test_determine_tokens_large() {
        use crate::tests::tokenizer::large_test::{CONTENT, EXPECTED};

        determine_tokens(CONTENT, EXPECTED);
    }

    fn determine_tokens(content: &'static str, expected: &'static [&'static str]) {
        let mut tokenizer = Tokenizer::new(content.as_bytes());

        let mut instant = crate::PrimedInstant::new();

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

        println!("Tokens: {:?}", tokens);
        println!("Total Time to gather: {:?}", elapsed);
    }
}
