#include <iostream>
#include <string>
#include <utility>

class Recurso {
  public:
    explicit Recurso(std::string datos) : datos_{std::move(datos)} {
        std::cout << "Construye " << datos_ << '\n';
    }

    Recurso(const Recurso& otro) : datos_{otro.datos_} {
        std::cout << "Copia " << datos_ << '\n';
    }

    Recurso(Recurso&& otro) noexcept
        : datos_{std::exchange(otro.datos_, "")} {
        std::cout << "Mueve " << datos_ << '\n';
    }

    Recurso& operator=(const Recurso& otro) {
        std::cout << "Asigna copiando " << otro.datos_ << " sobre "
                  << describir() << '\n';
        datos_ = otro.datos_;
        return *this;
    }

    Recurso& operator=(Recurso&& otro) noexcept {
        std::cout << "Asigna moviendo " << otro.datos_ << " sobre "
                  << describir() << '\n';
        datos_ = std::exchange(otro.datos_, "");
        return *this;
    }

    ~Recurso() {
        std::cout << "Destruye " << describir() << '\n';
    }

    std::string describir() const {
        return datos_.empty() ? "(vacío)" : datos_;
    }

  private:
    std::string datos_;
};

Recurso fabricar(const std::string& datos) {
    return Recurso{datos};
}

void usar(Recurso r) {
    std::cout << "Usa " << r.describir() << '\n';
}

int main() {
    std::cout << "-- copia y movimiento\n";
    Recurso a{"tabla"};
    Recurso b = a;
    Recurso c = std::move(a);
    std::cout << "a queda " << a.describir() << '\n';

    std::cout << "-- devolver un temporal\n";
    Recurso d = fabricar("informe");

    std::cout << "-- asignaciones\n";
    d = std::move(b);
    a = c;

    std::cout << "-- pasar por valor\n";
    usar(std::move(c));
    std::cout << "c queda " << c.describir() << '\n';

    std::cout << "-- mover un objeto const\n";
    const Recurso e{"constante"};
    Recurso f = std::move(e);

    std::cout << "-- fin de main\n";
}
