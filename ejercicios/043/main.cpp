#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    int umbral = 0;
    int n = 0;
    if (!(std::cin >> umbral >> n) || n < 0 || n > 1000) {
        std::cerr << "Error: escribe el umbral y cuántos números hay "
                     "(de 0 a 1000).\n";
        return 1;
    }
    std::vector<int> numeros(n);
    for (int& numero : numeros) {
        if (!(std::cin >> numero)) {
            std::cerr << "Error: faltan números o hay uno no válido.\n";
            return 1;
        }
    }

    auto supera = [umbral](int x) { return x > umbral; };
    auto cuantos = std::count_if(numeros.begin(), numeros.end(), supera);
    std::cout << "Mayores que " << umbral << ": " << cuantos << '\n';

    auto it = std::find_if(numeros.begin(), numeros.end(), supera);
    if (it == numeros.end()) {
        std::cout << "Ninguno supera el umbral.\n";
    } else {
        auto posicion = std::distance(numeros.begin(), it);
        std::cout << "Primero: " << *it << " en la posición " << posicion
                  << '\n';
    }
}
