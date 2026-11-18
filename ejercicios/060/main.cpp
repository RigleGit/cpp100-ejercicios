#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Movimiento {
    std::string tipo;
    long long importe{};
    long long saldo{};
};

class Cuenta {
  public:
    explicit Cuenta(const std::string& titular) : titular_{titular} {}

    bool ingresar(long long importe) {
        if (importe <= 0) {
            return false;
        }
        saldo_ += importe;
        movimientos_.push_back({"ingreso", importe, saldo_});
        return true;
    }

    bool retirar(long long importe) {
        if (importe <= 0 || importe > saldo_) {
            return false;
        }
        saldo_ -= importe;
        movimientos_.push_back({"retirada", importe, saldo_});
        return true;
    }

    const std::string& titular() const {
        return titular_;
    }

    long long saldo() const {
        return saldo_;
    }

    const std::vector<Movimiento>& movimientos() const {
        return movimientos_;
    }

  private:
    std::string titular_;
    long long saldo_ = 0;
    std::vector<Movimiento> movimientos_;
};

int main() {
    std::string titular;
    if (!std::getline(std::cin, titular) || titular.empty()) {
        std::cerr << "Error: la primera línea debe llevar el titular.\n";
        return 1;
    }
    Cuenta cuenta(titular);
    std::cout << "Titular: " << cuenta.titular() << '\n';

    std::string texto;
    int numero_linea = 1;
    while (std::getline(std::cin, texto)) {
        ++numero_linea;
        std::istringstream linea(texto);
        std::string orden;
        long long importe = 0;
        std::string sobra;
        if (!(linea >> orden >> importe) || (linea >> sobra) ||
            (orden != "ingresar" && orden != "retirar") || importe < 1 ||
            importe > 1000000) {
            std::cerr << "Error en la línea " << numero_linea
                      << ": usa «ingresar N» o «retirar N» con N de 1 a "
                         "1000000.\n";
            return 1;
        }
        bool hecho = orden == "ingresar" ? cuenta.ingresar(importe)
                                         : cuenta.retirar(importe);
        if (!hecho) {
            std::cout << "Rechazado: " << orden << ' ' << importe
                      << " (saldo " << cuenta.saldo() << ")\n";
        }
    }

    std::cout << "Movimientos: " << cuenta.movimientos().size() << '\n';
    for (const Movimiento& m : cuenta.movimientos()) {
        std::cout << "  " << m.tipo << ' ' << m.importe << " -> saldo "
                  << m.saldo << '\n';
    }
    std::cout << "Saldo final: " << cuenta.saldo() << '\n';
}
