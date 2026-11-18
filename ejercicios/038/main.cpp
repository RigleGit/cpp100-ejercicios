#include <cstddef>
#include <iostream>
#include <string>
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

void mostrar(const std::string& etiqueta, const std::vector<int>& valores) {
    std::cout << etiqueta << ':';
    for (int valor : valores) {
        std::cout << ' ' << valor;
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> valores;
    int indice{};
    if (!leerValores(valores) || !(std::cin >> indice)) {
        std::cerr << "Error: entrada no válida.\n";
        return 1;
    }
    if (indice < 0 || static_cast<std::size_t>(indice) >= valores.size()) {
        std::cerr << "Error: índice fuera de rango.\n";
        return 1;
    }

    mostrar("Antes", valores);
    const int eliminado = valores[static_cast<std::size_t>(indice)];
    valores.erase(valores.begin() + indice);
    std::cout << "Eliminado: " << eliminado << '\n';
    mostrar("Después", valores);
}
