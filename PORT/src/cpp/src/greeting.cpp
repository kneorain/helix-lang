#include "helix-compiler/src/cpp/mod.rs.h"
#include <iostream>
#include <cstdint>

void c(rust::Str greeting) {
    std::cout << greeting << std::endl;
    std::cout << "HELLO FROM THE C++" << std::endl;
    hello_from_python();
}

int64_t add_sum(int32_t a, int32_t b) {
    std::cout << "This is the sum of " << a << " and " << b << std::endl;
    std::cout << "SIKE we do **NOT** have a sum" << std::endl;
    return std::pow(a, b);
}