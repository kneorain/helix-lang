#include "helix-compiler/src/cpp/mod.rs.h"
#include <iostream>

void c(rust::Str greeting) {
    std::cout << greeting << std::endl;
    std::cout << "HELLO FROM THE C++" << std::endl;
    hello_from_python();
}