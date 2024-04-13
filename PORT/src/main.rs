#[allow(unused_imports)]
#[feature(ptr_metadata)]
#[feature(portable_simd)]
use pyo3::{ types::PyModule, PyResult, Python };
#[cfg(test)]
pub mod tests;

pub mod python;
pub mod rust;
pub mod cpp;


extern crate tokio;
extern crate pretty_env_logger;
#[macro_use]
extern crate log;

use std::{ io, panic, thread };
use std::time;

pub struct PrimedInstant {
    pub instant: std::time::Instant,
    pub average_overhead: u128,
    pub elapsed: u128,
}

impl PrimedInstant {
    const PRIME_ITERATIONS: u128 = 1000000;

    #[inline(always)]
    pub fn new() -> Self {
        
        ;
        Self {
            instant: std::time::Instant::now(),
            average_overhead: 0,
            elapsed: 0,
        }
    }

    #[inline(always)]
    // Primes the instruction cache with the instructions related to instant,
    // and returns the average time it takes to execute a timing operation to get an accurate delta
    pub fn prime(&mut self) {
        println!("Priming the instruction cache with the instructions related to instant...");
        self.average_overhead = (0..Self::PRIME_ITERATIONS).fold(0, |acc, _| {
            let start = std::time::Instant::now();
            ;
            let elapsed = start.elapsed();

            return acc + elapsed.as_nanos();
        }) / Self::PRIME_ITERATIONS;
    }
    
    #[inline(always)]
    pub fn start(&mut self) {
        self.instant = std::time::Instant::now();
    }

    #[inline(always)]
    pub fn end(&mut self) {
        self.elapsed = self.instant.elapsed().as_nanos() - self.average_overhead
    }

    pub fn log(&self,message: &str) {
        info!("{}: {:?}", message, self.elapsed);
    }
    
    pub fn log_elapsed(&self) {
        info!("Time Elapsed: {:?}",self.elapsed);
    }

    pub fn log_overhead(&self) {
        info!("Average `Instant` overhead time: {:?}",self.average_overhead);
    }

    #[inline(always)]
    pub fn get_elapsed_ns(&self)->u128{
        self.elapsed
    }
}





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
    let mut instant = PrimedInstant::new();

    pretty_env_logger::init(); // TO SEE LOGS run `set RUST_LOG=debug` in terminal
    rust::init_rust();
    python::init_python();
    println!("\n---------- PYTHON ----------");
    python::test::test_kwargs(1, 2, None);
    println!("{:?}", python::test::test_args(1, 2));
    
    // print the cwd
    println!("\n---------- RUST ----------");
    let cwd = std::env::current_dir().unwrap();
    println!("Current working directory: {}", cwd.display());

    println!("\n---------- C++ ----------");
    
    let inst = cpp::File::open(
        "PORT/src/test.hlx",
        "r",
        "utf-8"
    );

    //println!("{}", _reader);
    //let lexar = rust::token::lexer::Lexer::new("PORT/src/test.hlx");
    //let tokens = lexar.tokenize();
    //println!("{:?}", tokens);
    Ok(())
}

#[cfg(test)]
/// Gets the average time for instant to get a delta,
/// This also happens to prime the instruction cache with the instructions related to instant 
pub fn get_instant_average() -> std::time::Duration {
    
    const ITERATIONS: usize = 100000000;

    (0..ITERATIONS).fold(std::time::Duration::new(0, 0), |acc, _| {
        
        let start = std::time::Instant::now();

        let elapsed = start.elapsed();
        
        acc + elapsed
    }) / ITERATIONS as u32

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
