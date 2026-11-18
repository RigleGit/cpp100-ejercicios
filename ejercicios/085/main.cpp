#include <cstddef>
#include <iostream>
#include <string>

template <typename... Valores>
constexpr auto sumar(const Valores&... valores) {
    return (0 + ... + valores);
}

template <typename... Valores>
bool todos_positivos(const Valores&... valores) {
    return ((valores > 0) && ...);
}

template <typename Primero, typename... Resto>
void escribir(const Primero& primero, const Resto&... resto) {
    std::cout << primero;
    ((std::cout << " | " << resto), ...);
    std::cout << '\n';
}

template <typename... Valores>
constexpr std::size_t contar(const Valores&...) {
    return sizeof...(Valores);
}

std::string si_no(bool valor) {
    return valor ? "sí" : "no";
}

int main() {
    std::cout << "sumar() = " << sumar() << '\n';
    std::cout << "sumar(1, 2, 3) = " << sumar(1, 2, 3) << '\n';
    std::cout << "sumar(1.5, 2, 3) = " << sumar(1.5, 2, 3) << '\n';
    std::cout << "todos_positivos(4, 7, 1) = "
              << si_no(todos_positivos(4, 7, 1)) << '\n';
    std::cout << "todos_positivos(4, -7, 1) = "
              << si_no(todos_positivos(4, -7, 1)) << '\n';
    std::cout << "todos_positivos() = " << si_no(todos_positivos()) << '\n';
    std::cout << "contar(1, \"dos\", 3.5, 'c') = "
              << contar(1, "dos", 3.5, 'c') << '\n';
    escribir(1, "dos", 3.5, 'c');
    escribir("solo");

    static_assert(contar() == 0);
    static_assert(sumar(1, 2, 3) == 6);
}
