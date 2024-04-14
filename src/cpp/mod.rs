//! # Rust module integration with C++ for the Helix compiler project
//!
//! This Rust module serves as a bridge between Rust and C++ within the Helix
//! compiler environment. It defines and implements the integration of Rust
//! functions with C++ code, ensuring interoperability between the two languages
//! for enhanced functionality and performance. The module uses `cxx::bridge` to
//! expose Rust functions to C++ and to bind C++ headers and implementations into
//! Rust.
//!
//! ## Key Components
//! - `private` and `shared` modules: Organizes code visibility and sharing at
//!   the module level. `private` is not accessible outside of this crate, while
//!   `shared` is exposed for broader use.
//! - `cxx::bridge` attribute: Marks the beginning of the namespace and type
//!   bridging section. It includes the unsafe C++ blocks for direct inclusion of
//!   C++ headers such as `better_ints.hpp` and `panic.h` and the definition of
//!   interfacing functions.
//! - `panic_cpp_impl`: A Rust function exposed to C++, used for handling error
//!   scenarios in C++ code that require Rust's intervention.
//! - `FileIO` namespace under `cxx::bridge`: Binds the C++ `FileIO` class and
//!   its methods to Rust, facilitating file operations managed by C++ code but
//!   initiated and controlled from Rust.
//!
//! Usage of this module is crucial for projects requiring tight integration
//! between Rust and C++ components, especially in scenarios where certain
//! functionalities are better handled in one language over the other. This setup
//! is particularly used for performance critical operations in the Helix
//! compiler that benefit from the strengths of both C++ and Rust.
//!
//! SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//!
//! This work is licensed under the Creative Commons Attribution 4.0
//! International License. To view a copy of this license, visit
//! [http://creativecommons.org/licenses/by/4.0/](http://creativecommons.org/licenses/by/4.0/)
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!
//! [See the license here](http://creativecommons.org/licenses/by/4.0/)

mod private;
pub mod shared;


use crate::python::panic_cpp_impl;

#[cxx::bridge]
mod __ {
    //! Anything inside this module either is exposed to C++ or binds headers

    unsafe extern "C++" {
        include!("helix-compiler/src/cpp/include/better_ints.hpp");
        include!("helix-compiler/src/cpp/include/panic.h");
    }

    extern "Rust" {
        /// A Rust function exposed to C++, used for handling error scenarios
        /// in C++ code that require Rust's intervention.
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

#[cxx::bridge(namespace = "file_io")]
pub mod File {
    unsafe extern "C++" {
        include!("helix-compiler/src/cpp/include/file_io.hpp");

        type FileIO;

        fn open(filename: &str, mode: &str, encoding: &str) -> UniquePtr<FileIO>;
    }
}