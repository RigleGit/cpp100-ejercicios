#include <iostream>
#include <memory>
#include <utility>

struct Nodo {
    int valor;
    std::unique_ptr<Nodo> siguiente;
};

class Lista {
  public:
    ~Lista() {
        // Suelta los nodos de uno en uno para no encadenar destructores.
        while (cabeza_ != nullptr) {
            cabeza_ = std::move(cabeza_->siguiente);
        }
    }

    void insertar_delante(int valor) {
        cabeza_ = std::make_unique<Nodo>(valor, std::move(cabeza_));
        ++tamano_;
    }

    void invertir() {
        std::unique_ptr<Nodo> invertida;
        while (cabeza_ != nullptr) {
            std::unique_ptr<Nodo> resto = std::move(cabeza_->siguiente);
            cabeza_->siguiente = std::move(invertida);
            invertida = std::move(cabeza_);
            cabeza_ = std::move(resto);
        }
        cabeza_ = std::move(invertida);
    }

    void mostrar(std::ostream& salida) const {
        if (cabeza_ == nullptr) {
            salida << "(vacía)";
        }
        for (const Nodo* n = cabeza_.get(); n != nullptr;
             n = n->siguiente.get()) {
            salida << n->valor;
            if (n->siguiente != nullptr) {
                salida << " -> ";
            }
        }
        salida << '\n';
    }

    int tamano() const {
        return tamano_;
    }

  private:
    std::unique_ptr<Nodo> cabeza_;
    int tamano_ = 0;
};

int main() {
    Lista lista;
    while (std::cin >> std::ws && !std::cin.eof()) {
        int valor = 0;
        if (!(std::cin >> valor)) {
            std::cerr << "Error: la entrada solo puede tener enteros.\n";
            return 1;
        }
        lista.insertar_delante(valor);
    }

    std::cout << "Nodos: " << lista.tamano() << '\n';
    std::cout << "Lista: ";
    lista.mostrar(std::cout);
    lista.invertir();
    std::cout << "Invertida: ";
    lista.mostrar(std::cout);
}
