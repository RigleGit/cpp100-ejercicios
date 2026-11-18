#include <format>
#include <iostream>

class Registro {
  public:
    void anotar(int grados) {
        if (cuenta_ == 0 || grados < minimo_) {
            minimo_ = grados;
        }
        if (cuenta_ == 0 || grados > maximo_) {
            maximo_ = grados;
        }
        suma_ += grados;
        ++cuenta_;
    }

    int cuenta() const {
        return cuenta_;
    }

    int minimo() const {
        return minimo_;
    }

    int maximo() const {
        return maximo_;
    }

    double media() const {
        return static_cast<double>(suma_) / cuenta_;
    }

  private:
    int cuenta_ = 0;
    long long suma_ = 0;
    int minimo_ = 0;
    int maximo_ = 0;
};

void informe(const Registro& registro) {
    if (registro.cuenta() == 0) {
        std::cout << "Sin medidas.\n";
        return;
    }
    std::cout << "Medidas: " << registro.cuenta() << '\n';
    std::cout << "Mínima: " << registro.minimo() << '\n';
    std::cout << "Máxima: " << registro.maximo() << '\n';
    std::cout << std::format("Media: {:.1f}\n", registro.media());
}

int main() {
    Registro registro;
    while (std::cin >> std::ws && !std::cin.eof()) {
        int grados = 0;
        if (!(std::cin >> grados)) {
            std::cerr << "Error: escribe solo temperaturas enteras.\n";
            return 1;
        }
        if (grados < -100 || grados > 100) {
            std::cerr << "Error: temperatura fuera de rango: " << grados
                      << '\n';
            return 1;
        }
        registro.anotar(grados);
    }
    informe(registro);
}
