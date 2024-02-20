#include <stdio.h>

extern "C" {
    int sub(int a, int b) {
        return a - b;
    }

    int add(int a, int b) {
        return a + b;
    }
}