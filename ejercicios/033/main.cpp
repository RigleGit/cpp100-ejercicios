#include <charconv>
#include <iostream>
#include <string>
#include <system_error>

std::errc convertir(const std::string& texto, int& valor) {
    const char* inicio = texto.data();
    const char* fin = inicio + texto.size();
    auto [resto, error] = std::from_chars(inicio, fin, valor);
    if (error == std::errc{} && resto != fin) {
        return std::errc::invalid_argument;
    }
    return error;
}

int main() {
    std::string palabra;
    int validos = 0;
    long long suma = 0;
    while (std::cin >> palabra) {
        int valor{};
        const std::errc error = convertir(palabra, valor);
        std::cout << palabra << ": ";
        if (error == std::errc{}) {
            std::cout << valor << '\n';
            ++validos;
            suma += valor;
        } else if (error == std::errc::result_out_of_range) {
            std::cout << "fuera de rango\n";
        } else {
            std::cout << "no es un entero\n";
        }
    }
    std::cout << "Válidos: " << validos << '\n';
    std::cout << "Suma: " << suma << '\n';
}
