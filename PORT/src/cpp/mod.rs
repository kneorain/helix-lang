pub use cpp::*;

mod private;
pub mod shared;

#[cxx::bridge]
mod cpp {
    unsafe extern "C++" { // EXPOSED TO RUST
        include!("helix-compiler/src/cpp/include/greeting.h");
        fn c(greeting: &str);
        fn add_sum(a: i32, b: i32) -> i64;
    }

    extern "Rust" { // EXPOSED TO C++
        fn hello_from_python();
    }
}

use crate::python::test::hello_from_python;