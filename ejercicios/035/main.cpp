#include <cstddef>
#include <format>
#include <iostream>
#include <vector>

long long sumar(const std::vector<int>& valores) {
    long long suma = 0;
    for (int valor : valores) {
        suma += valor;
    }
    return suma;
}

int main() {
    int n{};
    if (!(std::cin >> n) || n < 0 || n > 1000) {
        std::cerr << "Error: entrada no válida.\n";
        return 1;
    }
    std::vector<int> valores(static_cast<std::size_t>(n));
    for (int& valor : valores) {
        if (!(std::cin >> valor)) {
            std::cerr << "Error: entrada no válida.\n";
            return 1;
        }
    }

    const long long suma = sumar(valores);
    std::cout << "Cantidad: " << valores.size() << '\n';
    std::cout << "Suma: " << suma << '\n';
    if (valores.empty()) {
        std::cout << "Media: sin valores\n";
    } else {
        const double media =
            static_cast<double>(suma) / static_cast<double>(valores.size());
        std::cout << std::format("Media: {:.2f}\n", media);
    }
}
