#include <array>
#include <cstddef>
#include <iostream>
#include <span>

int sumar(std::span<const int> tramo) {
    int total = 0;
    for (int venta : tramo) {
        total += venta;
    }
    return total;
}

bool tramoValido(int inicio, int cantidad, std::size_t total) {
    if (inicio < 0 || cantidad < 0) {
        return false;
    }
    const auto desde = static_cast<std::size_t>(inicio);
    const auto cuantos = static_cast<std::size_t>(cantidad);
    return desde <= total && cuantos <= total - desde;
}

int main() {
    const std::array<int, 7> ventas{120, 95, 130, 80, 150, 210, 175};
    int inicio{};
    int cantidad{};
    if (!(std::cin >> inicio >> cantidad)) {
        std::cerr << "Error: se esperaban dos enteros.\n";
        return 1;
    }
    if (!tramoValido(inicio, cantidad, ventas.size())) {
        std::cerr << "Error: el tramo se sale de la semana.\n";
        return 1;
    }

    std::span<const int> semana{ventas};
    std::span<const int> tramo =
        semana.subspan(static_cast<std::size_t>(inicio),
                       static_cast<std::size_t>(cantidad));

    std::cout << "Total de la semana: " << sumar(semana) << '\n';
    std::cout << "Tramo:";
    for (int venta : tramo) {
        std::cout << ' ' << venta;
    }
    std::cout << "\nSuma del tramo: " << sumar(tramo) << '\n';
}
