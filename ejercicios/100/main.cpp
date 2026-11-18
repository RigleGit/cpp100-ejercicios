#include "arbol.hpp"
#include "lexico.hpp"

#include <cstddef>
#include <format>
#include <iostream>
#include <string>

constexpr std::size_t longitud_maxima = 1000;

std::string resolver(const std::string& linea, bool mostrar_arbol) {
    if (linea.size() > longitud_maxima) {
        throw ErrorExpresion{longitud_maxima + 1,
                             "la línea supera los 1000 bytes"};
    }
    const PunteroNodo raiz = analizar(tokenizar(linea));
    double valor = evaluar(*raiz);
    if (valor == 0.0) {
        valor = 0.0; // evita mostrar -0
    }
    const std::string izquierda = mostrar_arbol ? a_texto(*raiz) : linea;
    return std::format("{} = {}", izquierda, valor);
}

int main(int argc, char* argv[]) {
    const bool mostrar_arbol =
        argc == 2 && std::string{argv[1]} == "--arbol";
    if (argc > 2 || (argc == 2 && !mostrar_arbol)) {
        std::cerr << "Uso: 100 [--arbol]\n";
        return 1;
    }

    std::string linea;
    int numero = 0;
    bool hubo_errores = false;
    while (std::getline(std::cin, linea)) {
        ++numero;
        if (linea.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }
        try {
            std::cout << resolver(linea, mostrar_arbol) << '\n';
        } catch (const ErrorExpresion& e) {
            std::cerr << std::format("Error en la línea {}, columna {}: "
                                     "{}.\n",
                                     numero, e.columna(), e.what());
            if (linea.size() <= longitud_maxima) {
                std::cerr << "  " << linea << '\n'
                          << std::string(e.columna() + 1, ' ') << "^\n";
            }
            hubo_errores = true;
        }
    }
    return hubo_errores ? 1 : 0;
}
