#include <charconv>
#include <cstddef>
#include <future>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>

int contar_primos(const std::string& texto) {
    int limite = 0;
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, limite);
    if (error != std::errc{} || resto != fin || limite < 0 ||
        limite > 1'000'000) {
        throw std::invalid_argument{"no es un entero entre 0 y 1000000"};
    }
    const auto n = static_cast<std::size_t>(limite);
    std::vector<bool> compuesto(n + 1, false);
    int primos = 0;
    for (std::size_t i = 2; i <= n; ++i) {
        if (compuesto[i]) {
            continue;
        }
        ++primos;
        for (std::size_t j = i * i; j <= n; j += i) {
            compuesto[j] = true;
        }
    }
    return primos;
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 17) {
        std::cerr << "Uso: 097 LIMITE... (de 1 a 16 límites)\n";
        return 1;
    }
    std::vector<std::string> limites(argv + 1, argv + argc);
    std::vector<std::future<int>> futuros;
    for (const std::string& limite : limites) {
        futuros.push_back(
            std::async(std::launch::async, contar_primos, limite));
    }

    bool hubo_errores = false;
    for (std::size_t i = 0; i < futuros.size(); ++i) {
        try {
            const int primos = futuros[i].get();
            std::cout << "Primos hasta " << limites[i] << ": " << primos
                      << '\n';
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error en '" << limites[i] << "': " << e.what()
                      << ".\n";
            hubo_errores = true;
        }
    }
    return hubo_errores ? 1 : 0;
}
