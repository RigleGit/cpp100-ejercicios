#ifdef NDEBUG
#error "Compila las pruebas sin NDEBUG: assert no comprobaría nada."
#endif

#include "tareas.hpp"
#include "vista.hpp"

#include <cassert>
#include <iostream>
#include <vector>

std::vector<int> ids(const std::vector<Tarea>& tareas) {
    std::vector<int> resultado;
    for (const Tarea& tarea : tareas) {
        resultado.push_back(tarea.id);
    }
    return resultado;
}

int main() {
    const std::vector<Tarea> tareas{{1, false, "regar"},
                                    {2, true, "Barrer"},
                                    {4, false, "Comprar pan"},
                                    {7, true, "barrer"}};

    // Sin opciones: todas, por identificador.
    assert(ids(preparar_listado(tareas, {})) ==
           (std::vector<int>{1, 2, 4, 7}));

    // Filtros.
    assert(ids(preparar_listado(tareas, {Filtro::pendientes, Orden::id})) ==
           (std::vector<int>{1, 4}));
    assert(ids(preparar_listado(tareas, {Filtro::hechas, Orden::id})) ==
           (std::vector<int>{2, 7}));

    // Orden por texto sin distinguir mayúsculas; empate por id.
    assert(ids(preparar_listado(tareas, {Filtro::todas, Orden::texto})) ==
           (std::vector<int>{2, 7, 4, 1}));

    // La lista vacía sigue vacía con cualquier opción.
    assert(preparar_listado({}, {Filtro::hechas, Orden::texto}).empty());

    // Añadir continúa tras el último identificador, aunque haya huecos.
    std::vector<Tarea> copia = tareas;
    assert(anadir(copia, "nueva") == 8);
    assert(copia.size() == 5);

    // Completar informa de si hubo cambio.
    assert(completar(copia, 1));
    assert(!completar(copia, 1));
    bool lanza = false;
    try {
        completar(copia, 3);
    } catch (const ErrorTareas&) {
        lanza = true;
    }
    assert(lanza);

    std::cout << "Pruebas del gestor superadas.\n";
}
