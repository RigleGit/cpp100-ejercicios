#include <iostream>
#include <string>

bool es_vocal(char c) {
    switch (c) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        return true;
    default:
        return false;
    }
}

int contar_vocales(const std::string& texto) {
    int total = 0;
    for (char c : texto) {
        if (es_vocal(c)) {
            ++total;
        }
    }
    return total;
}

int main() {
    std::string linea;
    std::getline(std::cin, linea);
    std::cout << "Vocales: " << contar_vocales(linea) << '\n';
}
