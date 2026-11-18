# Verificación de los ejercicios de C++

## Publicación del código — 18 de noviembre de 2026

Repositorio público: https://github.com/RigleGit/cpp100-ejercicios. Publicado por indicación del autor. Comprende los cien ejercicios, el verificador, el Dockerfile, el índice generado desde el manifiesto del libro, la licencia MIT y un workflow para Ubuntu y macOS. El manuscrito y su publicación se gestionan por separado; el libro sigue en revisión.

Resultados locales antes de la subida, sobre el mismo código que se publica:

- `python3 tools/verify.py` en macOS 27.2 ARM64 con Apple clang 21.0.0 y clang-format 23.1.6: 100 ejercicios, 678 casos, 0 fallos. Incluye `-Wpedantic -Werror`, AddressSanitizer, UndefinedBehaviorSanitizer, formato y los cuatro `pruebas.cpp` (93, 94, 99 y 100).
- La imagen del `Dockerfile` en Linux ARM64 con GCC 14.4.0 y clang-format 19.1.7: 100 ejercicios, 678 casos, 0 fallos.
- Ejercicios 95–97 compilados con `-fsanitize=thread` (Apple clang 21) y ejecutados cinco veces con cada caso de `casos.json`: 90 ejecuciones sin informes de ThreadSanitizer. Una ejecución limpia solo cubre los caminos observados; no demuestra que no haya carreras.

`verify.py` desactiva LeakSanitizer (`detect_leaks=0`): el ejercicio 65 provoca una fuga a propósito en uno de sus modos, como explica el libro.

No se ha ejecutado en Windows. El [workflow](https://github.com/RigleGit/cpp100-ejercicios/actions) muestra el estado remoto de cada commit; los resultados de arriba son locales y no se presentan como resultados de GitHub.
