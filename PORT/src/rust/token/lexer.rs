use super::{Token, TokenType};
use crate::rust::token::token_value::TokenValue;
use regex::Regex;
use std::sync::Arc;
use std::{fs::File, io::{self, BufRead}, path::Path};

pub struct Lexer {
    file_name: Arc<str>,
    string_re: Regex,
    character_re: Regex,
    numeric_re: Regex,
    identifier_re: Regex,
    delimiter_re: Regex,
    operator_re: Regex,
    comment_re: Regex,
}


/*
COMPILED_RE = re.compile(rf"""
            ([fbur]*"[^"\\]*(?:\\.[^"\\]*)*")                                                                          | # Double quotes strings, including f, b, r, u strings
            ([fbur]*'[^'\\]*(?:\\.[^'\\]*)*')                                                                          | # Single quotes strings, including f, b, r, u strings
            ({back_slash.join(base.COMMENT.split())}[^\n]*)                                                         | # Single line comments (~~)
            ({back_slash.join(base.BLOCK_COMMENT.split())}[\s\S]*?{back_slash.join(base.BLOCK_COMMENT.split())}) | # Multi line comments (~*~ ... ~*~)
            (\b\d+\.\d+\b)                                                                                             | # Decimal numbers
            (\b\w+\b)                                                                                                  | # Words (identifiers, keywords)
            ({'|'.join(base.FAT_CHARACTER)})                                                                        | # Double character operators
            ([\(\){{}};,])                                                                                             | # Single character delimiters
            (\S)                                                                                                       | # Catch other characters
        """, re.MULTILINE | re.VERBOSE)

        
*/

// TODO: Put regexps in a lazy static

impl Lexer {
    pub fn new(file_name: &str) -> Self {
        Self {
            file_name: Arc::from(file_name.to_owned()),
            string_re: Regex::new(r#"([fbur]*"[^"\\]*(?:\\.[^"\\]*)*")"#).unwrap(),
            character_re: Regex::new(r#"([fbur]*'[^'\\]*(?:\\.[^'\\]*)*')"#).unwrap(),
            numeric_re: Regex::new(r#"(\b\d+\.\d+\b|\b\d+[fdui]?\b)"#).unwrap(),
            identifier_re: Regex::new(r#"(\b[a-zA-Z][a-zA-Z0-9_]*\b)"#).unwrap(),
            delimiter_re: Regex::new(r#"([\(\)\{\}\[\];,])"#).unwrap(),
            operator_re: Regex::new(r#"([+\-*/%=&|!<>^])"#).unwrap(),
            comment_re: Regex::new(r#"((?://[^\n]*)|(/\*[\s\S]*?\*/))"#).unwrap(),
        }
    }

    pub fn tokenize(&self) -> io::Result<Vec<Token>> {
        let file = File::open(Path::new(self.file_name.as_ref()))?;
        let reader = io::BufReader::new(file);
        let mut tokens = Vec::new();

        for (line_number, line) in reader.lines().enumerate() {
            let line: Arc<str> = Arc::from(line.unwrap_or_default().as_str().to_owned());
            let line_tokens = self.tokenize_line(line, line_number as i32);
            tokens.extend(line_tokens);
        }

        Ok(tokens)
    }

    fn tokenize_line(&self, line: Arc<str>, line_number: i32) -> Vec<Token> {
        let mut tokens = Vec::new();
        let mut start = 0;

        while start < line.len() {
            if let Some((length, token_type)) = self.find_next_token(&line[start..]) {
                tokens.push(Token::new(
                    line.clone(),
                    self.file_name.clone(),
                    line_number,
                    start as u16,
                    line[start..start + length].trim().to_owned(),
                    token_type,
                ));
                start += length;
            } else {
                start += 1; // Skip to next character
            }
        }

        return tokens;
    }

    fn find_next_token(&self, s: &str) -> Option<(usize, TokenType)> {
        let regexps = [
            (&self.string_re, TokenType::STRING),
            (&self.character_re, TokenType::CHARACTER),
            (&self.numeric_re, TokenType::NUMERIC),
            (&self.identifier_re, TokenType::IDENTIFIER),
            (&self.delimiter_re, TokenType::DELIMITER),
            (&self.operator_re, TokenType::OPERATOR),
            (&self.comment_re, TokenType::COMMENT),
        ];

        for (regex, token_type) in regexps {
            if let Some(matched) = regex.find(s) {
                return Some((matched.end(), token_type));
            }
        }

        None
    }
}
