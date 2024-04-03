#[allow(unused_imports)]
use pyo3::{ types::PyModule, PyResult, Python };

pub mod python;
pub mod rust;
pub mod cpp;


extern crate tokio;
extern crate pretty_env_logger;
#[macro_use]
extern crate log;

use std::{ io, panic, thread };
use std::time;

#[allow(dead_code)]
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

fn main() -> io::Result<()> {
    pretty_env_logger::init(); // TO SEE LOGS run `set RUST_LOG=debug` in terminal
    rust::init_rust();
    python::init_python();
    
    println!("\n---------- PYTHON ----------");
    python::test::test_kwargs(1, 2, None);
    println!("{:?}", python::test::test_args(1, 2));
    
    println!("\n---------- C++ ----------");
    cpp::test::c("hello from Rust");
    
    println!("Result: {}", cpp::test::add_sum(2, 62)); // 2^62 is the max value for i64
    
    // print the cwd
    println!("\n---------- RUST ----------");
    let cwd = std::env::current_dir().unwrap();
    println!("Current working directory: {}", cwd.display());
    
    //let inst = cpp::file_stream::new_file_stream("PORT/src/test.hlx");
    
    
    
    //let _reader = inst.get_data_from_chunk(1);
    
    //let inst = cpp::file_stream::new_file_stream("PORT/src/test.hlx");
    //let _reader = inst.get_data_from_chunk(0);
    
    // let start = time::Instant::now();
    
    // let input = File::open("PORT/src/copy.hlx")?;
    // let buffered = std::io::BufReader::new(input);
    // let line_count = buffered.lines().count();
    
    // let elapsed = start.elapsed();
    
    // println!("Rust IO Elapsed: {:?}", elapsed);
    // println!("total lines {}", line_count);
    
    // FIXME: C++ IS UNDER COUNTING LINES
    
    println!("\n---------- C++ ----------");
    let start = time::Instant::now();
    
    let inst = cpp::file_stream::new_file_stream("PORT/src/copy.hlx");
    let line_count = inst.get_data_from_chunk(0);
    
    let elapsed = start.elapsed();
    println!("C++ IO Elapsed: {:?}", elapsed);
    println!("{}", line_count);

    thread::sleep(time::Duration::from_millis(200));

    //println!("{}", _reader);
    //let lexar = rust::token::lexer::Lexer::new("PORT/src/test.hlx");
    //let tokens = lexar.tokenize();
    //println!("{:?}", tokens);
    Ok(())
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
