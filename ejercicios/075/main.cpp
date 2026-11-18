#include <iostream>
#include <string>
#include <utility>

class Empleado {
  public:
    Empleado(std::string nombre, int sueldo_base)
        : nombre_{std::move(nombre)}, sueldo_base_{sueldo_base} {
        std::cout << "Construye Empleado " << nombre_ << '\n';
    }

    const std::string& nombre() const {
        return nombre_;
    }

    int sueldo() const {
        return sueldo_base_;
    }

  protected:
    int sueldo_base() const {
        return sueldo_base_;
    }

  private:
    std::string nombre_;
    int sueldo_base_;
};

class Gerente : public Empleado {
  public:
    Gerente(std::string nombre, int sueldo_base, int personas)
        : Empleado{std::move(nombre), sueldo_base}, personas_{personas} {
        std::cout << "Construye Gerente " << this->nombre() << '\n';
    }

    // Oculta Empleado::sueldo; no lo sustituye.
    int sueldo() const {
        return sueldo_base() + personas_ * plus_por_persona;
    }

    int personas() const {
        return personas_;
    }

  private:
    static constexpr int plus_por_persona = 100;
    int personas_;
};

void informar(const Empleado& e) {
    std::cout << e.nombre() << " como Empleado: " << e.sueldo()
              << " euros\n";
}

int main() {
    Empleado ana{"Ana", 1800};
    Gerente luis{"Luis", 2500, 4};

    std::cout << ana.nombre() << ": " << ana.sueldo() << " euros\n";
    std::cout << luis.nombre() << ": " << luis.sueldo() << " euros ("
              << luis.personas() << " personas a cargo)\n";

    informar(ana);
    informar(luis);
}
