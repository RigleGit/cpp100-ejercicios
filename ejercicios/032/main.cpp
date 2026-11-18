#include <cstddef>
#include <iostream>
#include <limits>
#include <string>

std::string recortar(const std::string& texto) {
    const std::string blancos = " \t\r";
    const std::size_t inicio = texto.find_first_not_of(blancos);
    if (inicio == std::string::npos) {
        return "";
    }
    const std::size_t fin = texto.find_last_not_of(blancos);
    return texto.substr(inicio, fin - inicio + 1);
}

int main() {
    int n{};
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Error: la primera línea debe ser un entero no "
                     "negativo.\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 1; i <= n; ++i) {
        std::string linea;
        if (!std::getline(std::cin, linea)) {
            std::cerr << "Error: se esperaban " << n
                      << " líneas y llegaron " << i - 1 << ".\n";
            return 1;
        }
        const std::string limpia = recortar(linea);
        if (limpia.empty()) {
            std::cout << i << ": (vacía)\n";
        } else {
            std::cout << i << ": [" << limpia << "]\n";
        }
    }
}
