#ifdef NDEBUG
#error "Compila las pruebas sin NDEBUG: assert no comprobaría nada."
#endif

#include "arbol.hpp"
#include "lexico.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

double calcular(const std::string& texto) {
    return evaluar(*analizar(tokenizar(texto)));
}

std::string arbol(const std::string& texto) {
    return a_texto(*analizar(tokenizar(texto)));
}

// Devuelve la columna del error, o 0 si no hubo error.
std::size_t columna_error(const std::string& texto) {
    try {
        calcular(texto);
    } catch (const ErrorExpresion& e) {
        return e.columna();
    }
    return 0;
}

int main() {
    // Tokens.
    const auto tokens = tokenizar("12.5*(3)");
    assert(tokens.size() == 6);
    assert(tokens[0].tipo == TipoToken::numero && tokens[0].valor == 12.5);
    assert(tokens[1].tipo == TipoToken::por && tokens[1].columna == 5);
    assert(tokens.back().tipo == TipoToken::fin);
    assert(tokenizar("").size() == 1);

    // Precedencia y asociatividad.
    assert(arbol("1 + 2 * 3") == "(+ 1 (* 2 3))");
    assert(arbol("8 - 3 - 2") == "(- (- 8 3) 2)");
    assert(arbol("-2 * 3") == "(* (- 2) 3)");
    assert(calcular("(1 + 2) * 3") == 9.0);
    assert(calcular("8 / 4 / 2") == 1.0);
    assert(calcular("2 * -3") == -6.0);
    assert(calcular("--4") == 4.0);

    // Errores con su columna.
    assert(columna_error("2 +") == 4);
    assert(columna_error("(1 + 2") == 7);
    assert(columna_error("1 + 2)") == 6);
    assert(columna_error("2 3") == 3);
    assert(columna_error("4 / (2 - 2)") == 3);
    assert(columna_error("1 ^ 2") == 3);
    assert(columna_error("3.") == 3);
    assert(columna_error(std::string(101, '(') + "1") == 101);
    assert(columna_error(std::string(100, '(') + "1" +
                         std::string(100, ')')) == 0);

    std::cout << "Pruebas de la calculadora superadas.\n";
}
