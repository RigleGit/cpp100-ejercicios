#include "tareas.hpp"
#include "vista.hpp"

#include <algorithm>
#include <charconv>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>

class ErrorUso : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};

const char* const ayuda = "Órdenes:\n"
                          "  099 ARCHIVO listar [--pendientes | --hechas] "
                          "[--por-texto]\n"
                          "  099 ARCHIVO añadir TEXTO\n"
                          "  099 ARCHIVO completar ID\n"
                          "  099 ayuda\n";

int leer_id(const std::string& texto) {
    int id = 0;
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, id);
    if (error != std::errc{} || resto != fin || id <= 0) {
        throw ErrorUso{"'" + texto + "' no es un identificador válido"};
    }
    return id;
}

OpcionesListado leer_opciones(const std::vector<std::string>& opciones) {
    OpcionesListado resultado;
    bool hay_filtro = false;
    bool hay_orden = false;
    for (const std::string& opcion : opciones) {
        if (opcion == "--pendientes" || opcion == "--hechas") {
            if (hay_filtro) {
                throw ErrorUso{"listar admite un solo filtro"};
            }
            hay_filtro = true;
            resultado.filtro =
                opcion == "--hechas" ? Filtro::hechas : Filtro::pendientes;
        } else if (opcion == "--por-texto") {
            if (hay_orden) {
                throw ErrorUso{"la opción --por-texto está repetida"};
            }
            hay_orden = true;
            resultado.orden = Orden::texto;
        } else {
            throw ErrorUso{"opción desconocida '" + opcion + "'"};
        }
    }
    return resultado;
}

void listar(const std::vector<Tarea>& tareas,
            const OpcionesListado& opciones) {
    const std::vector<Tarea> listado = preparar_listado(tareas, opciones);
    if (listado.empty()) {
        std::cout << "No hay tareas que mostrar.\n";
    }
    for (const Tarea& tarea : listado) {
        std::cout << (tarea.hecha ? "[x] " : "[ ] ") << tarea.id << ' '
                  << tarea.texto << '\n';
    }
    const auto pendientes =
        std::ranges::count(tareas, false, &Tarea::hecha);
    std::cout << "Pendientes: " << pendientes << " de " << tareas.size()
              << '\n';
}

void ejecutar(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw ErrorUso{"faltan argumentos"};
    }
    const std::string& ruta = args[0];
    const std::string& orden = args[1];
    const std::vector<std::string> resto(args.begin() + 2, args.end());

    if (orden == "listar") {
        const OpcionesListado opciones = leer_opciones(resto);
        listar(cargar(ruta), opciones);
    } else if (orden == "añadir") {
        if (resto.size() != 1) {
            throw ErrorUso{"añadir necesita un único TEXTO; usa comillas "
                           "si tiene espacios"};
        }
        std::vector<Tarea> tareas = cargar(ruta);
        const int id = anadir(tareas, resto[0]);
        guardar(ruta, tareas);
        std::cout << "Añadida la tarea " << id << ": " << resto[0] << '\n';
    } else if (orden == "completar") {
        if (resto.size() != 1) {
            throw ErrorUso{"completar necesita un único ID"};
        }
        const int id = leer_id(resto[0]);
        std::vector<Tarea> tareas = cargar(ruta);
        if (completar(tareas, id)) {
            guardar(ruta, tareas);
            std::cout << "Completada la tarea " << id << ".\n";
        } else {
            std::cout << "La tarea " << id << " ya estaba completada.\n";
        }
    } else {
        throw ErrorUso{"orden desconocida '" + orden + "'"};
    }
}

int main(int argc, char* argv[]) {
    const std::vector<std::string> args(argv + 1, argv + argc);
    if (args.size() == 1 && args[0] == "ayuda") {
        std::cout << ayuda;
        return 0;
    }
    try {
        ejecutar(args);
    } catch (const ErrorUso& e) {
        std::cerr << "Error de uso: " << e.what() << ".\n"
                  << "Escribe '099 ayuda' para ver las órdenes.\n";
        return 2;
    } catch (const ErrorTareas& e) {
        std::cerr << "Error: " << e.what() << ".\n";
        return 1;
    }
}
