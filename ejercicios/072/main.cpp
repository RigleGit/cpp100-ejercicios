#include <charconv>
#include <cstddef>
#include <iostream>
#include <optional>
#include <span>
#include <string>
#include <vector>

std::optional<int> primer_par(std::span<const int> valores) {
    for (int v : valores) {
        if (v % 2 == 0) {
            return v;
        }
    }
    return std::nullopt;
}

std::optional<std::size_t> posicion(std::span<const int> valores,
                                    int buscado) {
    for (std::size_t i = 0; i < valores.size(); ++i) {
        if (valores[i] == buscado) {
            return i;
        }
    }
    return std::nullopt;
}

std::optional<int> maximo(std::span<const int> valores) {
    if (valores.empty()) {
        return std::nullopt;
    }
    int mayor = valores[0];
    for (int v : valores) {
        if (v > mayor) {
            mayor = v;
        }
    }
    return mayor;
}

int main(int argc, char* argv[]) {
    int buscado = 0;
    std::string texto;
    if (argc == 2) {
        texto = argv[1];
    }
    auto [fin, error] =
        std::from_chars(texto.data(), texto.data() + texto.size(), buscado);
    if (argc != 2 || texto.empty() || error != std::errc{} ||
        fin != texto.data() + texto.size()) {
        std::cerr << "Error: uso: 072 ENTERO_BUSCADO.\n";
        return 1;
    }

    std::vector<int> valores;
    while (std::cin >> std::ws && !std::cin.eof()) {
        int v = 0;
        if (!(std::cin >> v)) {
            std::cerr << "Error: la entrada solo puede tener enteros.\n";
            return 1;
        }
        valores.push_back(v);
    }

    if (std::optional<int> par = primer_par(valores)) {
        std::cout << "Primer par: " << *par << '\n';
    } else {
        std::cout << "Primer par: ninguno\n";
    }

    std::optional<std::size_t> donde = posicion(valores, buscado);
    if (donde.has_value()) {
        std::cout << "Posición de " << buscado << ": " << donde.value()
                  << '\n';
    } else {
        std::cout << "Posición de " << buscado << ": no aparece\n";
    }

    std::cout << "Máximo o cero: " << maximo(valores).value_or(0) << '\n';
}
