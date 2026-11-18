#include <cstddef>
#include <iostream>
#include <vector>

bool leerValores(std::vector<int>& valores) {
    int n{};
    if (!(std::cin >> n) || n < 0 || n > 1000) {
        return false;
    }
    valores = std::vector<int>(static_cast<std::size_t>(n));
    for (int& valor : valores) {
        if (!(std::cin >> valor)) {
            return false;
        }
    }
    return true;
}

bool estaOrdenado(const std::vector<int>& valores) {
    for (std::size_t i = 1; i < valores.size(); ++i) {
        if (valores[i] < valores[i - 1]) {
            return false;
        }
    }
    return true;
}

// Primera posición cuyo valor no es menor que buscado.
std::size_t buscarPosicion(const std::vector<int>& valores, int buscado) {
    std::size_t izquierda = 0;
    std::size_t derecha = valores.size();
    while (izquierda < derecha) {
        const std::size_t medio = izquierda + (derecha - izquierda) / 2;
        if (valores[medio] < buscado) {
            izquierda = medio + 1;
        } else {
            derecha = medio;
        }
    }
    return izquierda;
}

int main() {
    std::vector<int> valores;
    int buscado{};
    if (!leerValores(valores) || !(std::cin >> buscado)) {
        std::cerr << "Error: faltan números o hay uno no válido.\n";
        return 1;
    }
    if (!estaOrdenado(valores)) {
        std::cerr << "Error: los valores deben ir de menor a mayor.\n";
        return 1;
    }

    const std::size_t posicion = buscarPosicion(valores, buscado);
    if (posicion < valores.size() && valores[posicion] == buscado) {
        std::cout << "Encontrado en la posición " << posicion << ".\n";
    } else {
        std::cout << "No está; iría en la posición " << posicion << ".\n";
    }
}
