#include "tareas.hpp"

#include <charconv>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

int leer_id(const std::string& texto) {
    int id = 0;
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, id);
    if (error != std::errc{} || resto != fin || id <= 0) {
        throw ErrorTareas{"'" + texto + "' no es un identificador válido"};
    }
    return id;
}

void listar(const std::vector<Tarea>& tareas) {
    if (tareas.empty()) {
        std::cout << "No hay tareas.\n";
    }
    for (const Tarea& tarea : tareas) {
        std::cout << (tarea.hecha ? "[x] " : "[ ] ") << tarea.id << ' '
                  << tarea.texto << '\n';
    }
}

int main(int argc, char* argv[]) {
    const std::vector<std::string> args(argv + 1, argv + argc);
    const bool uso_valido = (args.size() == 2 && args[1] == "listar") ||
                            (args.size() == 3 && (args[1] == "añadir" ||
                                                  args[1] == "completar"));
    if (!uso_valido) {
        std::cerr << "Uso: 098 ARCHIVO listar\n"
                     "     098 ARCHIVO añadir TEXTO\n"
                     "     098 ARCHIVO completar ID\n";
        return 2;
    }
    const std::string& ruta = args[0];
    const std::string& orden = args[1];
    try {
        std::vector<Tarea> tareas = cargar(ruta);
        if (orden == "listar") {
            listar(tareas);
        } else if (orden == "añadir") {
            const int id = anadir(tareas, args[2]);
            guardar(ruta, tareas);
            std::cout << "Añadida la tarea " << id << ": " << args[2]
                      << '\n';
        } else {
            const int id = leer_id(args[2]);
            if (completar(tareas, id)) {
                guardar(ruta, tareas);
                std::cout << "Completada la tarea " << id << ".\n";
            } else {
                std::cout << "La tarea " << id
                          << " ya estaba completada.\n";
            }
        }
    } catch (const ErrorTareas& e) {
        std::cerr << "Error: " << e.what() << ".\n";
        return 1;
    }
}
