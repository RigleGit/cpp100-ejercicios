#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

auto mayor_que(int limite) {
    return [limite](int x) { return x > limite; };
}

int main() {
    int umbral = 0;
    int n = 0;
    if (!(std::cin >> umbral >> n) || n < 0 || n > 1000) {
        std::cerr << "Error: escribe el umbral y cuántos números hay "
                     "(de 0 a 1000).\n";
        return 1;
    }
    std::vector<int> numeros(static_cast<std::size_t>(n));
    for (int& numero : numeros) {
        if (!(std::cin >> numero) || numero < -1000000 ||
            numero > 1000000) {
            std::cerr << "Error: faltan números o hay uno no válido (de "
                         "-1000000 a 1000000).\n";
            return 1;
        }
    }

    auto filtro = mayor_que(umbral);
    std::vector<int> elegidos;
    int suma = 0;
    int comprobaciones = 0;
    std::for_each(numeros.begin(), numeros.end(),
                  [filtro, &elegidos, &suma, &comprobaciones](int x) {
                      ++comprobaciones;
                      if (filtro(x)) {
                          elegidos.push_back(x);
                          suma += x;
                      }
                  });

    std::cout << "Mayores que " << umbral << ":";
    if (elegidos.empty()) {
        std::cout << " ninguno";
    }
    for (int x : elegidos) {
        std::cout << ' ' << x;
    }
    std::cout << "\nSuma: " << suma << '\n';
    std::cout << "Comprobaciones: " << comprobaciones << '\n';
}
