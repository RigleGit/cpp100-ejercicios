#ifndef TAREAS_HPP
#define TAREAS_HPP

#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

struct Tarea {
    int id;
    bool hecha;
    std::string texto;

    bool operator==(const Tarea&) const = default;
};

class ErrorTareas : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};

// Un archivo ausente equivale a una lista vacía. Un archivo con una
// línea mal formada lanza ErrorTareas y no se modifica.
std::vector<Tarea> cargar(const std::filesystem::path& ruta);

// Escribe primero un temporal y después lo renombra sobre la ruta.
void guardar(const std::filesystem::path& ruta,
             const std::vector<Tarea>& tareas);

// Devuelve el identificador asignado a la tarea nueva.
int anadir(std::vector<Tarea>& tareas, const std::string& texto);

// Devuelve false si la tarea ya estaba completada.
bool completar(std::vector<Tarea>& tareas, int id);

#endif
