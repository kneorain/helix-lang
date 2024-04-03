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
        fn get_total_chunks(&self) -> u32;
        fn get_data_from_chunk(&self, chunkIndex: u32) -> &str;
    }
}


use crate::python::test::hello_from_python;