#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

constexpr int saldo_maximo = 1000;

// Devuelve un saldo a su valor anterior si nadie confirma la operación.
class Deshacer {
  public:
    explicit Deshacer(int& saldo) : saldo_{saldo}, anterior_{saldo} {}

    ~Deshacer() {
        if (!confirmado_) {
            saldo_ = anterior_;
        }
    }

    Deshacer(const Deshacer&) = delete;
    Deshacer& operator=(const Deshacer&) = delete;

    void confirmar() {
        confirmado_ = true;
    }

  private:
    int& saldo_;
    int anterior_;
    bool confirmado_ = false;
};

class Banco {
  public:
    void abrir(const std::string& titular, int saldo) {
        cuentas_[titular] = saldo;
    }

    void transferir(const std::string& origen, const std::string& destino,
                    int cantidad) {
        if (cantidad <= 0) {
            throw std::invalid_argument{"la cantidad debe ser positiva"};
        }
        if (origen == destino) {
            throw std::invalid_argument{"origen y destino coinciden"};
        }
        int& saldo_origen = cuenta(origen);
        int& saldo_destino = cuenta(destino);

        Deshacer guardia{saldo_origen};
        retirar(saldo_origen, cantidad);
        ingresar(saldo_destino, cantidad);
        guardia.confirmar();
    }

    void mostrar() const {
        std::cout << "Saldos:";
        for (const auto& [titular, saldo] : cuentas_) {
            std::cout << ' ' << titular << '=' << saldo;
        }
        std::cout << '\n';
    }

  private:
    int& cuenta(const std::string& titular) {
        auto it = cuentas_.find(titular);
        if (it == cuentas_.end()) {
            throw std::invalid_argument{"no existe la cuenta " + titular};
        }
        return it->second;
    }

    static void retirar(int& saldo, int cantidad) {
        if (saldo < cantidad) {
            throw std::runtime_error{"saldo insuficiente"};
        }
        saldo -= cantidad;
    }

    static void ingresar(int& saldo, int cantidad) {
        if (saldo > saldo_maximo - cantidad) {
            throw std::runtime_error{"el destino superaría el máximo"};
        }
        saldo += cantidad;
    }

    std::map<std::string, int> cuentas_;
};

int main() {
    Banco banco;
    banco.abrir("ana", 100);
    banco.abrir("eva", 0);
    banco.abrir("luis", 950);

    std::string linea;
    bool fallos = false;
    while (std::getline(std::cin, linea)) {
        std::istringstream entrada{linea};
        std::string origen;
        std::string destino;
        int cantidad = 0;
        std::string sobra;
        if (!(entrada >> origen >> destino >> cantidad) ||
            entrada >> sobra) {
            std::cerr << linea << ": formato ORIGEN DESTINO CANTIDAD\n";
            fallos = true;
            continue;
        }
        try {
            banco.transferir(origen, destino, cantidad);
            std::cout << origen << " -> " << destino << ": " << cantidad
                      << '\n';
        } catch (const std::exception& e) {
            std::cerr << linea << ": " << e.what() << '\n';
            fallos = true;
        }
    }
    banco.mostrar();
    return fallos ? 1 : 0;
}
