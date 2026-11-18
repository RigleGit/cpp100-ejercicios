#include <format>
#include <iostream>
#include <memory>
#include <numbers>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Figura {
  public:
    virtual ~Figura() {
        std::cout << "  ~Figura\n";
    }

    virtual std::string describir() const = 0;
    virtual double area() const = 0;
};

class Circulo : public Figura {
  public:
    explicit Circulo(double radio) : radio_{radio} {}

    ~Circulo() override {
        std::cout << "~Circulo " << radio_ << '\n';
    }

    std::string describir() const override {
        return std::format("círculo de radio {}", radio_);
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

    ~Rectangulo() override {
        std::cout << "~Rectangulo " << ancho_ << 'x' << alto_ << '\n';
    }

    std::string describir() const override {
        return std::format("rectángulo de {}x{}", ancho_, alto_);
    }

    double area() const override {
        return ancho_ * alto_;
    }

  private:
    double ancho_;
    double alto_;
};

// Devuelve nullptr si la línea no describe una figura válida.
std::unique_ptr<Figura> crear(const std::string& linea) {
    std::istringstream entrada{linea};
    std::string tipo;
    double a = 0;
    double b = 0;
    std::string sobra;
    entrada >> tipo;
    if (tipo == "circulo" && entrada >> a && !(entrada >> sobra) && a > 0) {
        return std::make_unique<Circulo>(a);
    }
    if (tipo == "rectangulo" && entrada >> a >> b && !(entrada >> sobra) &&
        a > 0 && b > 0) {
        return std::make_unique<Rectangulo>(a, b);
    }
    return nullptr;
}

int main() {
    std::vector<std::unique_ptr<Figura>> figuras;
    std::string linea;
    bool fallos = false;
    while (std::getline(std::cin, linea)) {
        if (std::unique_ptr<Figura> f = crear(linea)) {
            figuras.push_back(std::move(f));
        } else {
            std::cerr << "Línea no válida: " << linea << '\n';
            fallos = true;
        }
    }

    double total = 0;
    for (const auto& f : figuras) {
        std::cout << std::format("{}: área {:.2f}\n", f->describir(),
                                 f->area());
        total += f->area();
    }
    std::cout << std::format("Área total: {:.2f}\n", total);

    // El orden en que vector destruye sus elementos no está fijado:
    // los liberamos nosotros del último al primero.
    while (!figuras.empty()) {
        figuras.pop_back();
    }
    std::cout << "Fin\n";
    return fallos ? 1 : 0;
}
