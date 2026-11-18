#include <iostream>

struct Rectangulo {
    int ancho{};
    int alto{};

    int area() {
        return ancho * alto;
    }

    int perimetro() {
        return 2 * (ancho + alto);
    }

    bool es_cuadrado() {
        return ancho == alto;
    }

    void escalar(int factor) {
        ancho *= factor;
        alto *= factor;
    }
};

void describir(Rectangulo& r) {
    std::cout << "Rectángulo " << r.ancho << " x " << r.alto << '\n';
    std::cout << "Área: " << r.area() << '\n';
    std::cout << "Perímetro: " << r.perimetro() << '\n';
    std::cout << "Cuadrado: " << (r.es_cuadrado() ? "sí" : "no") << '\n';
}

int main() {
    Rectangulo r;
    int factor = 0;
    if (!(std::cin >> r.ancho >> r.alto >> factor) || r.ancho < 1 ||
        r.ancho > 1000 || r.alto < 1 || r.alto > 1000 || factor < 1 ||
        factor > 10) {
        std::cerr
            << "Error: escribe ancho y alto (de 1 a 1000) y un factor "
               "(de 1 a 10).\n";
        return 1;
    }
    describir(r);
    r.escalar(factor);
    std::cout << "Escalado por " << factor << ":\n";
    describir(r);
}
