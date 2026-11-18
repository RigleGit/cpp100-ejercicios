#include <iostream>
#include <sstream>
#include <string>

template <typename T> T maximo(const T& a, const T& b) {
    return (a < b) ? b : a;
}

template <typename T>
bool responder(std::istringstream& linea, const std::string& tipo) {
    T a{};
    T b{};
    std::string sobra;
    if (!(linea >> a >> b) || linea >> sobra) {
        return false;
    }
    std::cout << tipo << ": " << maximo(a, b) << '\n';
    return true;
}

int main() {
    std::string texto;
    int numero = 0;
    while (std::getline(std::cin, texto)) {
        ++numero;
        std::istringstream linea{texto};
        std::string tipo;
        if (!(linea >> tipo)) {
            continue;
        }
        bool correcta = false;
        if (tipo == "entero") {
            correcta = responder<long long>(linea, tipo);
        } else if (tipo == "decimal") {
            correcta = responder<double>(linea, tipo);
        } else if (tipo == "texto") {
            correcta = responder<std::string>(linea, tipo);
        }
        if (!correcta) {
            std::cerr << "Error: la línea " << numero
                      << " no tiene la forma TIPO A B.\n";
            return 1;
        }
    }
}
