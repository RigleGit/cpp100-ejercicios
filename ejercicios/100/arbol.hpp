#ifndef ARBOL_HPP
#define ARBOL_HPP

#include "lexico.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct Nodo;
using PunteroNodo = std::unique_ptr<Nodo>;

struct Numero {
    double valor;
};

struct Negacion {
    PunteroNodo operando;
};

struct Binaria {
    char operador;       // '+', '-', '*' o '/'
    std::size_t columna; // dónde estaba el operador en el texto
    PunteroNodo izquierda;
    PunteroNodo derecha;
};

struct Nodo {
    std::variant<Numero, Negacion, Binaria> contenido;
};

// Gramática, de menor a mayor precedencia:
//   expresion := termino (('+' | '-') termino)*
//   termino   := factor (('*' | '/') factor)*
//   factor    := '-' factor | numero | '(' expresion ')'
// Lanza ErrorExpresion si los tokens no forman una expresión completa o
// si los paréntesis y signos '-' se anidan más de 100 niveles.
PunteroNodo analizar(const std::vector<Token>& tokens);

// Lanza ErrorExpresion ante una división entre cero o un resultado que
// no cabe en un double.
double evaluar(const Nodo& nodo);

// Forma prefija con paréntesis: (+ 1 (* 2 3)).
std::string a_texto(const Nodo& nodo);

#endif
