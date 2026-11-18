#include "arbol.hpp"

#include <cmath>
#include <format>
#include <utility>

namespace {

constexpr int profundidad_maxima = 100;

class Analizador {
  public:
    explicit Analizador(const std::vector<Token>& tokens)
        : tokens_{tokens} {}

    PunteroNodo completo() {
        PunteroNodo raiz = expresion();
        const Token& resto = actual();
        if (resto.tipo == TipoToken::cierra) {
            throw ErrorExpresion{resto.columna, "')' sin '(' que lo abra"};
        }
        if (resto.tipo != TipoToken::fin) {
            throw ErrorExpresion{resto.columna, "se esperaba un operador"};
        }
        return raiz;
    }

  private:
    const std::vector<Token>& tokens_;
    std::size_t posicion_ = 0;
    int profundidad_ = 0;

    const Token& actual() const {
        return tokens_[posicion_];
    }

    const Token& avanzar() {
        return tokens_[posicion_++];
    }

    static PunteroNodo binaria(const Token& operador, PunteroNodo izquierda,
                               PunteroNodo derecha) {
        char simbolo = '/';
        if (operador.tipo == TipoToken::mas) {
            simbolo = '+';
        } else if (operador.tipo == TipoToken::menos) {
            simbolo = '-';
        } else if (operador.tipo == TipoToken::por) {
            simbolo = '*';
        }
        return std::make_unique<Nodo>(Binaria{simbolo, operador.columna,
                                              std::move(izquierda),
                                              std::move(derecha)});
    }

    PunteroNodo expresion() {
        PunteroNodo izquierda = termino();
        while (actual().tipo == TipoToken::mas ||
               actual().tipo == TipoToken::menos) {
            const Token& operador = avanzar();
            izquierda = binaria(operador, std::move(izquierda), termino());
        }
        return izquierda;
    }

    PunteroNodo termino() {
        PunteroNodo izquierda = factor();
        while (actual().tipo == TipoToken::por ||
               actual().tipo == TipoToken::entre) {
            const Token& operador = avanzar();
            izquierda = binaria(operador, std::move(izquierda), factor());
        }
        return izquierda;
    }

    PunteroNodo factor() {
        const Token& token = actual();
        if (token.tipo == TipoToken::numero) {
            avanzar();
            return std::make_unique<Nodo>(Numero{token.valor});
        }
        if (token.tipo == TipoToken::fin) {
            throw ErrorExpresion{token.columna,
                                 "la expresión termina antes de tiempo"};
        }
        if (token.tipo != TipoToken::menos &&
            token.tipo != TipoToken::abre) {
            throw ErrorExpresion{token.columna,
                                 "se esperaba un número o '('"};
        }
        if (++profundidad_ > profundidad_maxima) {
            throw ErrorExpresion{token.columna,
                                 "demasiados niveles de anidamiento"};
        }
        avanzar();
        PunteroNodo nodo;
        if (token.tipo == TipoToken::menos) {
            nodo = std::make_unique<Nodo>(Negacion{factor()});
        } else {
            nodo = expresion();
            if (actual().tipo != TipoToken::cierra) {
                throw ErrorExpresion{
                    actual().columna,
                    std::format("falta ')' para cerrar el '(' de la "
                                "columna {}",
                                token.columna)};
            }
            avanzar();
        }
        --profundidad_;
        return nodo;
    }
};

struct Evaluador {
    double operator()(const Numero& numero) const {
        return numero.valor;
    }

    double operator()(const Negacion& negacion) const {
        return -evaluar(*negacion.operando);
    }

    double operator()(const Binaria& binaria) const {
        const double a = evaluar(*binaria.izquierda);
        const double b = evaluar(*binaria.derecha);
        double resultado = 0.0;
        switch (binaria.operador) {
        case '+':
            resultado = a + b;
            break;
        case '-':
            resultado = a - b;
            break;
        case '*':
            resultado = a * b;
            break;
        default:
            if (b == 0.0) {
                throw ErrorExpresion{binaria.columna,
                                     "división entre cero"};
            }
            resultado = a / b;
        }
        if (!std::isfinite(resultado)) {
            throw ErrorExpresion{binaria.columna,
                                 "resultado fuera de rango"};
        }
        return resultado;
    }
};

struct Escritor {
    std::string operator()(const Numero& numero) const {
        return std::format("{}", numero.valor);
    }

    std::string operator()(const Negacion& negacion) const {
        return "(- " + a_texto(*negacion.operando) + ")";
    }

    std::string operator()(const Binaria& binaria) const {
        return std::format("({} {} {})", binaria.operador,
                           a_texto(*binaria.izquierda),
                           a_texto(*binaria.derecha));
    }
};

} // namespace

PunteroNodo analizar(const std::vector<Token>& tokens) {
    return Analizador{tokens}.completo();
}

double evaluar(const Nodo& nodo) {
    return std::visit(Evaluador{}, nodo.contenido);
}

std::string a_texto(const Nodo& nodo) {
    return std::visit(Escritor{}, nodo.contenido);
}
