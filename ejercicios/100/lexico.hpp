#ifndef LEXICO_HPP
#define LEXICO_HPP

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

enum class TipoToken { numero, mas, menos, por, entre, abre, cierra, fin };

struct Token {
    TipoToken tipo;
    double valor;        // solo para TipoToken::numero
    std::size_t columna; // posición en bytes, empezando por 1
};

class ErrorExpresion : public std::runtime_error {
  public:
    ErrorExpresion(std::size_t columna, const std::string& mensaje);
    std::size_t columna() const;

  private:
    std::size_t columna_;
};

// Divide el texto en tokens. El último siempre es TipoToken::fin.
// Los números son cifras con una parte decimal opcional: 12, 0.5.
std::vector<Token> tokenizar(std::string_view texto);

#endif
