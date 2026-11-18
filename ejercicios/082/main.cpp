#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

template <typename T> class Pila {
  public:
    void apilar(T valor) {
        elementos_.push_back(std::move(valor));
    }

    std::optional<T> desapilar() {
        if (elementos_.empty()) {
            return std::nullopt;
        }
        T cima = std::move(elementos_.back());
        elementos_.pop_back();
        return cima;
    }

    bool vacia() const {
        return elementos_.empty();
    }

    std::size_t tamano() const {
        return elementos_.size();
    }

  private:
    std::vector<T> elementos_;
};

struct Apertura {
    char simbolo;
    std::size_t columna;
};

char pareja(char cierre) {
    switch (cierre) {
    case ')':
        return '(';
    case ']':
        return '[';
    default:
        return '{';
    }
}

std::string revisar(const std::string& linea) {
    Pila<Apertura> abiertos;
    for (std::size_t i = 0; i < linea.size(); ++i) {
        const char c = linea[i];
        const std::size_t columna = i + 1;
        if (c == '(' || c == '[' || c == '{') {
            abiertos.apilar({c, columna});
        } else if (c == ')' || c == ']' || c == '}') {
            const std::optional<Apertura> ultimo = abiertos.desapilar();
            if (!ultimo) {
                return "'" + std::string(1, c) + "' en la columna " +
                       std::to_string(columna) + " no tiene pareja";
            }
            if (ultimo->simbolo != pareja(c)) {
                return "'" + std::string(1, ultimo->simbolo) +
                       "' de la columna " +
                       std::to_string(ultimo->columna) +
                       " se cierra con '" + std::string(1, c) +
                       "' en la columna " + std::to_string(columna);
            }
        }
    }
    if (abiertos.vacia()) {
        return "ok";
    }
    const std::size_t pendientes = abiertos.tamano();
    const Apertura ultimo = *abiertos.desapilar();
    return "falta cerrar '" + std::string(1, ultimo.simbolo) +
           "' de la columna " + std::to_string(ultimo.columna) + " (" +
           std::to_string(pendientes) + " sin cerrar)";
}

int main() {
    std::string linea;
    int numero = 0;
    while (std::getline(std::cin, linea)) {
        ++numero;
        std::cout << numero << ": " << revisar(linea) << '\n';
    }
}
