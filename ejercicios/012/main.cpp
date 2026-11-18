#include <iostream>

int main() {
    long long suma{0};
    int cantidad{0};
    int numero{};

    while (std::cin >> numero) {
        if (numero == 0) {
            std::cout << "Números sumados: " << cantidad << '\n';
            std::cout << "Suma: " << suma << '\n';
            return 0;
        }
        suma += numero;
        ++cantidad;
    }

    if (std::cin.eof()) {
        std::cerr << "Error: la entrada terminó sin el 0 final.\n";
    } else {
        std::cerr << "Error: dato no válido; se esperaba un entero.\n";
    }
    return 1;
}
