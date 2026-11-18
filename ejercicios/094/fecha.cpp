#include "fecha.hpp"

bool es_bisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

int dias_del_mes(int anio, int mes) {
    switch (mes) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return es_bisiesto(anio) ? 29 : 28;
    default:
        return 0;
    }
}

bool es_valida(const Fecha& fecha) {
    return fecha.anio >= 1 && fecha.anio <= 9999 && fecha.dia >= 1 &&
           fecha.dia <= dias_del_mes(fecha.anio, fecha.mes);
}

int dia_del_anio(const Fecha& fecha) {
    int dias = fecha.dia;
    for (int mes = 1; mes < fecha.mes; ++mes) {
        dias += dias_del_mes(fecha.anio, mes);
    }
    return dias;
}

namespace {

std::optional<int> cifras(std::string_view texto) {
    int valor = 0;
    for (char c : texto) {
        if (c < '0' || c > '9') {
            return std::nullopt;
        }
        valor = valor * 10 + (c - '0');
    }
    return valor;
}

} // namespace

std::optional<Fecha> leer_fecha(std::string_view texto) {
    if (texto.size() != 10 || texto[4] != '-' || texto[7] != '-') {
        return std::nullopt;
    }
    const auto anio = cifras(texto.substr(0, 4));
    const auto mes = cifras(texto.substr(5, 2));
    const auto dia = cifras(texto.substr(8, 2));
    if (!anio || !mes || !dia) {
        return std::nullopt;
    }
    const Fecha fecha{*anio, *mes, *dia};
    if (!es_valida(fecha)) {
        return std::nullopt;
    }
    return fecha;
}
