#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {
    std::map<std::string, std::string> agenda;
    std::string texto;
    int numero_linea = 0;
    while (std::getline(std::cin, texto)) {
        ++numero_linea;
        std::istringstream linea(texto);
        std::string orden;
        std::string nombre;
        std::string telefono;
        std::string sobra;
        linea >> orden >> nombre >> telefono >> sobra;

        if (orden == "ADD" && !telefono.empty() && sobra.empty()) {
            auto [it, nuevo] = agenda.insert_or_assign(nombre, telefono);
            std::cout << (nuevo ? "Guardado: " : "Actualizado: ")
                      << it->first << '\n';
        } else if (orden == "GET" && !nombre.empty() && telefono.empty()) {
            auto it = agenda.find(nombre);
            if (it == agenda.end()) {
                std::cout << "No encontrado: " << nombre << '\n';
            } else {
                std::cout << it->first << ": " << it->second << '\n';
            }
        } else if (orden == "DEL" && !nombre.empty() && telefono.empty()) {
            if (agenda.erase(nombre) == 1) {
                std::cout << "Borrado: " << nombre << '\n';
            } else {
                std::cout << "No encontrado: " << nombre << '\n';
            }
        } else if (orden == "LIST" && nombre.empty()) {
            std::cout << "Contactos: " << agenda.size() << '\n';
            for (const auto& [quien, numero] : agenda) {
                std::cout << "  " << quien << ": " << numero << '\n';
            }
        } else {
            std::cerr << "Error en la línea " << numero_linea
                      << ": usa ADD nombre teléfono, GET nombre, "
                         "DEL nombre o LIST.\n";
            return 1;
        }
    }
}
