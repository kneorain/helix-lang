
#include "cstdio"
#include "iostream"
#include "vector"
#include "string"
#include "concepts"
struct Fraction {
    int n;
    int d;
};
int add(int a, int b) {
    return a + b;
}
Fraction add(Fraction a, Fraction b) {
    auto new_n = add(a.n + b.d, b.n + a.d);
    auto new_d = a.d * b.d;
    return {new_n, new_d};
}
inline Fraction operator+(Fraction a, Fraction b) { return add(a, b); }
Fraction        subtract(Fraction a, Fraction b) {
    auto new_n = add(a.n - b.d, b.n - a.d);
    auto new_d = a.d * b.d;
    return {new_n, new_d};
}
inline Fraction operator-(Fraction a, Fraction b) { return subtract(a, b); }
Fraction        multiply(Fraction a, Fraction b) {
    auto new_n = a.n * b.n;
    auto new_d = a.d * b.d;
    return {new_n, new_d};
}
inline Fraction operator*(Fraction a, Fraction b) { return multiply(a, b); }
Fraction        divide(Fraction a, Fraction b) {
    auto new_n = a.n * b.d;
    auto new_d = a.d * b.n;
    return {new_n, new_d};
}
inline Fraction operator/(Fraction a, Fraction b) { return divide(a, b); }
Fraction        unary_minus(Fraction a) {
    return {(-(a.n)), a.d};
}
inline Fraction operator-(Fraction a) { return unary_minus(a); }
Fraction        unary_plus(Fraction a) {
    return {a.n, a.d};
}
inline Fraction operator+(Fraction a) { return unary_plus(a); }
Fraction        increment(Fraction a) {
    return {a.n + a.d, a.d};
}
inline Fraction operator++(Fraction a) { return increment(a); }
Fraction        decrement(Fraction a) {
    return {a.n - a.d, a.d};
}
inline Fraction operator--(Fraction a) { return decrement(a); }
Fraction        add_assign(Fraction a, Fraction b) {
    return a + b;
}
inline Fraction operator+=(Fraction a, Fraction b) { return add_assign(a, b); }
Fraction        subtract_assign(Fraction a, Fraction b) {
    return a - b;
}
inline Fraction operator-=(Fraction a, Fraction b) { return subtract_assign(a, b); }
Fraction        multiply_assign(Fraction a, Fraction b) {
    return a * b;
}
inline Fraction operator*=(Fraction a, Fraction b) { return multiply_assign(a, b); }
Fraction        divide_assign(Fraction a, Fraction b) {
    return a / b;
}
inline Fraction operator/=(Fraction a, Fraction b) { return divide_assign(a, b); }
Fraction        modulus_assign(Fraction a, Fraction b) {
    return {a.n % b.n, a.d % b.d};
}
inline Fraction operator%=(Fraction a, Fraction b) { return modulus_assign(a, b); }
Fraction        bitwise_and_assign(Fraction a, Fraction b) {
    return {a.n & b.n, a.d & b.d};
}
inline Fraction operator&=(Fraction a, Fraction b) { return bitwise_and_assign(a, b); }
Fraction        bitwise_or_assign(Fraction a, Fraction b) {
    return {a.n | b.n, a.d | b.d};
}
inline Fraction operator|=(Fraction a, Fraction b) { return bitwise_or_assign(a, b); }
Fraction        bitwise_xor_assign(Fraction a, Fraction b) {
    return {a.n ^ b.n, a.d ^ b.d};
}
inline Fraction operator^=(Fraction a, Fraction b) { return bitwise_xor_assign(a, b); }
Fraction        left_shift_assign(Fraction a, Fraction b) {
    return {a.n << b.n, a.d << b.d};
}
inline Fraction operator<<=(Fraction a, Fraction b) { return left_shift_assign(a, b); }
Fraction        right_shift_assign(Fraction a, Fraction b) {
    return {a.n >> b.n, a.d >> b.d};
}
inline Fraction operator>>=(Fraction a, Fraction b) { return right_shift_assign(a, b); }
Fraction        modulus(Fraction a, Fraction b) {
    return {a.n % b.n, a.d % b.d};
}
inline Fraction operator%(Fraction a, Fraction b) { return modulus(a, b); }
Fraction        bitwise_and(Fraction a, Fraction b) {
    return {a.n & b.n, a.d & b.d};
}
inline Fraction operator&(Fraction a, Fraction b) { return bitwise_and(a, b); }
Fraction        bitwise_or(Fraction a, Fraction b) {
    return {a.n | b.n, a.d | b.d};
}
inline Fraction operator|(Fraction a, Fraction b) { return bitwise_or(a, b); }
Fraction        bitwise_xor(Fraction a, Fraction b) {
    return {a.n ^ b.n, a.d ^ b.d};
}
inline Fraction operator^(Fraction a, Fraction b) { return bitwise_xor(a, b); }
Fraction        left_shift(Fraction a, Fraction b) {
    return {a.n << b.n, a.d << b.d};
}
inline Fraction operator<<(Fraction a, Fraction b) { return left_shift(a, b); }
Fraction        right_shift(Fraction a, Fraction b) {
    return {a.n >> b.n, a.d >> b.d};
}
inline Fraction operator>>(Fraction a, Fraction b) { return right_shift(a, b); }
bool            less_than(Fraction a, Fraction b) {
    return a.n * b.d < b.n * a.d;
}
inline bool operator<(Fraction a, Fraction b) { return less_than(a, b); }
bool        greater_than(Fraction a, Fraction b) {
    return a.n * b.d > b.n * a.d;
}
inline bool operator>(Fraction a, Fraction b) { return greater_than(a, b); }
bool        less_than_or_equal(Fraction a, Fraction b) {
    return a.n * b.d <= b.n * a.d;
}
inline bool operator<=(Fraction a, Fraction b) { return less_than_or_equal(a, b); }
bool        greater_than_or_equal(Fraction a, Fraction b) {
    return a.n * b.d >= b.n * a.d;
}
inline bool operator>=(Fraction a, Fraction b) { return greater_than_or_equal(a, b); }
bool        logical_and(Fraction a, Fraction b) {
    return a.n && b.n && a.d && b.d;
}
inline bool operator&&(Fraction a, Fraction b) { return logical_and(a, b); }
bool        logical_or(Fraction a, Fraction b) {
    return a.n || b.n || a.d || b.d;
}
inline bool operator||(Fraction a, Fraction b) { return logical_or(a, b); }
bool        logical_not(Fraction a) {
    return (!(a.n && (!(a.d))));
}
inline bool operator!(Fraction a) { return logical_not(a); }
bool        equals(Fraction a, Fraction b) {
    return a.n * b.d == b.n * a.d;
}
inline bool operator==(Fraction a, Fraction b) { return equals(a, b); }
int         factorial(int n) {
    if (n <= 1) {
        return 1;
    };
    return n * factorial(n - 1);
}
std ::vector<int> range(int n) {
    std ::vector<int> v;
    for (int i = 0; i < n; (++(i))) {
        v.push_back(i);
    };
    return v;
}
template <typename Self>
concept Foo = requires(Self self) {
    { self.foo() } -> std ::same_as<int>;
};
template <typename Self>
concept Bar = Foo<Self> && requires(Self self) {
    { self.bar() } -> std ::same_as<int>;
};
class Fuzz {
    int foo() {
        return 0;
    };
};
template <typename T>
    requires Bar<T> && std ::is_base_of<Fuzz, T>::value
class Fish {
    T fish;
};
void print_vector(std ::vector<int> v) {
    for (auto i : range(v.size())) {
        printf("Vector element %d: %d\n", i, v[i]);
    };
}
int main() {
    auto sum = add(5, 7);
    printf("Sum: %d\n", sum);
    auto fact = factorial(5);
    printf("Factorial: %d\n", fact);
    std ::vector<int> numbers = {1, 2, 3, 4};
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);
    print_vector(numbers);
    auto greeting = std ::string("Hello from Helix and C++!");
    std ::cout << greeting << std ::endl;
    if (sum > fact) {
        printf("Sum is greater than factorial.\n");
    } else {
        printf("Factorial is greater than or equal to sum.\n");
    };
    Fraction f1 = {1, 2};
    Fraction f2 = {3, 4};
    auto     f3 = f1 + f2;
    printf("f1: %d/%d\n", f1.n, f1.d);
    printf("f2: %d/%d\n", f2.n, f2.d);
    printf("f3 (f1 + f2): %d/%d\n", f3.n, f3.d);
    printf("f1 == f2: %s\n", f1 == (f2) ? "True" : "False");
    return 0;
}
