#include <charconv>
#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>
#include <string_view>
#include <system_error>
#include <thread>
#include <vector>

std::optional<long long> leer(std::string_view texto, long long minimo,
                              long long maximo) {
    long long valor = 0;
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, valor);
    if (error != std::errc{} || resto != fin || valor < minimo ||
        valor > maximo) {
        return std::nullopt;
    }
    return valor;
}

void sumar_tramo(const std::vector<long long>& datos, std::size_t inicio,
                 std::size_t fin, long long& resultado) {
    long long suma = 0;
    for (std::size_t i = inicio; i < fin; ++i) {
        suma += datos[i];
    }
    resultado = suma;
}

int main(int argc, char* argv[]) {
    const auto n = argc == 3 ? leer(argv[1], 0, 1'000'000) : std::nullopt;
    const auto hilos = argc == 3 ? leer(argv[2], 1, 16) : std::nullopt;
    if (!n || !hilos) {
        std::cerr << "Uso: 095 N HILOS (N de 0 a 1000000, HILOS de 1 a "
                     "16)\n";
        return 1;
    }

    std::vector<long long> datos(static_cast<std::size_t>(*n));
    for (std::size_t i = 0; i < datos.size(); ++i) {
        datos[i] = static_cast<long long>(i) + 1;
    }

    const auto partes = static_cast<std::size_t>(*hilos);
    const std::size_t base = datos.size() / partes;
    const std::size_t sobran = datos.size() % partes;

    std::vector<long long> parciales(partes, 0);
    std::vector<std::size_t> inicios(partes + 1, 0);
    std::vector<std::thread> trabajadores;
    for (std::size_t i = 0; i < partes; ++i) {
        const std::size_t tamano = base + (i < sobran ? 1 : 0);
        inicios[i + 1] = inicios[i] + tamano;
        trabajadores.emplace_back(sumar_tramo, std::cref(datos), inicios[i],
                                  inicios[i + 1], std::ref(parciales[i]));
    }
    for (std::thread& t : trabajadores) {
        t.join();
    }

    long long total = 0;
    for (std::size_t i = 0; i < partes; ++i) {
        std::cout << "Hilo " << i + 1 << ": ";
        if (inicios[i] == inicios[i + 1]) {
            std::cout << "sin elementos\n";
        } else {
            std::cout << inicios[i] + 1 << ".." << inicios[i + 1] << " = "
                      << parciales[i] << '\n';
        }
        total += parciales[i];
    }
    std::cout << "Total: " << total << '\n';
    std::cout << "Fórmula: " << *n * (*n + 1) / 2 << '\n';
}
