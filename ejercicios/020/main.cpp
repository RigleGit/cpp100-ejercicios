#include <iostream>

constexpr int limite{1'000'000};

struct DivisionEntera {
    int cociente;
    int resto;
};

DivisionEntera dividir(int dividendo, int divisor) {
    return {dividendo / divisor, dividendo % divisor};
}

int main() {
    int dividendo{};
    int divisor{};
    if (!(std::cin >> dividendo >> divisor)) {
        std::cerr << "Error: se esperaban dos enteros.\n";
        return 1;
    }
    if (dividendo < -limite || dividendo > limite || divisor < -limite ||
        divisor > limite) {
        std::cerr << "Error: los valores deben estar entre -" << limite
                  << " y " << limite << ".\n";
        return 1;
    }
    if (divisor == 0) {
        std::cerr << "Error: el divisor no puede ser 0.\n";
        return 1;
    }

    auto [cociente, resto] = dividir(dividendo, divisor);
    std::cout << "Cociente: " << cociente << '\n';
    std::cout << "Resto: " << resto << '\n';
    std::cout << "Comprobación: " << cociente << " * " << divisor << " + "
              << resto << " = " << cociente * divisor + resto << '\n';
}
