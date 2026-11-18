#include <cstdlib>
#include <iostream>
#include <string>

class Traza {
  public:
    explicit Traza(const std::string& nombre) : nombre_{nombre} {
        std::cout << "Construye " << nombre_ << '\n';
    }

    ~Traza() {
        std::cout << "Destruye " << nombre_ << '\n';
    }

    Traza(const Traza&) = delete;
    Traza& operator=(const Traza&) = delete;

  private:
    std::string nombre_;
};

struct Pareja {
    Traza primero{"pareja.primero"};
    Traza segundo{"pareja.segundo"};
};

int main(int argc, char* argv[]) {
    std::string modo{"normal"};
    if (argc == 2) {
        modo = argv[1];
    }
    if (argc > 2 ||
        (modo != "normal" && modo != "return" && modo != "exit")) {
        std::cerr << "Error: uso: 062 [normal|return|exit].\n";
        return 1;
    }

    Traza a{"a"};
    {
        Traza b{"b"};
        Traza c{"c"};
        std::cout << "Fin del bloque interior\n";
    }
    Pareja pareja;

    if (modo == "return") {
        std::cout << "Sale con return\n";
        return 0;
    }
    if (modo == "exit") {
        std::cout << "Sale con std::exit\n";
        std::exit(0);
    }
    std::cout << "Fin de main\n";
}
