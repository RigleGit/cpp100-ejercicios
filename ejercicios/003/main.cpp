#include <iostream>
#include <string>

int main() {
    std::string nombre;
    int edad{};
    std::cin >> nombre >> edad;
    std::cout << "Hola, " << nombre << ". El año que viene tendrás "
              << edad + 1 << " años.\n";
}
