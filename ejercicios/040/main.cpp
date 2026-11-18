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

int quitarNegativos(std::vector<int>& valores) {
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
    if (!leerValores(valores)) {
        std::cerr << "Error: faltan números o hay uno no válido.\n";
        return 1;
    }

    std::vector<int> conBucle = valores;
    const int quitadosBucle = quitarNegativos(conBucle);

    std::vector<int> conErase = valores;
    const std::size_t quitadosErase =
        std::erase_if(conErase, [](int valor) { return valor < 0; });

    mostrar("Original", valores);
    mostrar("Con el bucle", conBucle);
    std::cout << "Quitados con el bucle: " << quitadosBucle << '\n';
    mostrar("Con std::erase_if", conErase);
    std::cout << "Quitados con std::erase_if: " << quitadosErase << '\n';
}
