#include <iostream>
#include <sstream>
#include <string>

int contarPalabras(const std::string& linea) {
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
        const int enLinea = contarPalabras(linea);
        palabras += enLinea;
        std::cout << "Línea " << lineas << ": " << enLinea << '\n';
    }
    std::cout << "Líneas: " << lineas << '\n';
    std::cout << "Palabras: " << palabras << '\n';
}
