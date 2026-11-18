#include <charconv>
#include <cmath>
#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>
#include <variant>
#include <vector>

struct Alumno {
    std::string nombre;
    double media;
};

std::string recortar(const std::string& texto) {
    const std::size_t inicio = texto.find_first_not_of(" \t\r");
    if (inicio == std::string::npos) {
        return "";
    }
    const std::size_t fin = texto.find_last_not_of(" \t\r");
    return texto.substr(inicio, fin - inicio + 1);
}

std::vector<std::string> dividir(const std::string& linea) {
    std::vector<std::string> campos;
    std::size_t inicio = 0;
    while (true) {
        const std::size_t coma = linea.find(',', inicio);
        if (coma == std::string::npos) {
            campos.push_back(recortar(linea.substr(inicio)));
            return campos;
        }
        campos.push_back(recortar(linea.substr(inicio, coma - inicio)));
        inicio = coma + 1;
    }
}

std::variant<Alumno, std::string> interpretar(const std::string& linea) {
    const std::vector<std::string> campos = dividir(linea);
    if (campos[0].empty()) {
        return std::string{"falta el nombre"};
    }
    if (campos.size() < 2) {
        return std::string{"no tiene notas"};
    }
    double suma = 0.0;
    for (std::size_t i = 1; i < campos.size(); ++i) {
        const std::string& campo = campos[i];
        double nota = 0.0;
        const char* fin = campo.data() + campo.size();
        auto [resto, error] = std::from_chars(campo.data(), fin, nota);
        if (campo.empty() || error != std::errc{} || resto != fin ||
            !std::isfinite(nota)) {
            return "'" + campo + "' no es una nota";
        }
        if (nota < 0.0 || nota > 10.0) {
            return "'" + campo + "' está fuera de 0..10";
        }
        suma += nota;
    }
    const auto notas = static_cast<double>(campos.size() - 1);
    return Alumno{campos[0], suma / notas};
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: 089 ARCHIVO.csv\n";
        return 1;
    }
    const std::string ruta = argv[1];
    std::ifstream archivo{ruta};
    if (!archivo) {
        std::cerr << "Error: no se puede abrir '" << ruta << "'.\n";
        return 1;
    }

    std::string linea;
    int numero = 0;
    std::vector<Alumno> alumnos;
    while (std::getline(archivo, linea)) {
        ++numero;
        if (recortar(linea).empty()) {
            continue;
        }
        const auto resultado = interpretar(linea);
        if (const auto* motivo = std::get_if<std::string>(&resultado)) {
            std::cerr << "Aviso: línea " << numero
                      << " ignorada: " << *motivo << ".\n";
            continue;
        }
        alumnos.push_back(std::get<Alumno>(resultado));
    }

    double suma = 0.0;
    for (const Alumno& alumno : alumnos) {
        std::cout << std::format("{}: {:.2f}\n", alumno.nombre,
                                 alumno.media);
        suma += alumno.media;
    }
    std::cout << "Alumnos: " << alumnos.size() << '\n';
    if (alumnos.empty()) {
        std::cout << "Media del grupo: sin datos\n";
    } else {
        const auto cantidad = static_cast<double>(alumnos.size());
        std::cout << std::format("Media del grupo: {:.2f}\n",
                                 suma / cantidad);
    }
}
