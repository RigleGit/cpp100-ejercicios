#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Operacion {
    std::string simbolo;
    std::function<int(int, int)> aplicar;
};

int maximo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main() {
    const std::vector<Operacion> tabla{
        {"+", std::plus<int>{}},
        {"-", std::minus<int>{}},
        {"*", std::multiplies<int>{}},
        {"/", [](int a, int b) { return a / b; }},
        {"max", maximo},
    };

    std::string texto;
    int numero_linea = 0;
    while (std::getline(std::cin, texto)) {
        ++numero_linea;
        std::istringstream linea(texto);
        int a = 0;
        int b = 0;
        std::string simbolo;
        std::string sobra;
        if (!(linea >> a >> simbolo >> b) || (linea >> sobra) ||
            a < -10000 || a > 10000 || b < -10000 || b > 10000) {
            std::cerr << "Error en la línea " << numero_linea
                      << ": usa «a operación b» con enteros entre -10000 y "
                         "10000.\n";
            return 1;
        }
        auto it = std::find_if(tabla.begin(), tabla.end(),
                               [&simbolo](const Operacion& op) {
                                   return op.simbolo == simbolo;
                               });
        if (it == tabla.end()) {
            std::cerr << "Error en la línea " << numero_linea
                      << ": operación desconocida: " << simbolo << '\n';
            return 1;
        }
        if (simbolo == "/" && b == 0) {
            std::cerr << "Error en la línea " << numero_linea
                      << ": división entre cero.\n";
            return 1;
        }
        std::cout << a << ' ' << simbolo << ' ' << b << " = "
                  << it->aplicar(a, b) << '\n';
    }
}
