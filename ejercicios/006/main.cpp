#include <format>
#include <iostream>

int main() {
    int a{};
    int b{};
    int c{};
    std::cin >> a >> b >> c;
    int suma{a + b + c};
    int division_entera{suma / 3};
    double media{static_cast<double>(suma) / 3};
    std::cout << "Suma: " << suma << '\n';
    std::cout << "División entera: " << division_entera << '\n';
    std::cout << std::format("Media: {:.2f}\n", media);
}
