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
pub mod File {
    unsafe extern "C++" {
        include!("helix-compiler/src/cpp/include/file_reader.hpp");

        type FileIO;

        fn init();

        fn open(filename: &str, mode: &str, encoding: &str) -> SharedPtr<FileIO>;

        fn readLine(&self) -> &[u8];
        fn readLines(&self) -> &[u8];
        fn read(&self) -> &[u8];

        fn write(&self, data: &[u8]);
        fn writeLine(&self, data: &[u8]);
        fn writeLines(&self, lines: &[&[u8]]);

        fn append(&self, data: &[u8]);
        fn appendLine(&self, data: &[u8]);
        fn appendLines(&self, lines: &[&[u8]]);

        fn close(&self);
    }
}

pub fn new_async_file_stream(filename: &str) -> Arc<Mutex<UniquePtr<T_FileReader>>> {
    return Arc::new(Mutex::new(FileReader::init(filename)));
}
