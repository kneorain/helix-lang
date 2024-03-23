#[macro_export]
macro_rules! repr_python {
    // Match when there are no arguments for the Python function.
    ($module_name:ident, $func_name:ident) => {
        pub fn $func_name() {
            Python::with_gil(|py| {
                let module = PyModule::import(py, stringify!($module_name))
                    .expect("Failed to import Python module");

                match module.call_method0(stringify!($func_name)) {
                    Ok(_) => (),
                    Err(e) => panic!("Failed to call Python function: {}", e),
                }
            })
        }
    };
    
    // Match when there are arguments for the Python function.
    ($module_name:ident,, $func_name:ident, $($arg_name:ident : $arg_type:ty),*) => {
        pub fn $func_name($($arg_name: $arg_type),*) -> PyResult<()> {
            Python::with_gil(|py| {
                let module = PyModule::import(py, stringify!($module_name))
                    .expect("Failed to import Python module");

                module.call_method1(stringify!($func_name), ($($arg_name,)*))?;
                Ok(())
            })
        }
    };
}

pub use crate::repr_python;
//
//[macro_export]
//acro_rules! repr_rs_python {
//   // repr_rs_python!("module_name")
//
//