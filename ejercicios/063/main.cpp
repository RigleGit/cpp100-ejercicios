#include <cstdio>
#include <iostream>

class Archivo {
  public:
    Archivo(const char* ruta, const char* modo)
        : f_{std::fopen(ruta, modo)} {}

    ~Archivo() {
        if (f_ != nullptr) {
            std::fclose(f_);
        }
    }

    Archivo(const Archivo&) = delete;
    Archivo& operator=(const Archivo&) = delete;

    bool abierto() const {
        return f_ != nullptr;
    }

    std::FILE* get() const {
        return f_;
    }

    // Cierra a propósito para poder comprobar el resultado.
    bool cerrar() {
        int resultado = std::fclose(f_);
        f_ = nullptr;
        return resultado == 0;
    }

  private:
    std::FILE* f_;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: uso: 063 ORIGEN DESTINO.\n";
        return 1;
    }

    Archivo origen{argv[1], "rb"};
    if (!origen.abierto()) {
        std::cerr << "Error: no se puede abrir " << argv[1] << ".\n";
        return 1;
    }
    Archivo destino{argv[2], "wb"};
    if (!destino.abierto()) {
        std::cerr << "Error: no se puede crear " << argv[2] << ".\n";
        return 1;
    }

    long bytes = 0;
    int c;
    while ((c = std::fgetc(origen.get())) != EOF) {
        if (std::fputc(c, destino.get()) == EOF) {
            std::cerr << "Error: no se puede escribir en " << argv[2]
                      << ".\n";
            return 1;
        }
        ++bytes;
    }
    if (std::ferror(origen.get()) != 0) {
        std::cerr << "Error: no se puede leer " << argv[1] << ".\n";
        return 1;
    }
    if (!destino.cerrar()) {
        std::cerr << "Error: no se puede cerrar " << argv[2] << ".\n";
        return 1;
    }
    std::cout << "Copiados " << bytes << " bytes\n";
}
