<div align="center">
  <img src="../assets/helix-logo.svg" alt="Helix Programming Language Logo" width="100%">
</div>

| [Website](https://www.helix-lang.com) | [Introduction](#helix-programming-language) | [Why Helix?](#why-helix) | [Features](#features) | [Syntax Examples](#helix-syntax-examples) | [Quick Start](#quick-start) | [Goals](#goals) | [Community and Contributing](#community-and-contributing) | [License](#license) | [Acknowledgements](#acknowledgements) | [Links](#links) |

# Helix Programming Language

Helix is an experimental programming language designed for high-performance, safety, and seamless interoperability with Python, C, C++, and Rust. It provides developers with a clean syntax, a robust feature set, and a focus on efficient code writing and maintenance. Helix aims to simplify the development process while maximizing performance, making it ideal for systems programming and application development.

---

<div>
  <img src="../assets/showcase.png" width="450" align="right" alt="Code Example">
</div>

## Why Helix?

Helix is designed to address several limitations found in other modern languages like Rust and Zig:

- **Performance:** Helix is optimized for speed and efficiency, making it ideal for performance-critical applications.
- **Interoperability:** Seamless integration with Python, C++, Rust, and more allows developers to leverage existing codebases without sacrificing performance.
- **Developer Productivity:** Advanced tooling, such as a robust standard library, package manager, and build system, streamlines the development process.
- **Safety:** Helix includes a strong type system and error handling mechanisms to catch bugs at both compile-time and runtime, ensuring safer code.

## Key Features

- **Concurrency Support:** Helix offers easy-to-use `async` and `await` for writing concurrent programs.
- **Pattern Matching:** A powerful pattern-matching system simplifies complex conditional logic.
- **Macros and Processors:** Extensible macros and processors for code generation and optimization.
- **Object-Oriented Programming (OOP):** Full OOP support with classes, inheritance, and polymorphism.
- **Rich Error Reporting:** Detailed error messages to guide developers through debugging and optimization.
- **Cross-Platform Interoperability:** Native support for Python, C, C++, and Rust out of the box.

## Syntax Examples

### Error Reporting
Helix provides detailed and informative error messages to help with debugging:

<div align="left"><img src="../assets/error-example.png" alt="error reporting" width="400">
  <a href="#">
  <img src="../assets/bumper.png">
</a></div>

### Strong Typing with Flexible Generics
Helix allows for flexible typing with robust generic systems:

<div align="left"><img src="../assets/ffi-example.png" alt="functions and classes example" width="450">
  <a href="#">
  <img src="../assets/bumper.png">
</a></div>


### Asynchronous Programming
Helix supports asynchronous code with `async` and `await`:

<div align="left"><img src="../assets/async-example.png" alt="async programming example" width="500">
  <a href="#">
  <img src="../assets/bumper.png">
</a></div>

---

## Why Not Rust or Zig?

While both Rust and Zig are excellent languages, they come with certain trade-offs that Helix seeks to address:
- **Lack of OOP Support:** Both Rust and Zig lack comprehensive OOP support, which is essential for certain domains like AI or game development.
- **Strict Safety Mechanisms (Rust):** While Rust's borrow checker is a powerful tool, it can sometimes be too strict, leading to complex refactoring for developers.
- **Limited Features (Zig):** Zig, while performant, lacks certain features like a macro processor that Helix provides.

### Advantages of Helix

Helix draws inspiration from Rust, Python, and C++, combining the strengths of these languages while addressing their weaknesses:
- **Balanced Safety:** Helix features a borrow checker, but with a less strict enforcement, offering flexibility without sacrificing safety.
- **Simpler Syntax:** Helix provides a modern, Python-like syntax, reducing verbosity while maintaining power.
- **OOP Support:** Helix fully supports object-oriented programming, making it suitable for a wide range of applications.

---

### Quick Start

#### Installation & Build

> [!WARNING]
> Helix is currently under development and does not yet have a useable compiler. The following instructions are for development and building the compiler itself.

> [!TIP]
> Linux is not *yet* tested, Most development is done on MacOS or Windows, if any issues arise with building on Linux, please open an issue.

### Prerequisites

- **Xmake**: [Install Xmake](https://xmake.io/#/)
- **Python**: [Install Python](https://www.python.org/downloads/)
- **Git**: [Install Git](https://git-scm.com/downloads)
- **C++ Compiler**: Ensure you have a C++ compiler (e.g., **Clang**, **MSVC**, or **GCC**).

##### Windows Specific (Visual Studio Build Tools)

> [!CAUTION]
> Only **msvc** is supported and tested on Windows, **gcc** is not supported on Windows. and **mingw** is not tested.

1. Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/) and select the following components:
   - **Desktop development with C++** (workload)
   - **MSVC v143** or higher
   - **Windows SDK**
   - **C++ CMake tools for Windows**
   - **C++ Clang Tools for Windows v17.0.x** or higher
   - **C++ ATL for v143 build tools** or higher
  
2. Install [Python](https://www.python.org/downloads/)

3. Install [xmake](https://xmake.io/#/) (PowerShell Only)
```powershell
$ Invoke-Expression (Invoke-Webrequest 'https://xmake.io/psget.text' -UseBasicParsing).Content
```

##### MacOS, Unix or Linux Specific (clang or gcc)

> [!WARNING]
> **Perl** is required for building on Linux, if you don't have it installed, install using your package manager.

1. Install [Python](https://www.python.org/downloads/)
   
2. Install Xmake (bash or zsh):
```sh
curl -fsSL https://xmake.io/shget.text | bash
```

3. Install necessary build tools such as Clang or GCC. (should be installed by default on MacOS)

##### All Platforms (After following platform specific steps)

1. Make a directory for the project and clone the repo
```sh
$ git clone https://github.com/kneorain/helix-lang.git
$ cd helix-lang
```

2. Build Helix along with the LLVM backend, Clang, Tests, and the Helix Compiler Toolchain API (~30 minutes on a 8-core CPU)
```sh
$ xmake build
```

3. Run the tests or the compiler
```sh
$ xmake run tests
$ xmake run helix -h
```

--------------------------------------------------------------------------------

### Hello, World!

Here's how you can write and run a simple "Hello, World!" program in Helix:

```rust
// hello_world.hlx
print("Hello, World!");
```

To compile then run the source:

```bash
path/to/helix hello_world.hlx
./hello_world
```

---

## Goals

Helix is built with the following goals in mind:

- **Interoperability:** Seamless interop with Python, C, C++, and Rust.
- **Performance:** High-performance code generation with optimizations for speed.
- **Simplicity:** Modern syntax inspired by Python for ease of use.
- **Comprehensive Feature Set:** Robust support for error handling, concurrency, and more.
- **Community-Driven Development:** Helix is open-source and encourages contributions from the community.

---

## Community and Contributing

Helix is an open-source project, and we welcome contributions! Whether it's fixing bugs, improving documentation, or adding new features, your contributions are valuable.

- [Submit Issues](https://github.com/kneorain/helix-lang/issues)
- [Submit Pull Requests](https://github.com/kneorain/helix-lang/pulls)

Read our [Contributing Guide](CONTRIBUTING.md) for more details.

---

## License

Helix is licensed under the Attribution 4.0 International License. See the [LICENSE](https://github.com/kneorain/helix-lang/blob/main/license) for more details.

---

## Acknowledgements

We want to thank all contributors for their efforts in making Helix a reality. Your work is appreciated!

<div align="center">
  <a href="https://github.com/kneorain/helix-lang/graphs/contributors">
    <img src="https://contrib.rocks/image?repo=kneorain/helix-lang">
  </a>
</div>

---

Happy coding with Helix! 🚀

---

## Links

- [Official Website](https://helix-lang.com)
- [Documentation](https://helix-lang.com/docs)
- [Tutorials](https://helix-lang.com/tutorials)
