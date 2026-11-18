#include <format>
#include <iostream>
#include <numbers>

int main() {
    double radio{};
    std::cin >> radio;
    double area{std::numbers::pi * radio * radio};
    double perimetro{2 * std::numbers::pi * radio};
    std::cout << std::format("Área: {:.2f}\n", area);
    std::cout << std::format("Perímetro: {:.2f}\n", perimetro);
}
