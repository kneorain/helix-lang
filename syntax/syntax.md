# Keywords

## conditionals

- if
- else
- unless

```rs

// ====-----scoped -----==== //
if a == b {...}
else if a == c {...}
else unless {...}



// ====-----one line -----==== //
if x < y: ...;
else if x > y: ...;
else unless: ...;
else: ...;


// ====-----ternary -----==== //
... if a == b else ...;
... unless a == b else ...;

```

# pre_processor
- define
- macro

```cpp

// ====-----define -----==== //
define PI: 3.14159;

define square_root(a): a as f32 if a is int else sqrt(a);

define add_and_sub(a: Number!, b: Number!) {
    a + b, a - b;
}

// ====-----macro -----==== //
macro any_cast(dest: Type!, src: Identifier! | Literal!) {
    switch (compiler::TARGET) {
        case compiler::Target::CPP {
            unsafe extern "C++" (dest)src;
            break;
        }

        case compiler::Target::C {
            extern "C" (dest)src;
            break;
        }

        default {
            panic MacroRuntimeError("Unsupported target");
        }
    }
}

```

# functions

- fn
- op
- inline
- return

```cpp

// ====-----fn -----==== //
fn add(a: int, b: int) -> int {
    return a + b;
}

fn add(a: int, b: int) -> int: a + b;

// ====-----op -----==== //
class Vector {
    op + as add(a: Vector, b: Vector) -> Vector {
        return Vector(a.x + b.x, a.y + b.y);
    }
}

// ====-----inline -----==== //
inline fn add(a: int, b: int) -> int: a + b;

inline fn add(a: int, b: int) -> int {
    return a + b;
}

```

# async
- async
- spawn
- thread
- await

```cpp

fn some_complex_function(a: int, b: int) -> int {
    std::sleep(1000); // stimulate a long process
    return a + b;
}

// ====-----async -----==== //
async fn some_process(a: int) -> int: some_complex_function(a, 10);

// ====-----spawn -----==== //
let a: std::future::Future = spawn  some_process(5); // green thread

// ====-----thread -----==== //
let b: std::future::Future = thread some_process(5); // red thread

// ====-----await -----==== //
let result = await a; // 15

```

# loops
- break
- continue
- for
- while

```cpp

// ====-----python for -----==== //
for i in range(10) { // under the hood: ..10 RangeTo::new(10)
    print(i);
}

// ====-----c for -----==== //
for let i = 0; i < 10; i++ {
    print(i);
}

// ====-----while -----==== //
let i = 0;
while i < 10 {
    print(i);
    i += 1;
}

// ====-----break -----==== //
while true {
    break;
}
let i = while true {
    break 5;
}

// ====-----continue -----==== //
for i in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] {
    if i == 5 {
        continue;
    }
    print(i);
}

```

# pattern identification
- switch
- match
- case
- default

```cpp

// ====-----switch -----==== //
switch a {
    case 1: print("one"); // no fall through
    case 2 {
        print("two"); // fall through
        break;
    }
    default: print("default");
}

// ====-----match -----==== //
let foo: string | int = match a { // no fall through
    AstNode(
        kind:  default,
        left:  "(",
        right: ")",
    ) -> {
        return "Contains Parenthesis";
    },

    AstNode(
        kind:  AST::Function,
        left:  default,
        right: default,
    ) -> "Is Function",

    AstNode(
        kind:  AST::Fish,
        left:  default,
        right: default,
    ) -> 3,

    "Hello" -> "Is Hello",

    let foo = "World" -> foo,

    let gish if gish.len() > 5 -> "Longer than 5",


    default -> {
        return "Not Binary";
    }
}

```
# data structures
- class
- struct
- enum
- union
- interface  -- *concepts*
- abstract   -- virtual and default methods
- type

```cpp

// ====-----class -----==== //
class Vector2 derives Point {
    let priv x: int;
    let priv y: int;

    fn new(x: int, y: int) {
        self.x = x;
        self.y = y;
    }

    // all dif constructors

    fn add(a: Vector, b: Vector) -> Vector {
        return Vector(a.x + b.x, a.y + b.y);
    }
}

// ====-----struct -----==== //
struct Point {
    let x: int;
    let y: int;

    fn new(x: int, y: int) {
        self.x = x;
        self.y = y;
    }
}

// ====-----enum -----==== //
enum RGBColor {
    Red   = 0xFF0000;
    Green = 0x00FF00;
    Blue  = 0x0000FF;
}

// ====-----union -----==== //
union Number {
    int    some_int;
    float  some_float;
    double some_double;
}

// ====-----interface -----==== //
interface Drawable {
    fn draw();
    fn erase();
}

// ====-----abstract -----==== //
abstract Shape {
    fn erase(); // must be implemented

    fn draw() { // can be overridden
        print("Drawing Shape");
    }
}

// ====-----type -----==== //
type Point  = (int, int);
type String = std::string<list<int>>; // example of a generic type not impl

```

# type handling
- type_of!
- sizeof!
- is

```cpp

// ====-----type_of -----==== //
let a: float = 5;

// a macro has a view of the ast namespace so this is valid, a would have to be defined
type BType = type_of!(a); // stores the type, error out and suggest the type alias keyword to stop chaining

let b: type_of!(a) = 5.0; // 5.0 as int (allowed since theres no chaining)

// ====-----sizeof -----==== //
let size = sizeof!(int); // 16 (size of ptr to heap and ptr to size)

let a: int = 2**32; // as int is a var int
print(a.size()); // 4 bytes

// ====-----is -----==== //
if a is int {
    print("a is an int");
}

```

# error handling
- try
- catch
- finally
- panic

```cpp

// ====-----try -----==== //
try {
    let a = 5 / 0;
} catch e {
    print(e);
}

// ====-----catch -----==== //
try {
    let a = 5 / 0;
} catch e {
    print(e);
}

// ====-----finally -----==== //
try {
    let a = 5 / 0;
} finally {
    print("Finally");
}

// or

try {
    let a = 5 / 0;
} catch e {
    print(e);
} finally {
    print("Finally");
}

// ====-----panic -----==== //
panic RuntimeError("An error occurred");

```

# variable declaration
- let
- priv
- const
- auto

```cpp

// ====-----let -----==== //
let a: int = 5;

// ====-----priv -----==== //
let priv b: int = 5;
priv fn some_function();

// ====-----const -----==== //
const PI: float = 3.14159;

// ====-----auto -----==== //
auto c = 5; // inferred as int and not a specific int (i32, u64, etc)

```

# module import
- import
- using
- from

```cpp

// ====-----import -----==== //
import std::io;
import std::io as io;

// ====-----using -----==== //
/*
breaks down to the following c++ ir:
#RS-LINK[std::mem]

template <typename T>
extern "C" int std::mem::size_of(T t);
*/
using "rust" import std::mem;
extern "C" fn std::mem::size_of<T>(t: T) -> int;
/*
--- if i was to use add in helix code ---
using "python" import tools::calc as py_calc;

fn main() {
    let a: int = 5;
    let b: int = 10;
    let c: int = py_calc.add(a, b);
    print(c);
}

it breaks down to the following c++ ir:
#include <pybind11>

pybind11::py::module py_calc = pybind11::module::import("tools.calc");

int main() {
    int a = 5;
    int b = 10;
    int c = py_calc.attr("add")(a, b).cast<int>();
    print(c);
}



*/
using "python" import add from tools::calc;
using "c++" {
    import parse_json from "rapidjson.h";   // local header
    import "rapidjson.cpp";                 // local source
    import parse_json from <rapidjson.h>;   // global header (system)
    import <string>;                        // global header (system)
}

// ====-----from -----==== //
import {print, println} from std::io;

```

# generators
- yield

```cpp

// ====-----yield -----==== //
fn fibonacci() {
    let a = 0;
    let b = 1;

    while true {
        yield a;
        let temp = a;
        a = b;
        b = temp + b;
    }
}

for i in fibonacci() {
    print(i);
    if i > 100 {
        break;
    }
}

```

# casting

a as unsafe int       // static_cast<int>(aa)
reinterpret a as int  // reinterpret_cast<int>(aa)
eval a as int         // dynamic_cast<int>(a)
std::cast::reinterpret<>()

```cpp
namespace std {
    namespace cast {

        priv define create_cast(name: str) {
            define name(ty: Type!, val: Identifier! | Literal! ) {
                extern "C++" name+"_cast"<ty>(val);
            }
        }

        /** helix code:
        define static(ty: Type!, val: Val!) {
            extern "C++" static_cast<ty>(val);
        }
        */
        create_cast!("static");
        create_cast!("reinterpret");
        create_cast!("dynamic");
        create_cast!("const");
        create_cast!("volatile");


        macro any_cast(dest: Type!, src: Identifier! | Literal!) {
            switch (compiler::TARGET) {
                case compiler::Target::CPP {
                    unsafe extern "C++" (dest)src;
                    break;
                }

                case compiler::Target::C {
                    extern "C" (dest)src;
                    break;
                }

                default {
                    panic MacroRuntimeError("Unsupported target");
                }
            }
        }
    }
}


```

# Prelude

```cpp

export std::io::print;
export std::io::println;

```



# When colon and when no colon



```py
if a == b:
    print()


```



# Emit Class Functions
- emit::func
- emit::inline


a as int

if T is int {
    return 4;
} else if T is float {
    return 4;
} else if T is double {
    return 8;
} else {
    return sizeof(T);
}

# Keyword Pairs
- else if
- else unless



# Macros
- assert!
- sizeof!
- typeof!

# Modifiers


# Config Options
post fix or prefix types
public or private by default
const or let by default





# if def and if not def are in each namespace

global define PI: 3.14159;

global

