#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

char inicial(const std::string& palabra) {
    unsigned char primera = static_cast<unsigned char>(palabra.front());
    if (std::isalpha(primera)) {
        return static_cast<char>(std::toupper(primera));
    }
    return '#';
}

int main() {
    std::map<char, std::vector<std::string>> grupos;
    std::string palabra;
    while (std::cin >> palabra) {
        grupos[inicial(palabra)].push_back(palabra);
    }

    if (grupos.empty()) {
        std::cout << "Sin palabras.\n";
    }
    for (const auto& [letra, palabras] : grupos) {
        std::cout << letra << " (" << palabras.size() << "):";
        for (const std::string& p : palabras) {
            std::cout << ' ' << p;
        }
        std::cout << '\n';
    }
}
