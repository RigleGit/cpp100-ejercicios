#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Versión 1: una jerarquía de clases.
class Tarifa {
  public:
    virtual ~Tarifa() = default;
    virtual int coste(int kilos) const = 0;
};

class TarifaNormal : public Tarifa {
  public:
    int coste(int kilos) const override {
        return 3 + kilos;
    }
};

class TarifaUrgente : public Tarifa {
  public:
    int coste(int kilos) const override {
        return 2 * (3 + kilos);
    }
};

class TarifaPlana : public Tarifa {
  public:
    explicit TarifaPlana(int precio) : precio_{precio} {}

    int coste(int) const override {
        return precio_;
    }

  private:
    int precio_;
};

std::unique_ptr<Tarifa> tarifa_por_nombre(const std::string& nombre) {
    if (nombre == "normal") {
        return std::make_unique<TarifaNormal>();
    }
    if (nombre == "urgente") {
        return std::make_unique<TarifaUrgente>();
    }
    if (nombre == "plana") {
        return std::make_unique<TarifaPlana>(8);
    }
    return nullptr;
}

// Versión 2: funciones guardadas en std::function.
using Calculo = std::function<int(int)>;

std::map<std::string, Calculo> tabla_de_tarifas() {
    int precio_plano = 8;
    return {
        {"normal", [](int kilos) { return 3 + kilos; }},
        {"urgente", [](int kilos) { return 2 * (3 + kilos); }},
        {"plana", [precio_plano](int) { return precio_plano; }},
    };
}

int main(int argc, char* argv[]) {
    std::string nombre = argc == 2 ? argv[1] : "";
    std::unique_ptr<Tarifa> tarifa = tarifa_por_nombre(nombre);
    std::map<std::string, Calculo> tabla = tabla_de_tarifas();
    auto it = tabla.find(nombre);
    if (tarifa == nullptr || it == tabla.end()) {
        std::cerr << "Error: uso: 079 normal|urgente|plana.\n";
        return 1;
    }
    const Calculo& calculo = it->second;

    std::vector<int> pesos;
    while (std::cin >> std::ws && !std::cin.eof()) {
        int kilos = 0;
        if (!(std::cin >> kilos)) {
            std::cerr << "Error: la entrada solo puede tener enteros.\n";
            return 1;
        }
        if (kilos < 1 || kilos > 30) {
            std::cerr << "Error: cada paquete pesa de 1 a 30 kilos.\n";
            return 1;
        }
        pesos.push_back(kilos);
    }

    int total_clases = 0;
    int total_lambdas = 0;
    for (std::size_t i = 0; i < pesos.size(); ++i) {
        int con_clase = tarifa->coste(pesos[i]);
        total_clases += con_clase;
        total_lambdas += calculo(pesos[i]);
        std::cout << "Paquete " << i + 1 << " (" << pesos[i]
                  << " kg): " << con_clase << " euros\n";
    }
    std::cout << "Total con clases: " << total_clases << " euros\n";
    std::cout << "Total con lambdas: " << total_lambdas << " euros\n";
}
