#ifndef VISTA_HPP
#define VISTA_HPP

#include "tareas.hpp"

#include <vector>

enum class Filtro { todas, pendientes, hechas };
enum class Orden { id, texto };

struct OpcionesListado {
    Filtro filtro = Filtro::todas;
    Orden orden = Orden::id;
};

// Devuelve una copia filtrada y ordenada; la lista original no cambia.
// El orden por texto no distingue mayúsculas ASCII y conserva el orden
// por identificador en los empates.
std::vector<Tarea> preparar_listado(const std::vector<Tarea>& tareas,
                                    const OpcionesListado& opciones);

#endif
