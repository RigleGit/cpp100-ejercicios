#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: 088 ARCHIVO\n";
        return 1;
    }
    const std::string ruta = argv[1];
    std::ifstream archivo{ruta};
    if (!archivo) {
        std::cerr << "Error: no se puede abrir '" << ruta << "'.\n";
        return 1;
    }

    std::string linea;
    int total = 0;
    int vacias = 0;
    int mas_larga = 0;
    std::size_t longitud_maxima = 0;
    while (std::getline(archivo, linea)) {
        ++total;
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        if (linea.empty()) {
            ++vacias;
        }
        if (mas_larga == 0 || linea.size() > longitud_maxima) {
            mas_larga = total;
            longitud_maxima = linea.size();
        }
    }
    if (archivo.bad()) {
        std::cerr << "Error: fallo al leer '" << ruta << "'.\n";
        return 1;
    }

    std::cout << "Líneas: " << total << '\n';
    std::cout << "Vacías: " << vacias << '\n';
    if (total == 0) {
        std::cout << "Más larga: ninguna\n";
    } else {
        std::cout << "Más larga: línea " << mas_larga << " ("
                  << longitud_maxima << " bytes)\n";
    }
}
