pub const CONTENT: &'static str =
    r#"fn=== main() {
println!("Hello,
world!");"Hello; \" world!"
if true != false {
let xyz_99_yoMama = 5 | b"some" | 'c'| b's';
}
}"2"#;

pub const EXPECTED: &'static [&'static str] = &[
    "fn",
    "===",
    "main",
    "(",
    ")",
    "{",
    "println",
    "!",
    "(",
    "\"Hello,\nworld!\"",
    ")",
    ";",
    "\"Hello; \\\" world!\"",
    "if",
    "true",
    "!=",
    "false",
    "{",
    "let",
    "xyz_99_yoMama",
    "=",
    "5",
    "|",
    "b\"some\"",
    "|",
    "'c'",
    "|",
    "b\'s\'",
    ";",
    "}",
    "}",
    "\"2",
];
