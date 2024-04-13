mod private;
pub mod shared;

use cxx::UniquePtr;
use std::sync::{Arc, Mutex};
use File::FileIO;

use crate::python::panic_cpp_impl;

#[cxx::bridge]
mod use_headers {
    unsafe extern "C++" {
        include!("helix-compiler/src/cpp/include/better_ints.hpp");
        include!("helix-compiler/src/cpp/include/panic.h");
    }
}


#[cxx::bridge(namespace = "file_io")]
pub mod File {
    unsafe extern "C++" {
        include!("helix-compiler/src/cpp/include/file_io.hpp");

        type FileIO;

        fn open(filename: &str, mode: &str, encoding: &str) -> UniquePtr<FileIO>;
    }

    extern "Rust" {
        fn panic_cpp_impl(
            _error: &str,
            mark: &[&str],
            _file: &str,
            line_no: i32,
            no_lines: bool,
            multi_frame: bool,
            pos: i8,
            follow_marked_order: bool,
            mark_start: u32,
            thread_name: &str,
            no_exit: bool,
            lang: &str,
            _code: &str,
        );
    }
}