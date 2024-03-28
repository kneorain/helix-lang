#[allow(unused_imports)]
use pyo3::{ types::PyModule, PyResult, Python };

pub mod python;
pub mod rust;
pub mod cpp;

extern crate pretty_env_logger;
#[macro_use]
extern crate log;

use std::path::Path;
use std::{ panic, thread };
use std::time;

fn test_threads() {
    let _handler = thread::Builder
        ::new()
        .name("Fish".into())
        .spawn(|| {
            panic!("Fish died...");
        });
    let _handler = thread::Builder
        ::new()
        .name("Fish1".into())
        .spawn(|| {
            panic!("Fish died...");
        });
    let _handler = thread::Builder
        ::new()
        .name("Fish2".into())
        .spawn(|| {
            panic!("Fish died...");
        });
    let _handler = thread::Builder
        ::new()
        .name("Fish3".into())
        .spawn(|| {
            panic!("Fish died...");
        });
    let _handler = thread::Builder
        ::new()
        .name("Fish4".into())
        .spawn(|| {
            panic!("Fish died...");
        });

    std::thread::sleep(time::Duration::from_millis(200));
}

fn main() {
    pretty_env_logger::init(); // TO SEE LOGS run `set RUST_LOG=debug` in terminal
    rust::init_rust();
    python::init_python();
    
    python::test::test_kwargs(1, 2, None);
    println!("{:?}", python::test::test_args(1, 2));
    
    cpp::c("hello from Rust");
    println!("Result: {}", cpp::add_sum(2, 62)); // 2^62 is the max value for i64
    
    // print the cwd
    let cwd = std::env::current_dir().unwrap();
    println!("Current working directory: {}", cwd.display());
    
    
    let start = time::Instant::now();
    let lexar = rust::token::lexer::Lexer::new("PORT/src/test.hlx");
    let tokens = lexar.tokenize();
    let elapsed = start.elapsed();
    println!("{:?}", tokens);
    println!("Elapsed: {:?}", elapsed);
    

}

#[allow(dead_code)]
#[derive(Debug)]
enum HelixError {
    PythonError(String),
}

impl std::error::Error for HelixError {}
impl std::fmt::Display for HelixError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            HelixError::PythonError(s) => { write!(f, "A python function {s}") }
        }
    }
}
