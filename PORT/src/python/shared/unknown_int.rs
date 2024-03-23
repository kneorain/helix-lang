use pyo3::{
    Python, ToPyObject, PyObject,
};

pub enum IntOrUint {
    Int(i32),
    Uint(u32),
}

impl ToPyObject for IntOrUint {
    fn to_object(&self, py: Python) -> PyObject {
        match self {
            IntOrUint::Int(i) => i.to_object(py),
            IntOrUint::Uint(u) => (*u as i64).to_object(py),  // u32 can be safely cast to i64
        }
    }
}

impl Default for IntOrUint {
    fn default() -> Self {
        IntOrUint::Int(0)
    }
}

