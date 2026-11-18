#include <format>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

struct Producto {
    std::string nombre;
    int unidades;
};

class Exportador {
  public:
    virtual ~Exportador() = default;
    virtual void cabecera(std::ostream& salida) const = 0;
    virtual void fila(std::ostream& salida, const Producto& p) const = 0;
};

class ExportadorTexto : public Exportador {
  public:
    void cabecera(std::ostream& salida) const override {
        salida << "Producto         Unidades\n";
        salida << "---------------- --------\n";
    }

    void fila(std::ostream& salida, const Producto& p) const override {
        salida << std::format("{:<16} {:>8}\n", p.nombre, p.unidades);
    }
};

class ExportadorCsv : public Exportador {
  public:
    void cabecera(std::ostream& salida) const override {
        salida << "nombre,unidades\n";
    }

    void fila(std::ostream& salida, const Producto& p) const override {
        salida << campo(p.nombre) << ',' << p.unidades << '\n';
    }

  private:
    // Entrecomilla si hace falta y duplica las comillas interiores.
    static std::string campo(std::string_view texto) {
        if (texto.find_first_of(",\"\n") == std::string_view::npos) {
            return std::string{texto};
        }
        std::string resultado = "\"";
        for (char c : texto) {
            if (c == '"') {
                resultado += '"';
            }
            resultado += c;
        }
        return resultado + '"';
    }
};

void exportar(const std::vector<Producto>& productos,
              const Exportador& formato, std::ostream& salida) {
    formato.cabecera(salida);
    for (const Producto& p : productos) {
        formato.fila(salida, p);
    }
}

int main(int argc, char* argv[]) {
    const ExportadorTexto texto;
    const ExportadorCsv csv;

    std::string elegido;
    if (argc == 2) {
        elegido = argv[1];
    }
    const Exportador* formato = nullptr;
    if (elegido == "texto") {
        formato = &texto;
    } else if (elegido == "csv") {
        formato = &csv;
    } else {
        std::cerr << "Error: uso: 077 texto|csv.\n";
        return 1;
    }

    const std::vector<Producto> productos{
        {"Arandela", 250},
        {"Tornillo \"M3\"", 1200},
        {"Tuerca, 5 mm", 75},
    };
    exportar(productos, *formato, std::cout);
}
