#include <concepts>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
concept EsVector = requires { typename T::value_type; } &&
                   std::same_as<T, std::vector<typename T::value_type>>;

template <typename T> std::string describir() {
    if constexpr (std::same_as<T, bool>) {
        return "booleano";
    } else if constexpr (std::integral<T>) {
        const std::string signo =
            std::signed_integral<T> ? "con signo" : "sin signo";
        return "entero " + signo + " de " + std::to_string(sizeof(T)) +
               " bytes";
    } else if constexpr (std::floating_point<T>) {
        return "decimal de " + std::to_string(sizeof(T)) + " bytes";
    } else if constexpr (std::same_as<T, std::string>) {
        return "texto";
    } else if constexpr (EsVector<T>) {
        return "vector de " + describir<typename T::value_type>();
    } else {
        return "tipo sin descripción";
    }
}

template <typename T> std::string describir(const T&) {
    return describir<T>();
}

struct Punto {
    int x;
    int y;
};

int main() {
    const std::vector<std::vector<double>> matriz{{1.0, 2.0}, {3.0, 4.0}};
    std::cout << "bool: " << describir<bool>() << '\n';
    std::cout << "int: " << describir<int>() << '\n';
    std::cout << "std::uint16_t: " << describir<std::uint16_t>() << '\n';
    std::cout << "std::int64_t: " << describir<std::int64_t>() << '\n';
    std::cout << "double: " << describir<double>() << '\n';
    std::cout << "std::string: " << describir<std::string>() << '\n';
    std::cout << "std::vector<int>: " << describir<std::vector<int>>()
              << '\n';
    std::cout << "matriz: " << describir(matriz) << '\n';
    std::cout << "Punto: " << describir(Punto{1, 2}) << '\n';
}
