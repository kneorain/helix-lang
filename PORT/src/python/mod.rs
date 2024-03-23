use std::fmt::Display;

use pyo3::{
    types::{PyDict, PyList, PyModule}, Python,
};

pub mod shared;
mod private;

pub use crate::python::shared::unknown_int::NumericType;
pub use private::python_import;
use private::python_import::repr_python;
use std::env;
pub use crate::__panic__;

// --------------------------- BEGIN PYTHON IMPORTS ----------------------------
pub mod test {
    use super::*;

    repr_python!("test21", fn hello_from_python());
    repr_python!("test21", fn test_args(a: i32, b: i32) -> i32);
    repr_python!("test21", fn test_kwargs(a: i32, b: i32; c: Option<i32> = None) -> i32);
}

// ---------------------------- END PYTHON IMPORTS -----------------------------

pub fn init_python() {
    pyo3::prepare_freethreaded_python();
    // the python import path from the virtualenv

    Python::with_gil(|py| {
        let sys = PyModule::import(py, "sys")
                .expect("Failed to import sys");
        
        let sys_path = sys.getattr("path")
                .expect("Failed to get sys.path")
                .downcast::<PyList>()
                    .expect("sys.path is not a PyList");

        let mut port_path = env::current_dir().expect("Failed to get current directory");
        if port_path.ends_with("PORT") {
            port_path.push("src\\python\\src");
        } else if port_path.ends_with("helix-lang") {
            port_path.push("PORT\\src\\python\\src");
        } else {
            panic!("Failed to find the PORT directory");
        }
        
        sys_path.insert(0, port_path)
            .expect("Failed to insert src/python to sys.path");
        
        sys_path.insert(0, "Z:/devolopment/helix/helix-lang/.venv/Lib/site-packages")
            .expect("Failed to insert .venv/Lib/site-packages to sys.path");

        sys_path.insert(0, "Z:/devolopment/helix/helix-lang/.venv/Lib")
            .expect("Failed to insert .venv/Lib to sys.path");

        sys_path.insert(0, "Z:/devolopment/helix/helix-lang/.venv/Scripts")
            .expect("Failed to insert .venv/Scripts to sys.path");
        // list the file at port_path
        py.run("import os; print(os.getcwd())", None, None).unwrap();
    });
}
 
#[macro_export]
macro_rules! __panic__ {
    ($error:expr, $mark:expr $(, line_no = $line_no:expr)?) => {
        {
            let mut params = $crate::python::shared::default_params::PanicParams::default();
            $(params.line_no = Some($crate::NumericType::Int($line_no));)*
            $crate::python::__panic__impl($error, $mark, params)
        }
    };
    ($error:expr, $mark:expr $(, $field:ident = $value:expr)*) => {
        {
            let mut params = $crate::python::shared::default_params::PanicParams::default();
            $(params.$field = Some($value);)*
            $crate::python::__panic__impl($error, $mark, params)
        }
    };
}

#[allow(non_snake_case)]
pub fn __panic__impl<T: Display>(__error: T, _mark: Option<Vec<&str>>, params: shared::default_params::PanicParams) {
    Python::with_gil(|py| {
        // print the __file__
        let module = PyModule::import(py, "panic").expect("Failed to import PANIC");
        
        let kwargs = PyDict::new(py);
        kwargs.set_item("file", params.file.unwrap_or_else(|| "")).expect("broke.");
        kwargs.set_item("line_no", params.line_no.unwrap_or_default()).expect("broke.");
        kwargs.set_item("no_lines", params.no_lines.unwrap_or_default()).expect("broke.");
        kwargs.set_item("multi_frame", params.multi_frame.unwrap_or_default()).expect("broke.");
        
        kwargs.set_item("pos", params.pos.unwrap_or_default()).expect("broke.");
        
        if let Some(ref repl) = params.replacements {
            kwargs.set_item("replacements", repl).expect("broke.");
        }
        kwargs.set_item(
            "follow_marked_order",
            params.follow_marked_order.unwrap_or_default(),
        ).expect("broke.");
        if let Some(ref mark) = params.mark_start {
            kwargs.set_item("mark_start", mark).expect("broke.");
        }
        if let Some(ref name) = params.thread_name {
            kwargs.set_item("thread_name", name).expect("broke.");
        }
        kwargs.set_item("no_exit", params.no_exit.unwrap_or_default()).expect("broke.");
        kwargs.set_item("lang", params.lang.unwrap_or_else(|| "")).expect("broke.");
        if let Some(ref code) = params._code {
            kwargs.set_item("_code", code).expect("broke.");
        }

        // Convert __error to a Python object
        let py_error = pyo3::types::PyString::new(py, &format!("{}", __error));

        // Call the Python function with arguments and keyword arguments
        match module.call_method("__panic__", (py_error, _mark), Some(kwargs)) {
            Ok(_) => {}
            Err(e) => {
                e.print_and_set_sys_last_vars(py);
            }
        };
    });

    return;
}

