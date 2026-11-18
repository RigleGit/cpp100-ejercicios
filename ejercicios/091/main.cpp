#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

namespace fs = std::filesystem;

struct Entrada {
    std::string nombre;
    fs::file_type tipo;
    std::uintmax_t bytes;
};

std::vector<Entrada> leer_directorio(const fs::path& carpeta) {
    std::vector<Entrada> entradas;
    for (const fs::directory_entry& entrada :
         fs::directory_iterator{carpeta}) {
        const fs::file_type tipo = entrada.status().type();
        const std::uintmax_t bytes =
            tipo == fs::file_type::regular ? entrada.file_size() : 0;
        entradas.push_back(
            {entrada.path().filename().string(), tipo, bytes});
    }
    std::ranges::sort(entradas, {}, &Entrada::nombre);
    return entradas;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: 091 DIRECTORIO\n";
        return 1;
    }
    const fs::path carpeta = argv[1];
    std::error_code error;
    const fs::file_status estado = fs::status(carpeta, error);
    if (!fs::exists(estado)) {
        std::cerr << "Error: '" << carpeta.string() << "' no existe.\n";
        return 1;
    }
    if (!fs::is_directory(estado)) {
        std::cerr << "Error: '" << carpeta.string()
                  << "' no es un directorio.\n";
        return 1;
    }

    try {
        int archivos = 0;
        int directorios = 0;
        std::uintmax_t total = 0;
        for (const Entrada& entrada : leer_directorio(carpeta)) {
            if (entrada.tipo == fs::file_type::regular) {
                std::cout << entrada.nombre << ": " << entrada.bytes
                          << " B\n";
                ++archivos;
                total += entrada.bytes;
            } else if (entrada.tipo == fs::file_type::directory) {
                std::cout << entrada.nombre << "/: directorio\n";
                ++directorios;
            } else {
                std::cout << entrada.nombre << ": otro tipo\n";
            }
        }
        std::cout << "Archivos: " << archivos << " (" << total << " B)\n";
        std::cout << "Directorios: " << directorios << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
