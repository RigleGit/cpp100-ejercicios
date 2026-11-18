#include <charconv>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>

namespace fs = std::filesystem;

const std::string cabecera = "inventario 1";

struct Producto {
    std::string nombre;
    long long cantidad;
    long long centimos;

    bool operator==(const Producto&) const = default;
};

bool leer_entero(const std::string& texto, long long maximo,
                 long long& valor) {
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, valor);
    return error == std::errc{} && resto == fin && valor >= 0 &&
           valor <= maximo;
}

Producto interpretar(const std::string& linea) {
    const auto primera = linea.find(';');
    const auto segunda = linea.find(';', primera + 1);
    if (primera == std::string::npos || segunda == std::string::npos ||
        linea.find(';', segunda + 1) != std::string::npos) {
        throw std::runtime_error{"se esperaba NOMBRE;CANTIDAD;CENTIMOS"};
    }
    Producto p{linea.substr(0, primera), 0, 0};
    if (p.nombre.empty()) {
        throw std::runtime_error{"falta el nombre"};
    }
    if (!leer_entero(linea.substr(primera + 1, segunda - primera - 1),
                     1'000'000, p.cantidad)) {
        throw std::runtime_error{"cantidad no válida"};
    }
    if (!leer_entero(linea.substr(segunda + 1), 1'000'000'000,
                     p.centimos)) {
        throw std::runtime_error{"precio no válido"};
    }
    return p;
}

// Lee una línea y quita el '\r' final de los archivos de Windows.
bool leer_linea(std::istream& entrada, std::string& linea) {
    if (!std::getline(entrada, linea)) {
        return false;
    }
    if (!linea.empty() && linea.back() == '\r') {
        linea.pop_back();
    }
    return true;
}

std::vector<Producto> leer(std::istream& entrada, bool con_cabecera) {
    std::vector<Producto> productos;
    std::string linea;
    int numero = 0;
    if (con_cabecera) {
        ++numero;
        if (!leer_linea(entrada, linea) || linea != cabecera) {
            throw std::runtime_error{"línea 1: falta la cabecera '" +
                                     cabecera + "'"};
        }
    }
    while (leer_linea(entrada, linea)) {
        ++numero;
        try {
            productos.push_back(interpretar(linea));
        } catch (const std::runtime_error& e) {
            throw std::runtime_error{"línea " + std::to_string(numero) +
                                     ": " + e.what()};
        }
    }
    return productos;
}

std::vector<Producto> cargar(const fs::path& ruta) {
    std::ifstream archivo{ruta};
    if (!archivo) {
        throw std::runtime_error{"no se puede abrir el archivo"};
    }
    return leer(archivo, true);
}

void guardar(const fs::path& ruta, const std::vector<Producto>& productos) {
    fs::path temporal = ruta;
    temporal += ".tmp";
    {
        std::ofstream archivo{temporal, std::ios::trunc};
        archivo << cabecera << '\n';
        for (const Producto& p : productos) {
            archivo << p.nombre << ';' << p.cantidad << ';' << p.centimos
                    << '\n';
        }
        archivo.close();
        if (!archivo) {
            std::error_code ignorado;
            fs::remove(temporal, ignorado);
            throw std::runtime_error{"no se pudo escribir el temporal"};
        }
    }
    fs::rename(temporal, ruta);
}

std::string euros(long long centimos) {
    return std::format("{}.{:02} €", centimos / 100, centimos % 100);
}

int main(int argc, char* argv[]) {
    const std::string orden = argc == 3 ? argv[1] : "";
    if (orden != "guardar" && orden != "mostrar") {
        std::cerr << "Uso: 092 guardar|mostrar ARCHIVO\n";
        return 1;
    }
    const fs::path ruta = argv[2];
    std::string lugar = ruta.string();
    try {
        if (orden == "guardar") {
            lugar = "entrada";
            const std::vector<Producto> productos = leer(std::cin, false);
            lugar = ruta.string();
            guardar(ruta, productos);
            if (cargar(ruta) != productos) {
                throw std::runtime_error{"la relectura no coincide"};
            }
            std::cout << "Productos guardados en " << ruta.string() << ": "
                      << productos.size() << '\n';
            return 0;
        }
        const std::vector<Producto> productos = cargar(ruta);
        long long total = 0;
        std::cout << "Productos: " << productos.size() << '\n';
        for (const Producto& p : productos) {
            const long long valor = p.cantidad * p.centimos;
            std::cout << p.nombre << ": " << p.cantidad << " uds. a "
                      << euros(p.centimos) << " = " << euros(valor) << '\n';
            total += valor;
        }
        std::cout << "Total: " << euros(total) << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << lugar << ", " << e.what() << ".\n";
        return 1;
    }
}
