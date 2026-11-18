#include <array>
#include <fstream>
#include <iostream>
#include <string>

long long medir(const std::string& ruta) {
    std::ifstream archivo{ruta, std::ios::binary | std::ios::ate};
    if (!archivo) {
        return -1;
    }
    return static_cast<long long>(archivo.tellg());
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: 090 ORIGEN DESTINO\n";
        return 1;
    }
    const std::string origen = argv[1];
    const std::string destino = argv[2];
    if (origen == destino) {
        std::cerr << "Error: el origen y el destino son la misma ruta.\n";
        return 1;
    }

    std::ifstream entrada{origen, std::ios::binary};
    if (!entrada) {
        std::cerr << "Error: no se puede abrir '" << origen << "'.\n";
        return 1;
    }
    std::ofstream salida{destino, std::ios::binary | std::ios::trunc};
    if (!salida) {
        std::cerr << "Error: no se puede crear '" << destino << "'.\n";
        return 1;
    }

    std::array<char, 4096> bloque{};
    long long copiados = 0;
    while (entrada.read(bloque.data(), bloque.size()) ||
           entrada.gcount() > 0) {
        salida.write(bloque.data(), entrada.gcount());
        copiados += entrada.gcount();
    }
    if (entrada.bad()) {
        std::cerr << "Error: fallo al leer '" << origen << "'.\n";
        return 1;
    }
    salida.close();
    if (!salida) {
        std::cerr << "Error: fallo al escribir '" << destino << "'.\n";
        return 1;
    }

    const long long tam_origen = medir(origen);
    const long long tam_destino = medir(destino);
    if (tam_origen != copiados || tam_destino != copiados) {
        std::cerr << "Error: los tamaños no coinciden (origen "
                  << tam_origen << ", destino " << tam_destino << ").\n";
        return 1;
    }
    std::cout << "Copiados " << copiados << " bytes de " << origen << " a "
              << destino << ".\n";
}
