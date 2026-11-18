#include <iostream>
#include <string>
#include <vector>

class Pedido {
  public:
    explicit Pedido(const std::string& cliente)
        : id_{siguiente_}, cliente_{cliente} {
        ++siguiente_;
    }

    int id() const {
        return id_;
    }

    const std::string& cliente() const {
        return cliente_;
    }

    static int creados() {
        return siguiente_ - 1;
    }

  private:
    inline static int siguiente_ = 1;
    int id_;
    std::string cliente_;
};

int main() {
    std::vector<Pedido> pedidos;
    std::string cliente;
    while (std::cin >> cliente) {
        pedidos.push_back(Pedido(cliente));
    }

    for (const Pedido& pedido : pedidos) {
        std::cout << "Pedido " << pedido.id() << ": " << pedido.cliente()
                  << '\n';
    }
    std::cout << "Pedidos creados: " << Pedido::creados() << '\n';
}
