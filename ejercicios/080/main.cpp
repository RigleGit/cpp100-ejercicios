#include <cmath>
#include <format>
#include <iostream>
#include <numbers>
#include <optional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

struct Circulo {
    double radio;
};

struct Rectangulo {
    double ancho;
    double alto;
};

struct Triangulo {
    double a;
    double b;
    double c;
};

using Figura = std::variant<Circulo, Rectangulo, Triangulo>;

struct Area {
    double operator()(const Circulo& f) const {
        return std::numbers::pi * f.radio * f.radio;
    }

    double operator()(const Rectangulo& f) const {
        return f.ancho * f.alto;
    }

    double operator()(const Triangulo& f) const {
        double s = (f.a + f.b + f.c) / 2; // fórmula de Herón
        return std::sqrt(s * (s - f.a) * (s - f.b) * (s - f.c));
    }
};

struct Perimetro {
    double operator()(const Circulo& f) const {
        return 2 * std::numbers::pi * f.radio;
    }

    double operator()(const Rectangulo& f) const {
        return 2 * (f.ancho + f.alto);
    }

    double operator()(const Triangulo& f) const {
        return f.a + f.b + f.c;
    }
};

struct Nombre {
    std::string operator()(const Circulo&) const {
        return "círculo";
    }

    std::string operator()(const Rectangulo&) const {
        return "rectángulo";
    }

    std::string operator()(const Triangulo&) const {
        return "triángulo";
    }
};

std::optional<Figura> leer(const std::string& linea) {
    std::istringstream entrada{linea};
    std::string tipo;
    double a = 0;
    double b = 0;
    double c = 0;
    std::string sobra;
    entrada >> tipo;
    if (tipo == "circulo" && entrada >> a && !(entrada >> sobra) && a > 0) {
        return Circulo{a};
    }
    if (tipo == "rectangulo" && entrada >> a >> b && !(entrada >> sobra) &&
        a > 0 && b > 0) {
        return Rectangulo{a, b};
    }
    if (tipo == "triangulo" && entrada >> a >> b >> c &&
        !(entrada >> sobra) && a > 0 && b > 0 && c > 0 && a + b > c &&
        a + c > b && b + c > a) {
        return Triangulo{a, b, c};
    }
    return std::nullopt;
}

int main() {
    std::vector<Figura> figuras;
    std::string linea;
    bool fallos = false;
    while (std::getline(std::cin, linea)) {
        if (std::optional<Figura> f = leer(linea)) {
            figuras.push_back(*f);
        } else {
            std::cerr << "Línea no válida: " << linea << '\n';
            fallos = true;
        }
    }

    for (const Figura& f : figuras) {
        std::cout << std::format(
            "{}: área {:.2f}, perímetro {:.2f}\n", std::visit(Nombre{}, f),
            std::visit(Area{}, f), std::visit(Perimetro{}, f));
    }
    return fallos ? 1 : 0;
}
