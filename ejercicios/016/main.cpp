#include <format>
#include <iostream>
#include <numbers>
#include <string>

struct Circulo {
    double radio;
};

double area(double lado) {
    return lado * lado;
}

double area(double base, double altura) {
    return base * altura;
}

double area(Circulo circulo) {
    return std::numbers::pi * circulo.radio * circulo.radio;
}

int main() {
    std::string figura;
    double primera{};
    double segunda{};
    if (!(std::cin >> figura >> primera)) {
        std::cerr << "Error: faltan la figura o sus medidas.\n";
        return 1;
    }
    if (figura == "rectangulo" && !(std::cin >> segunda)) {
        std::cerr << "Error: el rectángulo necesita base y altura.\n";
        return 1;
    }
    if (primera < 0 || segunda < 0) {
        std::cerr << "Error: las medidas no pueden ser negativas.\n";
        return 1;
    }

    double resultado{};
    if (figura == "cuadrado") {
        resultado = area(primera);
    } else if (figura == "rectangulo") {
        resultado = area(primera, segunda);
    } else if (figura == "circulo") {
        resultado = area(Circulo{primera});
    } else {
        std::cerr << "Error: figura desconocida '" << figura << "'.\n";
        return 1;
    }
    std::cout << std::format("Área: {:.2f}\n", resultado);
}
