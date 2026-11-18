#include <iostream>
#include <numeric>

class Fraccion {
  public:
    // Requisito: denominador distinto de cero.
    Fraccion(long long numerador, long long denominador)
        : num_{numerador}, den_{denominador} {
        if (den_ < 0) {
            num_ = -num_;
            den_ = -den_;
        }
        long long divisor = std::gcd(num_, den_);
        num_ /= divisor;
        den_ /= divisor;
    }

    long long numerador() const {
        return num_;
    }

    long long denominador() const {
        return den_;
    }

    bool operator==(const Fraccion& otra) const {
        return num_ == otra.num_ && den_ == otra.den_;
    }

  private:
    long long num_;
    long long den_;
};

Fraccion operator+(const Fraccion& a, const Fraccion& b) {
    return Fraccion(a.numerador() * b.denominador() +
                        b.numerador() * a.denominador(),
                    a.denominador() * b.denominador());
}

std::ostream& operator<<(std::ostream& salida, const Fraccion& f) {
    return salida << f.numerador() << '/' << f.denominador();
}

bool en_rango(long long x) {
    return x >= -1000000 && x <= 1000000;
}

int main() {
    long long a = 0;
    long long b = 0;
    long long c = 0;
    long long d = 0;
    if (!(std::cin >> a >> b >> c >> d) || !en_rango(a) || !en_rango(b) ||
        !en_rango(c) || !en_rango(d)) {
        std::cerr << "Error: escribe dos fracciones como cuatro enteros "
                     "(de -1000000 a 1000000).\n";
        return 1;
    }
    if (b == 0 || d == 0) {
        std::cerr << "Error: el denominador no puede ser cero.\n";
        return 1;
    }
    Fraccion x(a, b);
    Fraccion y(c, d);
    std::cout << x << " + " << y << " = " << x + y << '\n';
    std::cout << x << " == " << y << ": " << (x == y ? "sí" : "no") << '\n';
}
