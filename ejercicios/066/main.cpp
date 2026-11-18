#include <algorithm>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

class Bufer {
  public:
    explicit Bufer(std::size_t n) : n_{n}, datos_{new int[n]{}} {}

    ~Bufer() {
        delete[] datos_;
    }

    // Copia profunda: memoria nueva con los mismos valores.
    Bufer(const Bufer& otro) : n_{otro.n_}, datos_{new int[otro.n_]} {
        std::copy(otro.datos_, otro.datos_ + n_, datos_);
    }

    Bufer& operator=(const Bufer& otro) {
        if (this != &otro) {
            int* nuevos = new int[otro.n_];
            std::copy(otro.datos_, otro.datos_ + otro.n_, nuevos);
            delete[] datos_;
            datos_ = nuevos;
            n_ = otro.n_;
        }
        return *this;
    }

    // Movimiento: se lleva la memoria y deja el origen vacío.
    Bufer(Bufer&& otro) noexcept
        : n_{std::exchange(otro.n_, 0)},
          datos_{std::exchange(otro.datos_, nullptr)} {}

    Bufer& operator=(Bufer&& otro) noexcept {
        if (this != &otro) {
            delete[] datos_;
            n_ = std::exchange(otro.n_, 0);
            datos_ = std::exchange(otro.datos_, nullptr);
        }
        return *this;
    }

    std::size_t size() const {
        return n_;
    }

    int& operator[](std::size_t i) {
        return datos_[i];
    }

    int operator[](std::size_t i) const {
        return datos_[i];
    }

  private:
    std::size_t n_;
    int* datos_;
};

void mostrar(const std::string& titulo, const Bufer& b) {
    std::cout << titulo << ": [";
    for (std::size_t i = 0; i < b.size(); ++i) {
        std::cout << (i > 0 ? ", " : "") << b[i];
    }
    std::cout << "]\n";
}

int main(int argc, char* argv[]) {
    std::size_t n = 0;
    std::string texto;
    if (argc == 2) {
        texto = argv[1];
    }
    auto [fin, error] =
        std::from_chars(texto.data(), texto.data() + texto.size(), n);
    if (argc != 2 || texto.empty() || error != std::errc{} ||
        fin != texto.data() + texto.size() || n > 1000) {
        std::cerr << "Error: uso: 066 N, con N entre 0 y 1000.\n";
        return 1;
    }

    Bufer original{n};
    for (std::size_t i = 0; i < n; ++i) {
        original[i] = static_cast<int>(i + 1);
    }
    mostrar("Original", original);

    Bufer copia = original;
    if (copia.size() > 0) {
        copia[0] = 99;
    }
    mostrar("Copia cambiada", copia);
    mostrar("Original intacto", original);

    Bufer asignada{1};
    asignada = original;
    mostrar("Asignada", asignada);

    Bufer& alias = asignada;
    asignada = alias;
    mostrar("Tras asignarse a sí misma", asignada);

    Bufer movida = std::move(copia);
    mostrar("Movida", movida);
    movida = std::move(asignada);
    mostrar("Movida otra vez", movida);
}
