#include "fraccion.hpp"

#include <numeric>
#include <stdexcept>

Fraccion::Fraccion(long long numerador, long long denominador)
    : num_{numerador}, den_{denominador} {
    if (den_ == 0) {
        throw std::domain_error{"el denominador no puede ser cero"};
    }
    if (den_ < 0) {
        num_ = -num_;
        den_ = -den_;
    }
    const long long divisor = std::gcd(num_, den_);
    num_ /= divisor;
    den_ /= divisor;
}

long long Fraccion::numerador() const {
    return num_;
}

long long Fraccion::denominador() const {
    return den_;
}

Fraccion operator+(const Fraccion& a, const Fraccion& b) {
    return {a.numerador() * b.denominador() +
                b.numerador() * a.denominador(),
            a.denominador() * b.denominador()};
}

Fraccion operator-(const Fraccion& a, const Fraccion& b) {
    return a + Fraccion{-b.numerador(), b.denominador()};
}

Fraccion operator*(const Fraccion& a, const Fraccion& b) {
    return {a.numerador() * b.numerador(),
            a.denominador() * b.denominador()};
}

Fraccion operator/(const Fraccion& a, const Fraccion& b) {
    if (b.numerador() == 0) {
        throw std::domain_error{"división entre cero"};
    }
    return {a.numerador() * b.denominador(),
            a.denominador() * b.numerador()};
}

std::ostream& operator<<(std::ostream& salida, const Fraccion& f) {
    salida << f.numerador();
    if (f.denominador() != 1) {
        salida << '/' << f.denominador();
    }
    return salida;
}
