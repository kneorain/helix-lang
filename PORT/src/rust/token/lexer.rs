use super::{Token, TokenType};
use regex::Regex;
use std::sync::Arc;
use std::{fs::File, io::self};
use std::sync::Mutex;
use std::thread;
use std::sync::mpsc;
use std::io::BufRead;


pub struct Lexer {
    file_name: Arc<str>,
}



lazy_static::lazy_static! {
    static ref STRING_RE: Regex = Regex::new(r#"([fbur]*"[^"\\]*(?:\\.[^"\\]*)*")"#).unwrap();
    static ref CHARACTER_RE: Regex = Regex::new(r#"([fbur]*'[^'\\]*(?:\\.[^'\\]*)*')"#).unwrap();
    static ref NUMERIC_RE: Regex = Regex::new(r#"(\b\d+\.\d+\b|\b\d+[fdui]?\b)"#).unwrap();
    static ref IDENTIFIER_RE: Regex = Regex::new(r#"(\b[a-zA-Z][a-zA-Z0-9_]*\b)"#).unwrap();
    static ref DELIMITER_RE: Regex = Regex::new(r#"([\(\)\{\}\[\];,])"#).unwrap();
    static ref OPERATOR_RE: Regex = Regex::new(r#"([+\-*/%=&|!<>^])"#).unwrap();
    static ref COMMENT_RE: Regex = Regex::new(r#"((?://[^\n]*)|(/\*[\s\S]*?\*/))"#).unwrap();
}

// make an unsafe but VERY fast io reader for the lexer

impl Lexer {
    pub fn new(file_name: &str) -> Self {
        Self {
            file_name: Arc::from(file_name.to_owned()),
        }
    }

    pub fn tokenize(&self) -> Vec<Token> {
        let file = File::open(&*self.file_name).unwrap();
        let reader = io::BufReader::new(file);
        let tokens = Arc::new(Mutex::new(Vec::new()));
        let mut line_number = 1;
    
        let (sender, receiver) = mpsc::channel();
    
        // Spawn multiple threads to process lines concurrently
        let num_threads = 4;
        let receiver = Arc::new(Mutex::new(receiver));

        for _ in 0..num_threads {
            let tokens = Arc::clone(&tokens);
            let file_name = Arc::clone(&self.file_name);
            let receiver = Arc::clone(&receiver);

            let handle = thread::spawn(move || {
                while let Ok(line) = receiver.lock().unwrap().recv() {
                    let line_tokens = Lexer::tokenize_line(file_name.clone(), Arc::from(line), line_number);
                    line_number += 1;

                    tokens.lock().unwrap().extend(line_tokens);
                }
            });

            handle.join().unwrap();
        }

        // Read the file line by line and send each line to the threads
        for line in reader.lines() {
            sender.send(line.unwrap()).unwrap();
        }

        // Drop the sender to close the channel
        drop(sender);

        // Wait for all threads to finish
        for _ in 0..num_threads {
            receiver.lock().unwrap().recv().unwrap();
        }

        // Extract the tokens from the Arc<Mutex<Vec<Token>>>
        Arc::try_unwrap(tokens).unwrap().into_inner().unwrap()
    }

    fn tokenize_line(file_name: Arc<str>, line: Arc<str>, line_number: i32) -> Vec<Token> {
        let mut tokens = Vec::new();
        let mut start = 0;

        while start < line.len() {
            if let Some((length, token_type)) = Lexer::find_next_token(&line[start..]) {
                tokens.push(Token::new(
                    line.clone(),
                    file_name.clone(),
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

    fn find_next_token(s: &str) -> Option<(usize, TokenType)> {
        if let Some(captures) = STRING_RE.captures(s) {
            return Some((captures.get(0).unwrap().as_str().len(), TokenType::STRING));
        }

        if let Some(captures) = CHARACTER_RE.captures(s) {
            return Some((captures.get(0).unwrap().as_str().len(), TokenType::CHARACTER));
        }

        if let Some(captures) = NUMERIC_RE.captures(s) {
            return Some((captures.get(0).unwrap().as_str().len(), TokenType::NUMERIC));
        }

        if let Some(captures) = IDENTIFIER_RE.captures(s) {
            return Some((captures.get(0).unwrap().as_str().len(), TokenType::IDENTIFIER));
        }

        if let Some(captures) = DELIMITER_RE.captures(s) {
            return Some((captures.get(0).unwrap().as_str().len(), TokenType::DELIMITER));
        }

        if let Some(captures) = OPERATOR_RE.captures(s) {
            return Some((captures.get(0).unwrap().as_str().len(), TokenType::OPERATOR));
        }

        if let Some(captures) = COMMENT_RE.captures(s) {
            return Some((captures.get(0).unwrap().as_str().len(), TokenType::COMMENT));
        }

        return None;
    }
}
