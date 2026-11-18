#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>

std::array<int, 5> con_punto_extra(std::array<int, 5> notas) {
    for (int& nota : notas) {
        if (nota < 10) {
            ++nota;
        }
    }
    return notas;
}

void subir_en_sitio(int notas[], std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        if (notas[i] < 10) {
            ++notas[i];
        }
    }
}

void mostrar(const std::string& etiqueta, const int notas[],
             std::size_t n) {
    std::cout << etiqueta << ':';
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << ' ' << notas[i];
    }
    std::cout << '\n';
}

void mostrar(const std::string& etiqueta, const std::array<int, 5>& notas) {
    mostrar(etiqueta, notas.data(), notas.size());
}

int main() {
    int leidas[5]{};
    for (int& nota : leidas) {
        if (!(std::cin >> nota)) {
            std::cerr << "Error: se esperaban cinco notas enteras.\n";
            return 1;
        }
        if (nota < 0 || nota > 10) {
            std::cerr << "Error: las notas van de 0 a 10.\n";
            return 1;
        }
    }

    std::array<int, 5> notas = std::to_array(leidas);
    std::array<int, 5> subidas = con_punto_extra(notas);
    subir_en_sitio(leidas, std::size(leidas));

    mostrar("Notas", notas);
    mostrar("Copia con punto extra", subidas);
    mostrar("Array de C tras subir_en_sitio", leidas, std::size(leidas));
}
