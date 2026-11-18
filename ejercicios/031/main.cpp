#include <cstddef>
#include <iostream>
#include <string>

int reemplazarTodo(std::string& texto, const std::string& buscado,
                   const std::string& nuevo) {
    int cambios = 0;
    std::size_t posicion = texto.find(buscado);
    while (posicion != std::string::npos) {
        texto.replace(posicion, buscado.size(), nuevo);
        ++cambios;
        posicion = texto.find(buscado, posicion + nuevo.size());
    }
    return cambios;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: indica el texto buscado y su reemplazo.\n";
        return 1;
    }
    const std::string buscado = argv[1];
    const std::string nuevo = argv[2];
    if (buscado.empty()) {
        std::cerr << "Error: el texto buscado no puede estar vacío.\n";
        return 1;
    }

    std::string linea;
    int total = 0;
    while (std::getline(std::cin, linea)) {
        total += reemplazarTodo(linea, buscado, nuevo);
        std::cout << linea << '\n';
    }
    std::cout << "Reemplazos: " << total << '\n';
}
