#include <iostream>
#include <memory>
#include <string>

struct Nodo {
    explicit Nodo(const std::string& n) : nombre{n} {
        std::cout << "Construye " << nombre << '\n';
    }

    ~Nodo() {
        std::cout << "Destruye " << nombre << '\n';
    }

    std::string nombre;
    std::shared_ptr<Nodo> siguiente;
    std::shared_ptr<Nodo> anterior_fuerte;
    std::weak_ptr<Nodo> anterior;
};

int main(int argc, char* argv[]) {
    std::string modo;
    if (argc == 2) {
        modo = argv[1];
    }
    if (modo != "debil" && modo != "fuerte") {
        std::cerr << "Error: uso: 065 debil|fuerte.\n";
        return 1;
    }

    std::weak_ptr<Nodo> testigo;
    {
        auto a = std::make_shared<Nodo>("A");
        auto b = std::make_shared<Nodo>("B");
        testigo = a;

        a->siguiente = b;
        if (modo == "debil") {
            b->anterior = a;
        } else {
            b->anterior_fuerte = a;
        }
        std::cout << "Dueños de A: " << a.use_count()
                  << ", dueños de B: " << b.use_count() << '\n';

        if (std::shared_ptr<Nodo> previo = b->anterior.lock()) {
            std::cout << "B llega a " << previo->nombre
                      << " a través del weak_ptr\n";
        }
        std::cout << "Fin del bloque\n";
    }
    std::cout << "A liberado: " << (testigo.expired() ? "sí" : "no")
              << '\n';
}
