#include <format>
#include <iostream>
#include <string>

std::string formatear_precio(double cantidad, int decimales = 2,
                             std::string moneda = "€");

int main() {
    double cantidad{};
    if (!(std::cin >> cantidad)) {
        std::cerr << "Error: se esperaba una cantidad.\n";
        return 1;
    }
    std::cout << formatear_precio(cantidad) << '\n';
    std::cout << formatear_precio(cantidad, 0) << '\n';
    std::cout << formatear_precio(cantidad, 3, "USD") << '\n';
}

std::string formatear_precio(double cantidad, int decimales,
                             std::string moneda) {
    return std::format("{:.{}f} {}", cantidad, decimales, moneda);
}
