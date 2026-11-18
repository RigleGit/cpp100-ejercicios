#include <charconv>
#include <cmath>
#include <concepts>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

template <typename T>
    requires(std::integral<T> || std::floating_point<T>) &&
            (!std::same_as<T, bool>)
T sumar(const std::vector<T>& valores) {
    T total{};
    for (const T& valor : valores) {
        total += valor;
    }
    return total;
}

template <typename T>
    requires(std::integral<T> || std::floating_point<T>) &&
            (!std::same_as<T, bool>)
double media(const std::vector<T>& valores) {
    return static_cast<double>(sumar(valores)) /
           static_cast<double>(valores.size());
}

template <typename T>
    requires std::integral<T> || std::floating_point<T>
bool convertir(const std::string& texto, T& valor) {
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, valor);
    if (error != std::errc{} || resto != fin) {
        return false;
    }
    return std::isfinite(static_cast<double>(valor));
}

template <typename T> int procesar() {
    std::vector<T> valores;
    std::string palabra;
    while (std::cin >> palabra) {
        T valor{};
        if (!convertir(palabra, valor)) {
            std::cerr << "Error: '" << palabra
                      << "' no es un número válido.\n";
            return 1;
        }
        valores.push_back(valor);
    }
    std::cout << "Cantidad: " << valores.size() << '\n';
    std::cout << "Suma: " << sumar(valores) << '\n';
    if (valores.empty()) {
        std::cout << "Media: no definida\n";
    } else {
        std::cout << "Media: " << media(valores) << '\n';
    }
    return 0;
}

int main(int argc, char* argv[]) {
    const std::string modo = argc == 2 ? argv[1] : "";
    if (modo == "enteros") {
        return procesar<long long>();
    }
    if (modo == "decimales") {
        return procesar<double>();
    }
    std::cerr << "Uso: 083 enteros|decimales\n";
    return 1;
}
