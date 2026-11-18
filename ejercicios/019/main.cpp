#include <iostream>

constexpr long long limite{1'000'000'000};

long long mcd(long long a, long long b) {
    while (b != 0) {
        long long resto{a % b};
        a = b;
        b = resto;
    }
    return a;
}

long long mcm(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return a / mcd(a, b) * b;
}

int main() {
    long long a{};
    long long b{};
    if (!(std::cin >> a >> b)) {
        std::cerr << "Error: se esperaban dos enteros.\n";
        return 1;
    }
    if (a < 0 || a > limite || b < 0 || b > limite) {
        std::cerr << "Error: los números deben estar entre 0 y " << limite
                  << ".\n";
        return 1;
    }
    std::cout << "MCD: " << mcd(a, b) << '\n';
    std::cout << "MCM: " << mcm(a, b) << '\n';
}
