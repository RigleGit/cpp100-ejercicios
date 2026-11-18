#ifndef FECHA_HPP
#define FECHA_HPP

#include <optional>
#include <string_view>

// Calendario gregoriano para los años 1 a 9999.
struct Fecha {
    int anio;
    int mes;
    int dia;
};

bool es_bisiesto(int anio);

// Devuelve 0 si el mes no está entre 1 y 12.
int dias_del_mes(int anio, int mes);

bool es_valida(const Fecha& fecha);

// Precondición: es_valida(fecha).
int dia_del_anio(const Fecha& fecha);

// Acepta exactamente el formato AAAA-MM-DD con una fecha válida.
std::optional<Fecha> leer_fecha(std::string_view texto);

#endif
