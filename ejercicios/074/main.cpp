#include <cctype>
#include <charconv>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct Formulario {
    std::string nombre;
    std::string email;
    std::string edad;
    std::string clave;
};

bool nombre_valido(std::string_view nombre) noexcept {
    return !nombre.empty() && nombre.size() <= 40;
}

bool email_valido(std::string_view email) noexcept {
    auto arroba = email.find('@');
    if (arroba == std::string_view::npos || arroba == 0 ||
        email.find('@', arroba + 1) != std::string_view::npos) {
        return false;
    }
    std::string_view dominio = email.substr(arroba + 1);
    auto punto = dominio.find('.');
    return punto != std::string_view::npos && punto > 0 &&
           punto + 1 < dominio.size();
}

bool edad_valida(std::string_view texto) noexcept {
    int edad = 0;
    auto [fin, error] =
        std::from_chars(texto.data(), texto.data() + texto.size(), edad);
    return !texto.empty() && error == std::errc{} &&
           fin == texto.data() + texto.size() && edad >= 18 && edad <= 120;
}

bool clave_valida(std::string_view clave) noexcept {
    bool letra = false;
    bool cifra = false;
    for (char c : clave) {
        auto u = static_cast<unsigned char>(c);
        letra = letra || std::isalpha(u) != 0;
        cifra = cifra || std::isdigit(u) != 0;
    }
    return clave.size() >= 8 && letra && cifra;
}

// No es noexcept: push_back puede necesitar memoria.
std::vector<std::string> validar(const Formulario& f) {
    std::vector<std::string> errores;
    if (!nombre_valido(f.nombre)) {
        errores.push_back("nombre: entre 1 y 40 bytes");
    }
    if (!email_valido(f.email)) {
        errores.push_back("email: forma usuario@dominio.ext");
    }
    if (!edad_valida(f.edad)) {
        errores.push_back("edad: entero entre 18 y 120");
    }
    if (!clave_valida(f.clave)) {
        errores.push_back("clave: 8 caracteres o más, letras y cifras");
    }
    return errores;
}

int main() {
    Formulario f;
    std::getline(std::cin, f.nombre);
    std::getline(std::cin, f.email);
    std::getline(std::cin, f.edad);
    std::getline(std::cin, f.clave);

    std::vector<std::string> errores = validar(f);
    if (errores.empty()) {
        std::cout << "Formulario correcto\n";
        return 0;
    }
    std::cerr << "Errores: " << errores.size() << '\n';
    for (const std::string& e : errores) {
        std::cerr << "- " << e << '\n';
    }
    return 1;
}
