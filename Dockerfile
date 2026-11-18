# Verificación con GCC 14: compila cada ejercicio con los avisos y sanitizers
# de tools/verify.py, comprueba el formato y ejecuta sus casos.
FROM gcc:14
RUN apt-get update \
    && apt-get install -y --no-install-recommends python3 clang-format \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --create-home --shell /bin/bash developer
ENV CXX=g++
WORKDIR /workspace
USER developer
ENTRYPOINT ["python3", "tools/verify.py"]
