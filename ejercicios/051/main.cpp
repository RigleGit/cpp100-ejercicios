#include <iostream>
#include <set>
#include <sstream>
#include <string>

bool leerConjunto(std::set<int>& conjunto) {
    std::string texto;
    if (!std::getline(std::cin, texto)) {
        return false;
    }
    std::istringstream linea(texto);
    while (linea >> std::ws && !linea.eof()) {
        int numero = 0;
        if (!(linea >> numero)) {
            return false;
        }
        conjunto.insert(numero);
    }
    return true;
}

void mostrar(const std::string& etiqueta, const std::set<int>& conjunto) {
    std::cout << etiqueta << ':';
    if (conjunto.empty()) {
        std::cout << " (vacío)";
    }
    for (int numero : conjunto) {
        std::cout << ' ' << numero;
    }
    std::cout << '\n';
}

int main() {
    std::set<int> a;
    std::set<int> b;
    if (!leerConjunto(a) || !leerConjunto(b)) {
        std::cerr << "Error: escribe dos líneas de números enteros.\n";
        return 1;
    }

    std::set<int> comunes;
    for (int numero : a) {
        if (b.contains(numero)) {
            comunes.insert(numero);
        }
    }

    mostrar("A", a);
    mostrar("B", b);
    mostrar("Comunes", comunes);
}
