#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

std::string invertir(const std::string& texto) {
    std::string resultado;
    for (std::size_t i = texto.size(); i > 0; --i) {
        resultado += texto[i - 1];
    }
    return resultado;
}

char minuscula(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

bool esPalindromo(const std::string& texto) {
    const std::size_t n = texto.size();
    for (std::size_t i = 0; i < n / 2; ++i) {
        if (minuscula(texto[i]) != minuscula(texto[n - 1 - i])) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string palabra;
    if (!(std::cin >> palabra)) {
        std::cerr << "Error: falta la palabra.\n";
        return 1;
    }

    std::cout << "Al revés: " << invertir(palabra) << '\n';
    if (esPalindromo(palabra)) {
        std::cout << "Es palíndromo.\n";
    } else {
        std::cout << "No es palíndromo.\n";
    }
}
