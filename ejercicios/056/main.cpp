#include <iostream>
#include <numeric>
#include <string>

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

    long long numerador() {
        return num_;
    }

    long long denominador() {
        return den_;
    }

    std::string texto() {
        return std::to_string(num_) + "/" + std::to_string(den_);
    }

  private:
    long long num_;
    long long den_;
};

int main() {
    long long a = 0;
    long long b = 0;
    if (!(std::cin >> a >> b) || a < -1000000 || a > 1000000 ||
        b < -1000000 || b > 1000000) {
        std::cerr << "Error: escribe numerador y denominador "
                     "(de -1000000 a 1000000).\n";
        return 1;
    }
    if (b == 0) {
        std::cerr << "Error: el denominador no puede ser cero.\n";
        return 1;
    }
    Fraccion f(a, b);
    std::cout << a << '/' << b << " = " << f.texto() << '\n';
    std::cout << "Numerador: " << f.numerador() << '\n';
    std::cout << "Denominador: " << f.denominador() << '\n';
}
