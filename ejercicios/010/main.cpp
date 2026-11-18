#include <iostream>

int main() {
    int a{};
    char operador{};
    int b{};
    std::cin >> a >> operador >> b;

    int resultado{};
    switch (operador) {
    case '+':
        resultado = a + b;
        break;
    case '-':
        resultado = a - b;
        break;
    case '*':
        resultado = a * b;
        break;
    case '/':
    case '%':
        if (b == 0) {
            std::cerr << "Error: división por cero.\n";
            return 1;
        }
        if (operador == '/') {
            resultado = a / b;
        } else {
            resultado = a % b;
        }
        break;
    default:
        std::cerr << "Error: operador desconocido '" << operador << "'.\n";
        return 1;
    }

    std::cout << a << ' ' << operador << ' ' << b << " = " << resultado
              << '\n';
}
