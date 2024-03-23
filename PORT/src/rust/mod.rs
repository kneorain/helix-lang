pub mod token;
pub mod config;

//todo make proc macro
pub trait Label {

    fn label()-> &'static str;
}



pub fn panic_c(greeting: &str) {
    panic!("no {}", greeting);
}