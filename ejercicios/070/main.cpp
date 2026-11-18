#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

class ErrorPedido : public std::runtime_error {
  public:
    explicit ErrorPedido(const std::string& mensaje)
        : std::runtime_error{mensaje} {}
};

class FormatoInvalido : public ErrorPedido {
  public:
    FormatoInvalido()
        : ErrorPedido{"escribe un código y una cantidad positiva"} {}
};

class ProductoDesconocido : public ErrorPedido {
  public:
    explicit ProductoDesconocido(const std::string& codigo)
        : ErrorPedido{"no existe el producto " + codigo} {}
};

class SinExistencias : public ErrorPedido {
  public:
    SinExistencias(const std::string& codigo, int disponibles)
        : ErrorPedido{"no hay bastante " + codigo},
          disponibles_{disponibles} {}

    int disponibles() const {
        return disponibles_;
    }

  private:
    int disponibles_;
};

int servir(std::map<std::string, int>& almacen, const std::string& linea) {
    std::istringstream entrada{linea};
    std::string codigo;
    int cantidad = 0;
    std::string sobra;
    if (!(entrada >> codigo >> cantidad) || cantidad <= 0 ||
        entrada >> sobra) {
        throw FormatoInvalido{};
    }
    auto it = almacen.find(codigo);
    if (it == almacen.end()) {
        throw ProductoDesconocido{codigo};
    }
    if (it->second < cantidad) {
        throw SinExistencias{codigo, it->second};
    }
    it->second -= cantidad;
    return it->second;
}

int main() {
    std::map<std::string, int> almacen{
        {"tornillo", 10}, {"tuerca", 5}, {"arandela", 0}};

    std::string linea;
    int numero = 0;
    int servidos = 0;
    while (std::getline(std::cin, linea)) {
        ++numero;
        try {
            int quedan = servir(almacen, linea);
            std::cout << "Pedido " << numero << ": servido, quedan "
                      << quedan << '\n';
            ++servidos;
        } catch (const SinExistencias& e) {
            std::cerr << "Pedido " << numero << ": " << e.what()
                      << " (quedan " << e.disponibles() << ")\n";
        } catch (const ErrorPedido& e) {
            std::cerr << "Pedido " << numero << ": " << e.what() << '\n';
        }
    }
    std::cout << "Servidos: " << servidos << " de " << numero << '\n';
    return servidos == numero ? 0 : 1;
}
