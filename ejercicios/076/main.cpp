#include <format>
#include <iostream>
#include <numbers>
#include <string>

class Figura {
  public:
    virtual ~Figura() = default;

    virtual std::string nombre() const {
        return "figura";
    }

    virtual double area() const {
        return 0.0;
    }
};

class Circulo : public Figura {
  public:
    explicit Circulo(double radio) : radio_{radio} {}

    std::string nombre() const override {
        return "círculo";
    }

    double area() const override {
        return std::numbers::pi * radio_ * radio_;
    }

  private:
    double radio_;
};

class Rectangulo : public Figura {
  public:
    Rectangulo(double ancho, double alto) : ancho_{ancho}, alto_{alto} {}

    std::string nombre() const override {
        return "rectángulo";
    }

    double area() const override {
        return ancho_ * alto_;
    }

  private:
    double ancho_;
    double alto_;
};

class Triangulo : public Figura {
  public:
    Triangulo(double base, double altura) : base_{base}, altura_{altura} {}

    std::string nombre() const override {
        return "triángulo";
    }

    double area() const override {
        return base_ * altura_ / 2;
    }

  private:
    double base_;
    double altura_;
};

void informar(const Figura& f) {
    std::cout << std::format("{}: área {:.2f}\n", f.nombre(), f.area());
}

void informar_copia(Figura f) {
    std::cout << std::format("copia de {}: área {:.2f}\n", f.nombre(),
                             f.area());
}

int main() {
    Circulo circulo{1};
    Rectangulo rectangulo{2, 3};
    Triangulo triangulo{4, 3};

    const Figura* figuras[] = {&circulo, &rectangulo, &triangulo};
    double total = 0;
    for (const Figura* f : figuras) {
        informar(*f);
        total += f->area();
    }
    std::cout << std::format("Área total: {:.2f}\n", total);

    informar_copia(circulo);
}
