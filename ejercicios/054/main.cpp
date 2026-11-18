#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string enMinusculas(std::string texto) {
    for (char& c : texto) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return texto;
}

int main() {
    std::map<std::string, std::vector<std::string>> grupos;
    std::string palabra;
    while (std::cin >> palabra) {
        palabra = enMinusculas(palabra);
        std::string clave = palabra;
        std::sort(clave.begin(), clave.end());
        std::vector<std::string>& grupo = grupos[clave];
        if (std::find(grupo.begin(), grupo.end(), palabra) == grupo.end()) {
            grupo.push_back(palabra);
        }
    }

    int mostrados = 0;
    for (const auto& [clave, palabras] : grupos) {
        if (palabras.size() < 2) {
            continue;
        }
        ++mostrados;
        std::cout << clave << ':';
        for (const std::string& p : palabras) {
            std::cout << ' ' << p;
        }
        std::cout << '\n';
    }
    if (mostrados == 0) {
        std::cout << "Sin anagramas.\n";
    }
}
