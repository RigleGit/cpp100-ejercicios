#ifndef FRACCION_HPP
#define FRACCION_HPP

#include <ostream>

// Fracción siempre normalizada: denominador positivo y sin factores
// comunes. Pensada para numeradores y denominadores de hasta 10^9 en
// valor absoluto; con valores mayores las operaciones pueden desbordar.
class Fraccion {
  public:
    Fraccion(long long numerador = 0, long long denominador = 1);

    long long numerador() const;
    long long denominador() const;

    bool operator==(const Fraccion&) const = default;

  private:
    long long num_;
    long long den_;
};

Fraccion operator+(const Fraccion& a, const Fraccion& b);
Fraccion operator-(const Fraccion& a, const Fraccion& b);
Fraccion operator*(const Fraccion& a, const Fraccion& b);
Fraccion operator/(const Fraccion& a, const Fraccion& b);

std::ostream& operator<<(std::ostream& salida, const Fraccion& f);

#endif
