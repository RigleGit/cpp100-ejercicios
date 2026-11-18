#include <charconv>
#include <iostream>
#include <mutex>
#include <optional>
#include <string_view>
#include <system_error>
#include <thread>
#include <vector>

class Contador {
  public:
    void incrementar() {
        const std::lock_guard<std::mutex> cerrojo{mutex_};
        ++valor_;
    }

    long long valor() const {
        const std::lock_guard<std::mutex> cerrojo{mutex_};
        return valor_;
    }

  private:
    mutable std::mutex mutex_;
    long long valor_ = 0;
};

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

int main(int argc, char* argv[]) {
    const auto hilos = argc == 3 ? leer(argv[1], 1, 16) : std::nullopt;
    const auto veces =
        argc == 3 ? leer(argv[2], 0, 1'000'000) : std::nullopt;
    if (!hilos || !veces) {
        std::cerr << "Uso: 096 HILOS INCREMENTOS (HILOS de 1 a 16, "
                     "INCREMENTOS de 0 a 1000000)\n";
        return 1;
    }

    Contador contador;
    std::vector<std::thread> trabajadores;
    for (long long i = 0; i < *hilos; ++i) {
        trabajadores.emplace_back([&contador, n = *veces] {
            for (long long j = 0; j < n; ++j) {
                contador.incrementar();
            }
        });
    }
    for (std::thread& t : trabajadores) {
        t.join();
    }

    std::cout << "Esperado: " << *hilos * *veces << '\n';
    std::cout << "Obtenido: " << contador.valor() << '\n';
}
