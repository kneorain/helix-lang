mod private;
pub mod shared;

#[cxx::bridge]
pub mod test {
    unsafe extern "C++" { // EXPOSED TO RUST
        include!("helix-compiler/src/cpp/include/greeting.h");
        fn c(greeting: &str);
        fn add_sum(a: i32, b: i32) -> i64;
    }

    extern "Rust" { // EXPOSED TO C++
        fn hello_from_python();
    }
}

#[cxx::bridge(namespace = "file_stream_cpp")]
pub mod file_stream {
    unsafe extern "C++" { // EXPOSED TO RUST
        include!("helix-compiler/src/cpp/include/file_stream.hpp");
        type FileStream_CPP;
    
        fn new_file_stream(filename: &str) -> UniquePtr<FileStream_CPP>;
        fn read_line(&self, lineIndex: u32) -> &str;
        fn read_lines(&self, start: u32, offset: u32) -> &str;
        fn read_file(&self) -> &str;
        fn get_total_lines(&self) -> u32;
    }
}

pub fn new_async_file_stream(filename: &str) -> std::sync::Arc<Mutex<cxx::UniquePtr<file_stream::FileStream_CPP>>> {
    return std::sync::Arc::new(std::sync::Mutex::new(file_stream::new_file_stream(filename)));
}


use std::sync::Mutex;

use crate::python::test::hello_from_python;