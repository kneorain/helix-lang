mod private;
pub mod shared;

use cxx::UniquePtr;
use std::sync::{Arc, Mutex};
use FileReader::T_FileReader;

use crate::python::test::hello_from_python;

#[cxx::bridge]
pub mod test {
    unsafe extern "C++" {
        // EXPOSED TO RUST
        include!("helix-compiler/src/cpp/include/greeting.h");
        fn c(greeting: &str);
        fn add_sum(a: i32, b: i32) -> i64;
    }

    extern "Rust" {
        // EXPOSED TO C++
        fn hello_from_python();
    }
}

#[cxx::bridge(namespace = "file_reader")]
pub mod FileReader {
    unsafe extern "C++" {
        // EXPOSED TO RUST
        include!("helix-compiler/src/cpp/include/file_reader.hpp");
        type T_FileReader;

        fn init(filename: &str) -> UniquePtr<T_FileReader>;
        fn read_line(&self, lineIndex: u32) -> &str;
        fn read_lines(&self, start: u32, offset: u32) -> &str;
        fn read_file(&self) -> &str;
        fn get_total_lines(&self) -> u32;
    }
}

pub fn new_async_file_stream(filename: &str) -> Arc<Mutex<UniquePtr<T_FileReader>>> {
    return Arc::new(Mutex::new(FileReader::init(filename)));
}
