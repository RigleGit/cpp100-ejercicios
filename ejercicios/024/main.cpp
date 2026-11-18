#include <cstddef>
#include <iostream>
#include <iterator>

int* buscar(int* datos, std::size_t n, int valor) {
    for (std::size_t i = 0; i < n; ++i) {
        if (datos[i] == valor) {
            return &datos[i];
        }
    }
    return nullptr;
}

void mostrar(const int* datos, std::size_t n) {
    std::cout << "Puntos:";
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << ' ' << datos[i];
    }
    std::cout << '\n';
}

int main() {
    int puntos[] = {12, 7, 30, 7, 25};
    int valor{};
    if (!(std::cin >> valor)) {
        std::cerr << "Error: se esperaba un entero.\n";
        return 1;
    }

    int* encontrado = buscar(puntos, std::size(puntos), valor);
    if (encontrado == nullptr) {
        std::cout << "No encontrado.\n";
    } else {
        std::cout << "Encontrado en la posición " << (encontrado - puntos)
                  << ".\n";
        *encontrado = 0;
    }
    mostrar(puntos, std::size(puntos));
}
