use super::unknown_int::NumericType;
use std::collections::HashMap;

pub struct PanicParams<'a> {
    pub file: Option<&'a str>,
    pub line_no: Option<NumericType>,
    pub no_lines: Option<bool>,
    pub multi_frame: Option<bool>,
    pub pos: Option<i8>,
    pub replacements: Option<HashMap<&'a str, &'a str>>,
    pub follow_marked_order: Option<bool>,
    pub mark_start: Option<u32>,
    pub thread_name: Option<&'a str>,
    pub no_exit: Option<bool>,
    pub lang: Option<&'a str>,
    pub _code: Option<&'a str>,
}

impl Default for PanicParams<'_> {
    fn default() -> Self {
        PanicParams {
            file: None,
            line_no: None,
            no_lines: None,
            multi_frame: None,
            pos: None,
            replacements: None,
            follow_marked_order: None,
            mark_start: None,
            thread_name: None,
            no_exit: None,
            lang: None,
            _code: None,
        }
    }
}