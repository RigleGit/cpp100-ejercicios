#include <cstddef>
#include <iostream>
#include <string>
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

void mostrar(const std::string& etiqueta, const std::vector<int>& valores) {
    std::cout << etiqueta << ':';
    for (int valor : valores) {
        std::cout << ' ' << valor;
    }
    std::cout << '\n';
}

bool es_negativo(int valor) {
    return valor < 0;
}

int quitar_negativos(std::vector<int>& valores) {
    int quitados = 0;
    auto it = valores.begin();
    while (it != valores.end()) {
        if (*it < 0) {
            it = valores.erase(it);
            ++quitados;
        } else {
            ++it;
        }
    }
    return quitados;
}

int main() {
    std::vector<int> valores;
    if (!leer_valores(valores)) {
        std::cerr << "Error: faltan números o hay uno no válido.\n";
        return 1;
    }

    std::vector<int> con_bucle = valores;
    const int quitados_bucle = quitar_negativos(con_bucle);

    std::vector<int> con_erase = valores;
    const std::size_t quitados_erase =
        std::erase_if(con_erase, es_negativo);

    mostrar("Original", valores);
    mostrar("Con el bucle", con_bucle);
    std::cout << "Quitados con el bucle: " << quitados_bucle << '\n';
    mostrar("Con std::erase_if", con_erase);
    std::cout << "Quitados con std::erase_if: " << quitados_erase << '\n';
}
