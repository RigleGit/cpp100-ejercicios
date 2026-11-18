#include <cctype>
#include <iostream>
#include <map>
#include <string>

std::string enMinusculas(std::string texto) {
    for (char& c : texto) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return texto;
}

int main() {
    std::map<std::string, int> frecuencias;
    int total = 0;
    std::string palabra;
    while (std::cin >> palabra) {
        ++frecuencias[enMinusculas(palabra)];
        ++total;
    }

    std::cout << "Palabras: " << total << '\n';
    std::cout << "Distintas: " << frecuencias.size() << '\n';
    for (const auto& [clave, veces] : frecuencias) {
        std::cout << clave << ": " << veces << '\n';
    }
}
