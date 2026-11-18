#include "tareas.hpp"

#include <algorithm>
#include <charconv>
#include <fstream>
#include <limits>
#include <system_error>
#include <utility>

namespace fs = std::filesystem;

namespace {

void validar_texto(const std::string& texto) {
    if (texto.find_first_not_of(' ') == std::string::npos) {
        throw ErrorTareas{"el texto de la tarea está vacío"};
    }
    if (texto.size() > 200) {
        throw ErrorTareas{"el texto supera los 200 bytes"};
    }
    const bool control = std::ranges::any_of(
        texto, [](char c) { return static_cast<unsigned char>(c) < 32; });
    if (control) {
        throw ErrorTareas{"el texto contiene caracteres de control"};
    }
}

Tarea interpretar(const std::string& linea) {
    const auto primera = linea.find(';');
    const auto segunda = linea.find(';', primera + 1);
    if (primera == std::string::npos || segunda == std::string::npos) {
        throw ErrorTareas{"se esperaba ID;ESTADO;TEXTO"};
    }
    Tarea tarea{0, false, linea.substr(segunda + 1)};
    const char* inicio = linea.data();
    const char* fin = inicio + primera;
    auto [resto, error] = std::from_chars(inicio, fin, tarea.id);
    if (error != std::errc{} || resto != fin || tarea.id <= 0) {
        throw ErrorTareas{"identificador no válido"};
    }
    const std::string estado =
        linea.substr(primera + 1, segunda - primera - 1);
    if (estado == "hecha") {
        tarea.hecha = true;
    } else if (estado != "pendiente") {
        throw ErrorTareas{"estado desconocido '" + estado + "'"};
    }
    validar_texto(tarea.texto);
    return tarea;
}

} // namespace

std::vector<Tarea> cargar(const fs::path& ruta) {
    std::vector<Tarea> tareas;
    std::ifstream archivo{ruta};
    if (!archivo) {
        std::error_code error;
        if (fs::exists(ruta, error) || error) {
            throw ErrorTareas{"no se puede abrir " + ruta.string()};
        }
        return tareas;
    }
    std::string linea;
    int numero = 0;
    while (std::getline(archivo, linea)) {
        ++numero;
        try {
            Tarea tarea = interpretar(linea);
            if (!tareas.empty() && tarea.id <= tareas.back().id) {
                throw ErrorTareas{"los identificadores deben crecer"};
            }
            tareas.push_back(std::move(tarea));
        } catch (const ErrorTareas& e) {
            throw ErrorTareas{ruta.string() + ", línea " +
                              std::to_string(numero) + ": " + e.what()};
        }
    }
    if (archivo.bad()) {
        throw ErrorTareas{"fallo al leer " + ruta.string()};
    }
    return tareas;
}

void guardar(const fs::path& ruta, const std::vector<Tarea>& tareas) {
    fs::path temporal = ruta;
    temporal += ".tmp";
    std::ofstream archivo{temporal, std::ios::trunc};
    for (const Tarea& tarea : tareas) {
        archivo << tarea.id << ';' << (tarea.hecha ? "hecha" : "pendiente")
                << ';' << tarea.texto << '\n';
    }
    archivo.close();
    if (!archivo) {
        std::error_code ignorado;
        fs::remove(temporal, ignorado);
        throw ErrorTareas{"no se pudo escribir " + temporal.string()};
    }
    std::error_code error;
    fs::rename(temporal, ruta, error);
    if (error) {
        fs::remove(temporal, error);
        throw ErrorTareas{"no se pudo reemplazar " + ruta.string()};
    }
}

int anadir(std::vector<Tarea>& tareas, const std::string& texto) {
    validar_texto(texto);
    if (!tareas.empty() &&
        tareas.back().id == std::numeric_limits<int>::max()) {
        throw ErrorTareas{"no quedan identificadores libres"};
    }
    const int id = tareas.empty() ? 1 : tareas.back().id + 1;
    tareas.push_back({id, false, texto});
    return id;
}

bool completar(std::vector<Tarea>& tareas, int id) {
    const auto it = std::ranges::find(tareas, id, &Tarea::id);
    if (it == tareas.end()) {
        throw ErrorTareas{"no existe la tarea " + std::to_string(id)};
    }
    if (it->hecha) {
        return false;
    }
    it->hecha = true;
    return true;
}
