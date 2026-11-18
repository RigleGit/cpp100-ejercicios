#include <iostream>

void intercambiar_copia(int a, int b) {
    int auxiliar = a;
    a = b;
    b = auxiliar;
}

void intercambiar(int& a, int& b) {
    int auxiliar = a;
    a = b;
    b = auxiliar;
}

int main() {
    int a{};
    int b{};
    if (!(std::cin >> a >> b)) {
        std::cerr << "Error: se esperaban dos enteros.\n";
        return 1;
    }

    std::cout << "Antes: a = " << a << ", b = " << b << '\n';
    intercambiar_copia(a, b);
    std::cout << "Tras intercambiar_copia: a = " << a << ", b = " << b
              << '\n';
    intercambiar(a, b);
    std::cout << "Tras intercambiar: a = " << a << ", b = " << b << '\n';
}
