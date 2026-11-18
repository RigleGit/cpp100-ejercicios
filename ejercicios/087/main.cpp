#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    const bool anadir = argc == 3 && std::string{argv[1]} == "-a";
    if (argc != 2 && !anadir) {
        std::cerr << "Uso: 087 [-a] ARCHIVO\n";
        return 1;
    }
    const std::string ruta = argv[argc - 1];
    const std::ios::openmode modo =
        anadir ? std::ios::app : std::ios::trunc;

    std::ofstream archivo{ruta, std::ios::out | modo};
    if (!archivo) {
        std::cerr << "Error: no se puede abrir '" << ruta
                  << "' para escribir.\n";
        return 1;
    }

    std::string linea;
    int escritas = 0;
    while (std::getline(std::cin, linea)) {
        archivo << linea << '\n';
        ++escritas;
    }
    archivo.close();
    if (!archivo) {
        std::cerr << "Error: no se pudo terminar de escribir '" << ruta
                  << "'.\n";
        return 1;
    }
    std::cout << "Líneas " << (anadir ? "añadidas a " : "guardadas en ")
              << ruta << ": " << escritas << '\n';
}
