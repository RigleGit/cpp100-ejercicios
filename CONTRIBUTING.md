# Contribuir a los ejercicios de C++

Antes de cambiar una solución, lee su enunciado y su contrato en el libro. Los primeros ejercicios trabajan con entradas válidas y valores pequeños: no añadas validación avanzada sin revisar qué concepto se está enseñando en ese bloque.

Si encuentras un fallo, guarda un caso pequeño con el número de ejercicio, la entrada, el resultado esperado y el obtenido. Incluye tu sistema operativo y la primera línea de `g++ --version` o `clang++ --version`. Abre una [incidencia](https://github.com/RigleGit/cpp100-ejercicios/issues) con esos datos. Para proponer una corrección, usa una rama de tu fork y un pull request que explique el problema y las comprobaciones que has ejecutado.

## Comprobar un cambio

Desde la raíz del repositorio:

```sh
python3 tools/verify.py
CXX=g++ python3 tools/verify.py
```

El verificador compila con avisos estrictos, `-Werror` y los sanitizers de direcciones y de comportamiento indefinido, comprueba el formato con `clang-format` si está instalado, ejecuta los casos de `casos.json` y, si existe, `pruebas.cpp`. Puedes limitarlo a un ejercicio (`001`) o a un rango (`093-100`).

Si añades un caso, debe describir un comportamiento observable del contrato. Comprueba primero que falla con la versión sin corregir y por el motivo esperado. Formatea el código con `clang-format -i` antes de enviarlo.

Los ejercicios con hilos (95–97) dependen del planificador: una ejecución correcta no demuestra que no haya carreras. Si los cambias, repítelos varias veces y, si tu compilador lo admite, compílalos con `-fsanitize=thread`.

## Correspondencia con el libro

Toda solución impresa debe coincidir byte a byte con sus archivos de este repositorio. Si cambias código, hay que actualizar también el listado del capítulo; el proyecto del libro lo comprueba automáticamente. El índice `docs/EJERCICIOS.md` se genera desde el manifiesto del libro: no lo edites a mano.

El código se distribuye bajo [MIT](LICENSE). Esta licencia corresponde a este repositorio y no cambia los derechos del texto del libro.
