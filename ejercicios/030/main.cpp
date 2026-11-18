#include <iostream>
#include <sstream>
#include <string>

int contar_palabras(const std::string& linea) {
    std::istringstream flujo(linea);
    std::string palabra;
    int total = 0;
    while (flujo >> palabra) {
        ++total;
    }
    return total;
}

int main() {
    std::string linea;
    int lineas = 0;
    int palabras = 0;
    while (std::getline(std::cin, linea)) {
        ++lineas;
        const int en_linea = contar_palabras(linea);
        palabras += en_linea;
        std::cout << "Línea " << lineas << ": " << en_linea << '\n';
    }
    std::cout << "Líneas: " << lineas << '\n';
    std::cout << "Palabras: " << palabras << '\n';
}
