use pyo3::{
    Python, ToPyObject, PyObject,
};

pub enum NumericType {
    Int(i32),
    Uint(u32),
}

impl ToPyObject for NumericType {
    fn to_object(&self, py: Python) -> PyObject {
        match self {
            NumericType::Int(i) => i.to_object(py),
            NumericType::Uint(u) => (*u as i64).to_object(py),  // u32 can be safely cast to i64
        }
    }
}

impl Default for NumericType {
    fn default() -> Self {
        NumericType::Int(0)
    }
}

#[allow(dead_code)]
trait IntoNumericType {
    fn into_numeric_type(self) -> NumericType;
}

impl IntoNumericType for i32 {
    fn into_numeric_type(self) -> NumericType {
        NumericType::Int(self)
    }
}

impl IntoNumericType for u32 {
    fn into_numeric_type(self) -> NumericType {
        NumericType::Uint(self)
    }
}

impl NumericType {
    #[allow(dead_code)]
    fn new<T: IntoNumericType>(value: T) -> Self {
        value.into_numeric_type()
    }
}