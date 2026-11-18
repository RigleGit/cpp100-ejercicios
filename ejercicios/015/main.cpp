#include <iostream>

int maximo(int a, int b);

int main() {
    int a{};
    int b{};
    if (!(std::cin >> a >> b)) {
        std::cerr << "Error: se esperaban dos enteros.\n";
        return 1;
    }
    std::cout << "El mayor es " << maximo(a, b) << ".\n";
}

int maximo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
