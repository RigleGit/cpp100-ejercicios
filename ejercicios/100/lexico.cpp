#include "lexico.hpp"

#include <charconv>
#include <system_error>

ErrorExpresion::ErrorExpresion(std::size_t columna,
                               const std::string& mensaje)
    : std::runtime_error{mensaje}, columna_{columna} {}

std::size_t ErrorExpresion::columna() const {
    return columna_;
}

namespace {

bool es_cifra(char c) {
    return c >= '0' && c <= '9';
}

TipoToken simbolo(char c) {
    switch (c) {
    case '+':
        return TipoToken::mas;
    case '-':
        return TipoToken::menos;
    case '*':
        return TipoToken::por;
    case '/':
        return TipoToken::entre;
    case '(':
        return TipoToken::abre;
    case ')':
        return TipoToken::cierra;
    default:
        return TipoToken::fin;
    }
}

} // namespace

std::vector<Token> tokenizar(std::string_view texto) {
    std::vector<Token> tokens;
    std::size_t i = 0;
    while (i < texto.size()) {
        const char c = texto[i];
        const std::size_t columna = i + 1;
        if (c == ' ' || c == '\t') {
            ++i;
        } else if (es_cifra(c)) {
            const std::size_t inicio = i;
            while (i < texto.size() && es_cifra(texto[i])) {
                ++i;
            }
            if (i < texto.size() && texto[i] == '.') {
                ++i;
                if (i == texto.size() || !es_cifra(texto[i])) {
                    throw ErrorExpresion{i + 1, "falta la parte decimal"};
                }
                while (i < texto.size() && es_cifra(texto[i])) {
                    ++i;
                }
            }
            double valor = 0.0;
            const char* fin = texto.data() + i;
            auto [resto, error] =
                std::from_chars(texto.data() + inicio, fin, valor);
            if (error != std::errc{} || resto != fin) {
                throw ErrorExpresion{columna, "número fuera de rango"};
            }
            tokens.push_back({TipoToken::numero, valor, columna});
        } else if (simbolo(c) != TipoToken::fin) {
            tokens.push_back({simbolo(c), 0.0, columna});
            ++i;
        } else if (c > ' ' && c < 127) {
            throw ErrorExpresion{columna, "carácter inesperado '" +
                                              std::string(1, c) + "'"};
        } else {
            throw ErrorExpresion{columna, "carácter no admitido"};
        }
    }
    tokens.push_back({TipoToken::fin, 0.0, texto.size() + 1});
    return tokens;
}
