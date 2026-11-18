#include <iostream>
#include <sstream>
#include <string>
#include <variant>

struct Error {
    std::string mensaje;
};

using Resultado = std::variant<long long, Error>;

constexpr long long limite = 1'000'000;

Resultado calcular(long long a, char op, long long b) {
    if (a < -limite || a > limite || b < -limite || b > limite) {
        return Error{"operandos fuera de -1000000..1000000"};
    }
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0) {
            return Error{"división por cero"};
        }
        return a / b;
    default:
        return Error{std::string{"operador desconocido "} + op};
    }
}

Resultado interpretar(const std::string& linea) {
    std::istringstream entrada{linea};
    long long a = 0;
    long long b = 0;
    char op = ' ';
    std::string sobra;
    if (!(entrada >> a >> op >> b) || entrada >> sobra) {
        return Error{"formato A OP B"};
    }
    return calcular(a, op, b);
}

struct Mostrar {
    const std::string& linea;

    void operator()(long long valor) const {
        std::cout << linea << " = " << valor << '\n';
    }

    void operator()(const Error& error) const {
        std::cerr << linea << ": " << error.mensaje << '\n';
    }
};

int main() {
    std::string linea;
    int errores = 0;
    while (std::getline(std::cin, linea)) {
        Resultado r = interpretar(linea);
        std::visit(Mostrar{linea}, r);
        if (std::holds_alternative<Error>(r)) {
            ++errores;
        }
    }
    return errores == 0 ? 0 : 1;
}
