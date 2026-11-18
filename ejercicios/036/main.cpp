#include <cstddef>
#include <iostream>
#include <vector>

bool leer_valores(std::vector<int>& valores) {
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

struct Extremos {
    int minimo;
    int maximo;
};

// Antes de llamarla, comprueba que valores no esté vacío.
Extremos extremos(const std::vector<int>& valores) {
    Extremos resultado{valores[0], valores[0]};
    for (int valor : valores) {
        if (valor < resultado.minimo) {
            resultado.minimo = valor;
        }
        if (valor > resultado.maximo) {
            resultado.maximo = valor;
        }
    }
    return resultado;
}

int main() {
    std::vector<int> valores;
    if (!leer_valores(valores)) {
        std::cerr << "Error: faltan números o hay uno no válido.\n";
        return 1;
    }
    if (valores.empty()) {
        std::cerr << "Error: no hay valores.\n";
        return 1;
    }

    const auto [minimo, maximo] = extremos(valores);
    std::cout << "Mínimo: " << minimo << '\n';
    std::cout << "Máximo: " << maximo << '\n';
}
