#include <charconv>
#include <iostream>
#include <string>
#include <system_error>

bool leerEntero(const std::string& texto, int& valor) {
    const char* fin = texto.data() + texto.size();
    auto [resto, error] = std::from_chars(texto.data(), fin, valor);
    return error == std::errc{} && resto == fin;
}

char desplazar(char c, int desplazamiento) {
    if (c >= 'a' && c <= 'z') {
        return static_cast<char>('a' + (c - 'a' + desplazamiento) % 26);
    }
    if (c >= 'A' && c <= 'Z') {
        return static_cast<char>('A' + (c - 'A' + desplazamiento) % 26);
    }
    return c;
}

std::string cifrar(const std::string& texto, int desplazamiento) {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = desplazar(c, desplazamiento);
    }
    return resultado;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: indica el desplazamiento como único "
                     "argumento.\n";
        return 1;
    }
    int desplazamiento{};
    if (!leerEntero(argv[1], desplazamiento)) {
        std::cerr << "Error: el desplazamiento debe ser un entero.\n";
        return 1;
    }
    const int normalizado = (desplazamiento % 26 + 26) % 26;

    std::string linea;
    while (std::getline(std::cin, linea)) {
        std::cout << cifrar(linea, normalizado) << '\n';
    }
}
