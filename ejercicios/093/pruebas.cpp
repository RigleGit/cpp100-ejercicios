#include "fraccion.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string texto(const Fraccion& f) {
    std::ostringstream salida;
    salida << f;
    return salida.str();
}

bool lanza_domain_error(long long numerador, long long denominador) {
    try {
        Fraccion f{numerador, denominador};
    } catch (const std::domain_error&) {
        return true;
    }
    return false;
}

int main() {
    // Normalización al construir.
    assert(Fraccion(2, 4) == Fraccion(1, 2));
    assert(Fraccion(3, -6).numerador() == -1);
    assert(Fraccion(3, -6).denominador() == 2);
    assert(Fraccion(-3, -6) == Fraccion(1, 2));
    assert(Fraccion(0, 7) == Fraccion());
    assert(lanza_domain_error(1, 0));

    // Operaciones.
    assert(Fraccion(1, 2) + Fraccion(1, 3) == Fraccion(5, 6));
    assert(Fraccion(1, 2) - Fraccion(3, 4) == Fraccion(-1, 4));
    assert(Fraccion(2, 3) * Fraccion(3, 4) == Fraccion(1, 2));
    assert(Fraccion(1, 2) / Fraccion(-1, 4) == Fraccion(-2));
    bool division_por_cero = false;
    try {
        Fraccion(1, 2) / Fraccion(0);
    } catch (const std::domain_error&) {
        division_por_cero = true;
    }
    assert(division_por_cero);

    // Salida.
    assert(texto(Fraccion(6, 3)) == "2");
    assert(texto(Fraccion(-1, 4)) == "-1/4");
    assert(texto(Fraccion()) == "0");

    std::cout << "Pruebas de Fraccion superadas.\n";
}
