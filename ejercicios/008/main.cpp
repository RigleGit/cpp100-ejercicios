#include <iostream>

int main() {
    int n{};
    std::cin >> n;

    if (n % 2 == 0) {
        std::cout << "Paridad: par\n";
    } else {
        std::cout << "Paridad: impar\n";
    }

    if (n > 0) {
        std::cout << "Signo: positivo\n";
    } else if (n < 0) {
        std::cout << "Signo: negativo\n";
    } else {
        std::cout << "Signo: cero\n";
    }
}
