#[macro_export]
macro_rules! __panic__ {
    ($error:expr, $mark:expr $(, line_no = $line_no:expr)?) => {
        {
            let mut params = $crate::python::shared::default_params::PanicParams::default();
            $(params.line_no = Some($crate::NumericType::Int($line_no));)*
            $crate::python::__panic__impl($error, $mark, params);
        }
    };
    ($error:expr, $mark:expr $(, $field:ident = $value:expr)*) => {
        {
            let mut params = $crate::python::shared::default_params::PanicParams::default();
            $(params.$field = Some($value);)*
            $crate::python::__panic__impl($error, $mark, params);
        }
    };
}
