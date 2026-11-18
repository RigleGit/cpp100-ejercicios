#include "vista.hpp"

#include <algorithm>
#include <string>

namespace {

std::string clave(const std::string& texto) {
    std::string resultado = texto;
    for (char& c : resultado) {
        if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>(c - 'A' + 'a');
        }
    }
    return resultado;
}

bool pasa_filtro(const Tarea& tarea, Filtro filtro) {
    switch (filtro) {
    case Filtro::pendientes:
        return !tarea.hecha;
    case Filtro::hechas:
        return tarea.hecha;
    default:
        return true;
    }
}

} // namespace

std::vector<Tarea> preparar_listado(const std::vector<Tarea>& tareas,
                                    const OpcionesListado& opciones) {
    std::vector<Tarea> listado;
    for (const Tarea& tarea : tareas) {
        if (pasa_filtro(tarea, opciones.filtro)) {
            listado.push_back(tarea);
        }
    }
    if (opciones.orden == Orden::texto) {
        std::ranges::stable_sort(listado, {}, [](const Tarea& tarea) {
            return clave(tarea.texto);
        });
    }
    return listado;
}
