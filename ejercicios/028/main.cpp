#include <cstddef>
#include <iostream>
#include <string>

std::string caracteres(std::size_t n) {
    if (n == 1) {
        return "1 carácter";
    }
    return std::to_string(n) + " caracteres";
}

int main() {
    std::string primera;
    std::string segunda;
    if (!(std::cin >> primera >> segunda)) {
        std::cerr << "Error: se esperaban dos palabras.\n";
        return 1;
    }

    const std::string unidas = primera + " " + segunda;
    std::cout << "Primera: " << primera << " ("
              << caracteres(primera.size()) << ")\n";
    std::cout << "Segunda: " << segunda << " ("
              << caracteres(segunda.size()) << ")\n";
    std::cout << "Unidas: " << unidas << " (" << caracteres(unidas.size())
              << ")\n";

    if (primera == segunda) {
        std::cout << "Son iguales.\n";
    } else if (primera < segunda) {
        std::cout << primera << " va antes que " << segunda << ".\n";
    } else {
        std::cout << segunda << " va antes que " << primera << ".\n";
    }
}
