# Guidelines
These are guidelines for using these three languages together and using them in general.

* Any file except `main.rs` can have only a single entry.
* Type structures are defined in files separate from where they are used.
* Pass by reference, pointer/memory address, or an owned-value, except in the following cases:
  * If the size of the data is less than `4 bytes`, the data can be passed by value without a comment attached.
  * If the size of the data is less than or equal to `32 bytes`, the data can be passed by value with a comment attached.
* Interfacal inheritance should be prioritized over classical inheriatance.
* do not interact with the `lib` directory outside of the `mod.rs` file in either the parent directory or in the `lib` dir.

## Language Specifics

### C++
* Follow the template below for the file:
    ```cpp
    #include <rs>

    ... rs_entry(...) {
        ...
    }
    ```

### Python
* Pass by value for primitive types under `32 bytes`.
* Define interfaces to avoid circular imports.

### Rust
* When writing code that incorporates the use of `unsafe`, stipulate the safety of the code in a comment.
* Do not just clone a value to statisfy the borrow checker.