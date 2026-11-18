#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Alumno {
    std::string nombre;
    int nota{};
};

void mostrar(const std::vector<Alumno>& alumnos) {
    for (const Alumno& alumno : alumnos) {
        std::cout << "  " << alumno.nombre << ' ' << alumno.nota << '\n';
    }
}

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 0 || n > 1000) {
        std::cerr << "Error: escribe cuántos alumnos hay (de 0 a 1000).\n";
        return 1;
    }
    std::vector<Alumno> alumnos;
    for (int i = 0; i < n; ++i) {
        Alumno alumno;
        if (!(std::cin >> alumno.nombre >> alumno.nota) ||
            alumno.nota < 0 || alumno.nota > 10) {
            std::cerr << "Error: cada alumno lleva un nombre y una nota "
                         "de 0 a 10.\n";
            return 1;
        }
        alumnos.push_back(alumno);
    }

    std::sort(alumnos.begin(), alumnos.end(),
              [](const Alumno& a, const Alumno& b) {
                  if (a.nombre != b.nombre) {
                      return a.nombre < b.nombre;
                  }
                  return a.nota < b.nota;
              });
    std::cout << "Por nombre:\n";
    mostrar(alumnos);

    std::stable_sort(
        alumnos.begin(), alumnos.end(),
        [](const Alumno& a, const Alumno& b) { return a.nota > b.nota; });
    std::cout << "Por nota:\n";
    mostrar(alumnos);
}
