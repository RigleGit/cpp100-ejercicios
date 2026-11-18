#include <iostream>

int main() {
    int total{};
    std::cin >> total;
    int horas{total / 3600};
    int minutos{total % 3600 / 60};
    int segundos{total % 60};
    std::cout << total << " s = " << horas << " h " << minutos << " min "
              << segundos << " s\n";
}
