## this file defines all the langauge features of helix that make the language very powerful and easy to use.


# Language Features

### Generics
Generics in helix are handled in a way that is completly unique to the language.

```helix
fn add(a: T, b: T) -> T
  requires <T> if T has Add {
    return a + b;
}

fn call_a_string_method(a: T) -> T
  requires <T> if T derives string {
    return a.to_uppercase();
}

fn call_a_method(a: T) -> string {
    try:
        return string(a);
    catch:
        return "Error";
}
```

Things to note here:
1. The `requires` keyword is used to specify the constraints on the generic type.
2. The `if` keyword is used to specify the condition that the generic type must satisfy. (optional)
3. The `derives` keyword is a strict constraint that the generic type must satisfy, it is used to specify that the generic type MUST derive from a specific type.
4. The `has` keyword is used to specify that the generic type must implement the specified type's methods (not necessarily derive from the type).


### Pattern Matching
Pattern matching in helix is very powerful and can be used in a variety of ways.

```helix
fn match_example(a: AST_Node) -> int? {
    match a {
        AST_Node(
            type: "int",
            value: _,
            children: _
        ) -> 1;

        AST_Node(
            type: "float",
            value: _,
            children: _
        ) -> 2;

        AST_Node(
            type: "string",
            value: _,
            children: _
        ) -> 3;

        _ -> null;
    }
}
```

Things to note here:
1. The `match` keyword is used to start a pattern matching block.
2. The `->` operator is used to specify the return value of the function if the pattern matches.
3. The `_` operator is used to specify that the value is not important and can be anything.
4. The `null` keyword is used to specify that the pattern did not match any of the cases.
5. The `AST_Node` is a custom type that is defined in the codebase.
6. The `type`, `value`, and `children` are fields of the `AST_Node` type.
7. The `int?` return type specifies that the function can return an integer or null.

