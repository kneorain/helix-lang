mod private;
pub mod shared;

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
pub mod file_reader {
    unsafe extern "C++" {
        // EXPOSED TO RUST
        include!("helix-compiler/src/cpp/include/file_reader.hpp");
        type FileReader; //where Self:Sync;
        fn init(filename: &str) -> UniquePtr<FileReader>;
        fn read_line(&self, lineIndex: u32) -> &str;
        fn read_lines(&self, start: u32, offset: u32) -> &str;
        fn read_file(&self) -> &str;
        fn get_total_lines(&self) -> u32;
    }
}

// TODO: Make a macro that does this called cpp class

// macro_rules! cpp_class {
//     ($name:ident) => {
//     };
// }

pub struct FileReader {
    ptr: UniquePtr<file_reader::FileReader>,
}

impl FileReader {
    #[inline(always)]
    pub fn init(filename: &str) -> Self {
        FileReader {
            ptr: file_reader::init(filename),
        }
    }

    #[inline(always)]
    pub fn read_line(&self, line_index: u32) -> &str {
        self.ptr.read_line(line_index)
    }

    #[inline(always)]
    pub fn read_lines(&self, start: u32, offset: u32) -> &str {
        self.ptr.read_lines(start, offset)
    }

    #[inline(always)]
    pub fn read_file(&self) -> &str {
        self.ptr.read_file()
    }

    #[inline(always)]
    pub fn get_total_lines(&self) -> u32 {
        self.ptr.get_total_lines()
    }
}

pub fn new_async_file_stream(filename: &str) -> std::sync::Arc<Mutex<FileReader>> {
    return std::sync::Arc::new(std::sync::Mutex::new(FileReader::init(filename)));
}

use std::sync::Mutex;

use cxx::UniquePtr;

use crate::python::test::hello_from_python;
