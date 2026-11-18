#include <iostream>

int main() {
    double nota{};
    std::cin >> nota;

    if (nota < 0 || nota > 10) {
        std::cerr << "Error: la nota debe estar entre 0 y 10.\n";
        return 1;
    }

    if (nota < 5) {
        std::cout << "Insuficiente\n";
    } else if (nota < 6) {
        std::cout << "Suficiente\n";
    } else if (nota < 7) {
        std::cout << "Bien\n";
    } else if (nota < 9) {
        std::cout << "Notable\n";
    } else {
        std::cout << "Sobresaliente\n";
    }
}
