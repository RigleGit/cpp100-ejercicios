#include <iostream>
#include <vector>

std::vector<long long> acumulados(const std::vector<int>& valores) {
    std::vector<long long> resultado;
    resultado.reserve(valores.size());
    long long suma = 0;
    for (int valor : valores) {
        suma += valor;
        resultado.push_back(suma);
    }
    return resultado;
}

int main() {
    std::vector<int> valores;
    while (std::cin >> std::ws && !std::cin.eof()) {
        int valor{};
        if (!(std::cin >> valor)) {
            std::cerr << "Error: entrada no válida.\n";
            return 1;
        }
        valores.push_back(valor);
    }

    const std::vector<long long> sumas = acumulados(valores);
    std::cout << "Leídos: " << valores.size() << '\n';
    std::cout << "Valores:";
    for (int v : valores) {
        std::cout << ' ' << v;
    }
    std::cout << "\nAcumulados:";
    for (long long s : sumas) {
        std::cout << ' ' << s;
    }
    std::cout << '\n';
}
