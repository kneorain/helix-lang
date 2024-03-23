#[macro_export]
macro_rules! repr_python {
     // Case: Function without arguments, without a return type
     ($module:expr, fn $func_name:ident()) => {
        pub fn $func_name() {
            Python::with_gil(|py| {
                let module = PyModule::import(py, $module)
                    .expect("Failed to import Python module");
                module
                    .getattr(stringify!($func_name))
                    .expect("Failed to get Python function")
                    .call0()
                    .expect("Failed to call Python function");
                return;
            })
        }

        #[macro_export]
        macro_rules! $func_name {
            () => {
                $crate::$func_name()
            }
        }
    };

    // Case: Function without arguments, with a return type
    ($module:expr, fn $func_name:ident() -> $ret_type:ty) => {
        pub fn $func_name() -> $ret_type {
            Python::with_gil(|py| {
                let module = PyModule::import(py, $module)
                    .expect("Failed to import Python module");
                let result: $ret_type = module
                    .getattr(stringify!($func_name))
                    .expect("Failed to get Python function")
                    .call0()
                    .expect("Failed to call Python function")
                    .extract()
                    .expect("Failed to convert Python return value");
                result
            })
        }

        #[macro_export]
        macro_rules! $func_name {
            () => {
                $crate::$func_name()
            }
        }
    };

    // Case: Function with arguments, including optional keyword arguments, and a return type
    ($module:expr, fn $func_name:ident($($arg_name:ident : $arg_type:ty),* $(; $kwarg_name:ident : $kwarg_type:ty = $kwarg_default:expr)*) -> $ret_type:ty) => {
        pub fn $func_name($($arg_name: $arg_type,)* $($kwarg_name: Option<$kwarg_type>,)*) -> $ret_type {
            Python::with_gil(|py| {
                let module = PyModule::import(py, $module)
                    .expect("Failed to import Python module");
                let func = module
                    .getattr(stringify!($func_name))
                    .expect("Failed to get Python function");
                
                let args = ($($arg_name,)*);
                let kwargs = PyDict::new(py);
                $(
                    if let Some(value) = $kwarg_name {
                        kwargs.set_item(stringify!($kwarg_name), value).expect("Failed to set keyword argument");
                    }
                )*

                let _result = func.call(args, Some(kwargs))
                    .expect("Failed to call Python function");

                let result: $ret_type = _result.extract()
                    .expect("Failed to convert Python return value");
                result
            })
        }

        #[macro_export]
        macro_rules! $func_name {
            ($($arg_name:ident : $arg_type:expr),* $(, $kwarg_name = $kwarg_val:expr)*) => {
                {
                    let mut kwargs = std::collections::HashMap::new();
                    $(kwargs.insert(stringify!($kwarg_name), $kwarg_val);)*
                    $crate::$func_name($($arg_name,)* $(kwargs.remove(stringify!($kwarg_name)).unwrap_or(None),)*)
                }
            }
        }
    }
}


pub use crate::repr_python;