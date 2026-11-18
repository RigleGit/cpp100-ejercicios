#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 0 || n > 1000) {
        std::cerr << "Error: escribe cuántos números hay (de 0 a 1000).\n";
        return 1;
    }
    std::vector<int> numeros(static_cast<std::size_t>(n));
    for (int& numero : numeros) {
        if (!(std::cin >> numero) || numero < -10000 || numero > 10000) {
            std::cerr << "Error: faltan números o hay uno no válido (de "
                         "-10000 a 10000).\n";
            return 1;
        }
    }

    std::ranges::sort(numeros);
    std::cout << "Ordenados:";
    for (int x : numeros) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';

    auto es_par = [](int x) { return x % 2 == 0; };
    auto cuadrado = [](int x) { return x * x; };
    auto resultado = numeros | std::views::filter(es_par) |
                     std::views::transform(cuadrado);

    std::cout << "Cuadrados de los pares:";
    for (int x : resultado) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}
