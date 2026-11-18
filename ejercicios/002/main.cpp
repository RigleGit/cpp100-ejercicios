#include <iostream>
#include <string>

int main() {
    std::string nombre{"Ana"};
    int edad{19};
    double altura{1.68};
    bool estudia{true};
    auto curso{2};

    ++edad;

    std::cout << "Nombre: " << nombre << '\n';
    std::cout << "Edad: " << edad << '\n';
    std::cout << "Altura: " << altura << " m\n";
    std::cout << "Curso: " << curso << '\n';
    std::cout << "Estudia: " << std::boolalpha << estudia << '\n';
}
