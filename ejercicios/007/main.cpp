#include <format>
#include <iostream>

constexpr int porcentaje_iva{21};
constexpr double tipo_iva{porcentaje_iva / 100.0};

int main() {
    double base{};
    std::cin >> base;
    const double iva{base * tipo_iva};
    const double total{base + iva};
    std::cout << std::format("Base: {:.2f} €\n", base);
    std::cout << std::format("IVA ({} %): {:.2f} €\n", porcentaje_iva, iva);
    std::cout << std::format("Total: {:.2f} €\n", total);
}
