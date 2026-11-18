#include <cstddef>
#include <iostream>
#include <vector>

using Matriz = std::vector<std::vector<int>>;

Matriz trasponer(const Matriz& m) {
    const std::size_t filas = m.size();
    const std::size_t columnas = m[0].size();
    Matriz t(columnas, std::vector<int>(filas));
    for (std::size_t i = 0; i < filas; ++i) {
        for (std::size_t j = 0; j < columnas; ++j) {
            t[j][i] = m[i][j];
        }
    }
    return t;
}

void mostrar(const Matriz& m) {
    for (const std::vector<int>& fila : m) {
        for (std::size_t j = 0; j < fila.size(); ++j) {
            if (j > 0) {
                std::cout << ' ';
            }
            std::cout << fila[j];
        }
        std::cout << '\n';
    }
}

int main() {
    int filas{};
    int columnas{};
    if (!(std::cin >> filas >> columnas) || filas < 1 || filas > 10 ||
        columnas < 1 || columnas > 10) {
        std::cerr << "Error: filas y columnas van de 1 a 10.\n";
        return 1;
    }

    Matriz m(static_cast<std::size_t>(filas),
             std::vector<int>(static_cast<std::size_t>(columnas)));
    for (std::vector<int>& fila : m) {
        for (int& celda : fila) {
            if (!(std::cin >> celda)) {
                std::cerr << "Error: faltan valores de la matriz.\n";
                return 1;
            }
        }
    }

    const Matriz t = trasponer(m);
    std::cout << "Traspuesta (" << t.size() << 'x' << t[0].size() << "):\n";
    mostrar(t);
}
