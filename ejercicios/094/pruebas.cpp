#ifdef NDEBUG
#error "Compila las pruebas sin NDEBUG: assert no comprobaría nada."
#endif

#include "fecha.hpp"

#include <cassert>
#include <iostream>

int main() {
    // Años bisiestos: cada 4, salvo los centenarios no divisibles
    // entre 400.
    assert(es_bisiesto(2024));
    assert(!es_bisiesto(2023));
    assert(!es_bisiesto(1900));
    assert(es_bisiesto(2000));

    // Días del mes, con febrero como caso especial.
    assert(dias_del_mes(2023, 2) == 28);
    assert(dias_del_mes(2024, 2) == 29);
    assert(dias_del_mes(2024, 4) == 30);
    assert(dias_del_mes(2024, 12) == 31);
    assert(dias_del_mes(2024, 13) == 0);
    assert(dias_del_mes(2024, 0) == 0);

    // Validez en los bordes.
    assert(es_valida({2024, 2, 29}));
    assert(!es_valida({2023, 2, 29}));
    assert(!es_valida({2024, 4, 31}));
    assert(!es_valida({2024, 1, 0}));
    assert(!es_valida({0, 1, 1}));
    assert(es_valida({9999, 12, 31}));

    // Día del año.
    assert(dia_del_anio({2024, 1, 1}) == 1);
    assert(dia_del_anio({2024, 3, 1}) == 61);
    assert(dia_del_anio({2023, 3, 1}) == 60);
    assert(dia_del_anio({2024, 12, 31}) == 366);

    // Lectura del texto.
    assert(leer_fecha("2024-03-01").has_value());
    assert(leer_fecha("2024-03-01")->dia == 1);
    assert(!leer_fecha("2024-3-1"));
    assert(!leer_fecha("2024/03/01"));
    assert(!leer_fecha("2024-02-30"));
    assert(!leer_fecha("20a4-01-01"));
    assert(!leer_fecha(""));

    std::cout << "Pruebas de fechas superadas.\n";
}
