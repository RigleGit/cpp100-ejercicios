#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

// Convierte una línea en una edad entre 0 y 130.
// Lanza std::invalid_argument si no es un entero y
// std::out_of_range si lo es pero no cabe en el rango.
int leer_edad(const std::string& texto) {
    std::size_t usados = 0;
    int edad = std::stoi(texto, &usados);
    if (usados != texto.size()) {
        throw std::invalid_argument{"sobran caracteres"};
    }
    if (edad < 0 || edad > 130) {
        throw std::out_of_range{"edad fuera de rango"};
    }
    return edad;
}

int main() {
    std::string linea;
    int numero = 0;
    int validas = 0;
    while (std::getline(std::cin, linea)) {
        ++numero;
        try {
            int edad = leer_edad(linea);
            std::cout << "Línea " << numero << ": " << edad << '\n';
            ++validas;
        } catch (const std::invalid_argument&) {
            std::cerr << "Línea " << numero << ": \"" << linea
                      << "\" no es un entero\n";
        } catch (const std::out_of_range&) {
            std::cerr << "Línea " << numero << ": \"" << linea
                      << "\" está fuera del rango 0-130\n";
        }
    }
    std::cout << "Válidas: " << validas << " de " << numero << '\n';
    return validas == numero ? 0 : 1;
}
