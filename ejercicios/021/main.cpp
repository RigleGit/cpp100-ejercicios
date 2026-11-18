#include <iostream>

constexpr bool es_bisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

constexpr int dias_del_mes(int mes, int anio) {
    switch (mes) {
    case 2:
        if (es_bisiesto(anio)) {
            return 29;
        }
        return 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

constexpr int dias_del_anio(int anio) {
    int total{0};
    for (int mes{1}; mes <= 12; ++mes) {
        total += dias_del_mes(mes, anio);
    }
    return total;
}

static_assert(es_bisiesto(2024));
static_assert(es_bisiesto(2000));
static_assert(!es_bisiesto(1900));
static_assert(dias_del_mes(2, 2023) == 28);
static_assert(dias_del_anio(2023) == 365);
static_assert(dias_del_anio(2024) == 366);

int main() {
    int anio{};
    int mes{};
    if (!(std::cin >> anio >> mes)) {
        std::cerr << "Error: se esperaban el año y el mes.\n";
        return 1;
    }
    if (anio < 1 || anio > 9999) {
        std::cerr << "Error: el año debe estar entre 1 y 9999.\n";
        return 1;
    }
    if (mes < 1 || mes > 12) {
        std::cerr << "Error: el mes debe estar entre 1 y 12.\n";
        return 1;
    }
    std::cout << "El mes " << mes << " de " << anio << " tiene "
              << dias_del_mes(mes, anio) << " días.\n";
    std::cout << "El año " << anio << " tiene " << dias_del_anio(anio)
              << " días.\n";
}
