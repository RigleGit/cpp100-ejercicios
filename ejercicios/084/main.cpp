#include <concepts>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
concept Imprimible = requires(std::ostream& salida, const T& valor) {
    { salida << valor } -> std::same_as<std::ostream&>;
};

struct Punto {
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& salida, const Punto& p) {
    return salida << '(' << p.x << ", " << p.y << ')';
}

struct Lugar {
    std::string nombre;
    Punto posicion;
};

static_assert(Imprimible<int>);
static_assert(Imprimible<std::string>);
static_assert(Imprimible<Punto>);
static_assert(!Imprimible<Lugar>);
static_assert(!Imprimible<std::vector<int>>);

template <Imprimible T>
void mostrar(const std::string& titulo, const std::vector<T>& valores) {
    std::cout << titulo << ": [";
    for (std::size_t i = 0; i < valores.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << valores[i];
    }
    std::cout << "]\n";
}

int main() {
    std::vector<Lugar> lugares;
    std::string texto;
    int numero = 0;
    while (std::getline(std::cin, texto)) {
        ++numero;
        std::istringstream linea{texto};
        Lugar lugar;
        std::string sobra;
        if (!(linea >> lugar.nombre)) {
            continue;
        }
        if (!(linea >> lugar.posicion.x >> lugar.posicion.y) ||
            linea >> sobra) {
            std::cerr << "Error: la línea " << numero
                      << " no tiene la forma NOMBRE X Y.\n";
            return 1;
        }
        lugares.push_back(lugar);
    }
    std::vector<std::string> nombres;
    std::vector<Punto> puntos;
    for (const Lugar& lugar : lugares) {
        nombres.push_back(lugar.nombre);
        puntos.push_back(lugar.posicion);
    }
    mostrar("Nombres", nombres);
    mostrar("Puntos", puntos);
}
