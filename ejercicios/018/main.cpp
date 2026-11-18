#include <iostream>

constexpr int maximo_n{20};

unsigned long long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return static_cast<unsigned long long>(n) * factorial(n - 1);
}

int main() {
    int n{};
    if (!(std::cin >> n)) {
        std::cerr << "Error: se esperaba un entero.\n";
        return 1;
    }
    if (n < 0 || n > maximo_n) {
        std::cerr << "Error: n debe estar entre 0 y " << maximo_n << ".\n";
        return 1;
    }
    std::cout << n << "! = " << factorial(n) << '\n';
}
