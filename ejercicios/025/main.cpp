#include <iostream>

struct Marcador {
    int local = 0;
    int visitante = 0;
};

bool es_equipo(char equipo) {
    return equipo == 'L' || equipo == 'V';
}

// Antes de llamarla, comprueba que equipo sea 'L' o 'V'.
int& puntos_de(Marcador& marcador, char equipo) {
    if (equipo == 'L') {
        return marcador.local;
    }
    return marcador.visitante;
}

int main() {
    Marcador marcador;
    char equipo{};
    while (std::cin >> equipo) {
        if (!es_equipo(equipo)) {
            std::cerr << "Error: equipo desconocido: " << equipo << '\n';
            return 1;
        }
        int puntos{};
        if (!(std::cin >> puntos)) {
            std::cerr << "Error: falta la puntuación entera.\n";
            return 1;
        }
        if (puntos < 1 || puntos > 3) {
            std::cerr << "Error: una canasta vale 1, 2 o 3 puntos.\n";
            return 1;
        }
        puntos_de(marcador, equipo) += puntos;
    }

    std::cout << "Local " << marcador.local << " - " << marcador.visitante
              << " Visitante\n";
}
