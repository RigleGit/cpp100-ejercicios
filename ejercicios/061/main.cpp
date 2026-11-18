#include <algorithm>
#include <charconv>
#include <compare>
#include <iostream>
#include <string>
#include <vector>

struct Version {
    unsigned mayor{};
    unsigned menor{};
    unsigned parche{};

    auto operator<=>(const Version&) const = default;
};

bool leerParte(const std::string& texto, unsigned& parte) {
    const char* inicio = texto.data();
    const char* fin = inicio + texto.size();
    auto [resto, error] = std::from_chars(inicio, fin, parte);
    return !texto.empty() && error == std::errc{} && resto == fin;
}

bool leerVersion(const std::string& texto, Version& version) {
    auto punto1 = texto.find('.');
    if (punto1 == std::string::npos) {
        return false;
    }
    auto punto2 = texto.find('.', punto1 + 1);
    if (punto2 == std::string::npos) {
        return false;
    }
    return leerParte(texto.substr(0, punto1), version.mayor) &&
           leerParte(texto.substr(punto1 + 1, punto2 - punto1 - 1),
                     version.menor) &&
           leerParte(texto.substr(punto2 + 1), version.parche);
}

std::ostream& operator<<(std::ostream& salida, const Version& v) {
    return salida << v.mayor << '.' << v.menor << '.' << v.parche;
}

int main() {
    std::vector<Version> versiones;
    std::string texto;
    while (std::cin >> texto) {
        Version v;
        if (!leerVersion(texto, v)) {
            std::cerr << "Error: versión no válida: " << texto << '\n';
            return 1;
        }
        versiones.push_back(v);
    }
    if (versiones.empty()) {
        std::cout << "Sin versiones.\n";
        return 0;
    }

    std::sort(versiones.begin(), versiones.end());
    for (const Version& v : versiones) {
        std::cout << v << '\n';
    }
    std::cout << "Más reciente: " << versiones.back() << '\n';
}
