#include "fraccion.hpp"

#include <charconv>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <system_error>

long long leer_entero(const std::string& texto) {
    long long valor = 0;
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, valor);
    if (error != std::errc{} || resto != fin || valor < -1'000'000'000 ||
        valor > 1'000'000'000) {
        throw std::invalid_argument{"'" + texto +
                                    "' no es un entero de hasta 10^9"};
    }
    return valor;
}

Fraccion leer_fraccion(const std::string& texto) {
    const auto barra = texto.find('/');
    if (barra == std::string::npos) {
        return Fraccion{leer_entero(texto)};
    }
    return Fraccion{leer_entero(texto.substr(0, barra)),
                    leer_entero(texto.substr(barra + 1))};
}

Fraccion calcular(const std::string& linea) {
    std::istringstream entrada{linea};
    std::string izquierda;
    std::string operacion;
    std::string derecha;
    std::string sobra;
    if (!(entrada >> izquierda >> operacion >> derecha) ||
        entrada >> sobra || operacion.size() != 1) {
        throw std::invalid_argument{"se esperaba A OP B"};
    }
    const Fraccion a = leer_fraccion(izquierda);
    const Fraccion b = leer_fraccion(derecha);
    switch (operacion[0]) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        throw std::invalid_argument{"operación desconocida '" + operacion +
                                    "'"};
    }
}

int main() {
    std::string linea;
    int numero = 0;
    bool hubo_errores = false;
    while (std::getline(std::cin, linea)) {
        ++numero;
        if (linea.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }
        try {
            const Fraccion resultado = calcular(linea);
            std::cout << linea << " = " << resultado << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Error en la línea " << numero << ": " << e.what()
                      << ".\n";
            hubo_errores = true;
        }
    }
    return hubo_errores ? 1 : 0;
}
