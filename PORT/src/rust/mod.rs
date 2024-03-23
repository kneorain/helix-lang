//pub mod tokenize_line;
//pub mod type_alias;


                //    pub mod token;

//todo make proc macro
pub trait Label {

    fn label()-> &'static str;
}



pub fn panic_c(greeting: &str) {
    panic!("no {}", greeting);
}