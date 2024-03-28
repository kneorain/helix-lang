//use regex::Regex;
//use std::collections::HashMap;
//use std::cell::RefCell;
//use lazy_static::lazy_static;
//
//
//thread_local! {
//    static COMPILED_RE: RefCell<Option<Regex>> = RefCell::new(None);
//}
//
//fn compiled_re(ignore_strings: bool) -> Regex {
//    COMPILED_RE.with(|re| {
//        if re.borrow().is_none() || ignore_strings {
//            let back_slash = r"\\";
//            let pattern = format!(r#"
//                (["r#fbur]*"[^"\\]*(?:\\.[^"\\]*)*")                                                                     | # Double quotes strings, including f, b, r, u strings
//                (["r#fbur]*'[^'\\]*(?:\\.[^'\\]*)*')                                                                     | # Single quotes strings, including f, b, r, u strings
//                ({}[^\n]*)                                                                                              | # Single line comments (~~)
//                ({}[\s\S]*?{})                                                                                          | # Multi line comments (~*~ ... ~*~)
//                (\b\d+\.\d+\b)                                                                                          | # Decimal numbers
//                (\b\w+\b)                                                                                               | # Words (identifiers, keywords)
//                ({})                                                                                                    | # Double character operators
//                ([(){{}};])                                                                                             | # Single character delimiters
//                (\S)                                                                                                    | # Catch other characters
//            "#,
//                back_slash.to_owned() + &base::COMMENT.replace(" ", back_slash),
//                back_slash.to_owned() + &base::BLOCK_COMMENT.replace(" ", back_slash),
//                back_slash.to_owned() + &base::BLOCK_COMMENT.replace(" ", back_slash),
//                base::FAT_CHARACTER.join("|"));
//            let regex = Regex::new(&pattern).unwrap();
//            *re.borrow_mut() = Some(regex);
//        }
//        re.borrow().as_ref().unwrap().clone()
//    })
//}
//
//pub fn tokenize_line(code: &Token, path: Option<&str>, ignore_errors: bool, ignore_strings: bool) -> Option<Vec<String>> {
//    let tokens: Vec<Vec<String>> = compiled_re(ignore_strings).captures_iter(&code.token)
//        .map(|caps| {
//            (1..caps.len()).filter_map(|i| caps.get(i).map(|m| m.as_str().to_string())).collect()
//        })
//        .collect();
//
//    let flattened_tokens = tokens.into_iter().flatten()
//        .filter(|token|
//            !token.starts_with(&base::COMMENT) &&
//            !token.starts_with(&base::BLOCK_COMMENT) &&
//            !token.ends_with(&base::BLOCK_COMMENT))
//        .collect::<Vec<String>>();
//
//    if path.is_none() {
//        panic("The path must be specified. Internal error");
//    }
//
//    for token in &flattened_tokens {
//        if base::RESERVED_KEYWORDS.contains(token) && !ignore_errors {
//            panic(&format!("Reserved keyword '{}' used.", token));
//        }
//    }
//
//    let code_line = if !flattened_tokens.is_empty() {
//        flattened_tokens.into_iter().map(|token| {
//            base::EARLY_REPLACEMENTS.get(&token).cloned().unwrap_or(token)
//        }).collect()
//    } else {
//        vec![]
//    };
//
//    Some(code_line)
//}
//
//pub fn standalone_tokenize_line(line: &str) -> Vec<String> {
//    let back_slash = r"\\";
//    let pattern = Regex::new(&format!(r#"
//        ({}[^\n]*)                                                                                                  | # Single line comments (~~)
//        ({}[\s\S]*?{})                                                                                              | # Multi line comments (~*~ ... ~*~)
//        (\b\d+\.\d+\b)                                                                                              | # Decimal numbers
//        (\b\w+\b)                                                                                                   | # Words (identifiers, keywords)
//        ({})                                                                                                        | # Double character operators
//        ([(){{}};])                                                                                                 | # Single character delimiters
//        (\S)                                                                                                        | # Catch other characters
//    "#,
//        back_slash.to_owned() + &base::COMMENT.replace(" ", back_slash),
//        back_slash.to_owned() + &base::BLOCK_COMMENT.replace(" ", back_slash),
//        back_slash.to_owned() + &base::BLOCK_COMMENT.replace(" ", back_slash),
//        base::FAT_CHARACTER.join("|"))).unwrap();
//
//    pattern.captures_iter(line)
//        .map(|caps| {
//            (1..caps.len()).filter_map(|i| caps.get(i).map(|m| m.as_str().to_string())).collect::<Vec<String>>()
//        })
//        .flatten()
//        .filter(|token|
//            !token.starts_with(&base::COMMENT) &&
//            !token.starts_with(&base::BLOCK_COMMENT) &&
//            !token.ends_with(&base::BLOCK_COMMENT))
//        .collect()
//}