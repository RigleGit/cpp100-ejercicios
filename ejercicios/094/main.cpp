#include "fecha.hpp"

#include <iostream>
#include <optional>
#include <string>

int main() {
    std::string linea;
    int numero = 0;
    bool hubo_errores = false;
    while (std::getline(std::cin, linea)) {
        ++numero;
        if (linea.empty()) {
            continue;
        }
        const std::optional<Fecha> fecha = leer_fecha(linea);
        if (!fecha) {
            std::cerr << "Error en la línea " << numero << ": '" << linea
                      << "' no es una fecha AAAA-MM-DD válida.\n";
            hubo_errores = true;
            continue;
        }
        std::cout << linea << ": día " << dia_del_anio(*fecha) << " de "
                  << (es_bisiesto(fecha->anio) ? 366 : 365) << '\n';
    }
    return hubo_errores ? 1 : 0;
}
