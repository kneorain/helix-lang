extern crate libc;
use libc::chdir;
use std::ffi::CString;


fn main() {
    println!("hello");
    unsafe {let dir = CString::new("/tmp") as *const i8;}
    if unsafe { chdir(dir) } == -1 {
        // handle failure
    }
}
