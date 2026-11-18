#include <cstdlib>
#include <iostream>

constexpr int maximo_intentos{5};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: programa SECRETO (entero entre 1 y 100)\n";
        return 1;
    }
    int secreto{std::atoi(argv[1])};
    if (secreto < 1 || secreto > 100) {
        std::cerr << "Error: el secreto debe estar entre 1 y 100.\n";
        return 1;
    }

    int intentos{0};
    int propuesta{0};
    do {
        if (!(std::cin >> propuesta)) {
            std::cerr << "Error: se esperaba otro intento.\n";
            return 1;
        }
        ++intentos;
        if (propuesta < secreto) {
            std::cout << "Más alto.\n";
        } else if (propuesta > secreto) {
            std::cout << "Más bajo.\n";
        }
    } while (propuesta != secreto && intentos < maximo_intentos);

    if (propuesta == secreto) {
        std::cout << "¡Acertaste! Intentos: " << intentos << '\n';
    } else {
        std::cout << "Sin intentos. El número era " << secreto << ".\n";
    }
}
