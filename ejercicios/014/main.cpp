#include <iostream>

constexpr int limite{1000};

int main() {
    int n{};
    if (!(std::cin >> n)) {
        std::cerr << "Error: se esperaba un entero.\n";
        return 1;
    }
    if (n > limite) {
        std::cerr << "Error: n no puede superar " << limite << ".\n";
        return 1;
    }

    int total{0};
    std::cout << "Primos hasta " << n << ":";
    for (int candidato{2}; candidato <= n; ++candidato) {
        if (candidato > 2 && candidato % 2 == 0) {
            continue;
        }
        bool es_primo{true};
        for (int divisor{3}; divisor * divisor <= candidato; divisor += 2) {
            if (candidato % divisor == 0) {
                es_primo = false;
                break;
            }
        }
        if (es_primo) {
            std::cout << ' ' << candidato;
            ++total;
        }
    }
    if (total == 0) {
        std::cout << " ninguno";
    }
    std::cout << "\nTotal: " << total << '\n';
}
