#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> palabras;
    std::string palabra;
    while (std::cin >> palabra) {
        palabras.push_back(palabra);
    }
    std::cout << "Leídas: " << palabras.size() << '\n';

    std::sort(palabras.begin(), palabras.end());
    auto nuevo_final = std::unique(palabras.begin(), palabras.end());
    palabras.erase(nuevo_final, palabras.end());

    std::cout << "Distintas: " << palabras.size() << '\n';
    for (const std::string& p : palabras) {
        std::cout << p << '\n';
    }
}
