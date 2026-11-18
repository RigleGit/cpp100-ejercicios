#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::string unir(const std::vector<double>& valores) {
    std::string texto;
    for (double valor : valores) {
        texto += std::format(" {:.1f}", valor);
    }
    return texto;
}

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 0 || n > 1000) {
        std::cerr << "Error: escribe cuántas temperaturas hay "
                     "(de 0 a 1000).\n";
        return 1;
    }
    std::vector<double> celsius(n);
    for (double& grados : celsius) {
        if (!(std::cin >> grados) || grados < -273.15 || grados > 1000.0) {
            std::cerr << "Error: faltan temperaturas o hay una no válida "
                         "(de -273.15 a 1000).\n";
            return 1;
        }
    }
    if (celsius.empty()) {
        std::cout << "Sin temperaturas.\n";
        return 0;
    }

    std::vector<double> fahrenheit(celsius.size());
    std::transform(celsius.begin(), celsius.end(), fahrenheit.begin(),
                   [](double c) { return c * 9.0 / 5.0 + 32.0; });

    double sumaC = std::accumulate(celsius.begin(), celsius.end(), 0.0);
    double sumaF =
        std::accumulate(fahrenheit.begin(), fahrenheit.end(), 0.0);
    double cuantas = static_cast<double>(celsius.size());

    std::cout << "Celsius:" << unir(celsius) << '\n';
    std::cout << "Fahrenheit:" << unir(fahrenheit) << '\n';
    std::cout << std::format("Media: {:.1f} °C = {:.1f} °F\n",
                             sumaC / cuantas, sumaF / cuantas);
}
