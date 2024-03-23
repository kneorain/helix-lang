pub use cpp::*;

mod private;

#[cxx::bridge]
mod cpp {
    unsafe extern "C++" { // EXPOSED TO RUST
        include!("helix-compiler/src/cpp/include/greeting.h");
        fn c(greeting: &str);
    }

    extern "Rust" { // EXPOSED TO C++
        fn panic_c(greeting: &str);
        
        fn hello_from_python();
    }
}



use crate::rust::panic_c;
use crate::python::test::hello_from_python;