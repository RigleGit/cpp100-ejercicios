# Aprende C++ paso a paso: 100 ejercicios resueltos

Repositorio de código que acompaña al volumen 3 de **Programación práctica**, de Rodrigo Iglesias. Contiene cien ejercicios de C++20 en quince bloques, desde el primer programa hasta referencias, `std::vector`, algoritmos, clases, RAII, excepciones, plantillas, archivos, pruebas e hilos, y dos proyectos finales: un gestor de tareas y una calculadora de expresiones. No necesitas haber leído otros volúmenes de la colección.

Empieza por el [índice de ejercicios](docs/EJERCICIOS.md). Cada entrada enlaza todos los archivos del ejercicio y copia la orden de compilación que usa el libro. Las soluciones corresponden al manuscrito en revisión; el libro todavía no se ha publicado.

## Empezar

Necesitas un compilador de C++20: GCC 13 o posterior, o Clang 17 o posterior. En macOS sirve el Clang de las herramientas de línea de órdenes de Xcode (`xcode-select --install`). Las soluciones usan solo la biblioteca estándar.

```sh
git clone https://github.com/RigleGit/cpp100-ejercicios.git
cd cpp100-ejercicios
g++ --version
g++ -std=c++20 -Wall -Wextra -o programa ejercicios/001/main.cpp
./programa
```

El programa muestra `¡Hola, C++!`. Si usas Clang, cambia `g++` por `clang++`; las opciones son las mismas. Las órdenes parten de la raíz del repositorio.

## Cómo practicar

1. Lee el enunciado e intenta resolverlo antes de consultar la solución.
2. Usa entradas del dominio indicado. En los primeros bloques se trabaja con datos válidos y pequeños; la validación llega cuando el libro ha presentado las herramientas para hacerla.
3. Sigue los valores con un ejemplo conocido y compara tu resultado con la explicación.
4. Conserva tus intentos en una copia o una rama antes de modificar una solución de referencia.
5. Ejecuta las comprobaciones del ejercicio. Que funcione con algunos casos no demuestra que funcione con todos.

Un reto «Un paso más» amplía el contrato del ejemplo: si lo implementas, añade a `casos.json` un caso con el comportamiento nuevo y comprueba que los anteriores siguen pasando.

## Organización

```text
cpp100-ejercicios/
  .clang-format
  ejercicios/
    001/
      main.cpp
      casos.json
    ...
  tools/
    verify.py
```

Cada carpeta numerada es un programa independiente. `main.cpp` es el punto de entrada; si el ejercicio reparte el código en varios archivos, los demás `.cpp` y las cabeceras `.hpp` están en la misma carpeta y se compilan juntos. Los ejercicios 93, 94, 99 y 100 tienen además un `pruebas.cpp` con comprobaciones escritas con `assert`, y el 94 incluye un `CMakeLists.txt` mínimo. Los ejercicios 95–97 usan hilos y se compilan con `-pthread`.

`casos.json` describe con qué se ejecuta el programa y qué debe producir: argumentos (`args`), entrada estándar (`stdin`), estado de salida (`status`), salida exacta (`stdout`), mensaje de error (`stderr` o `stderr_contains`) y, en los ejercicios de archivos, los archivos de partida (`files`) y los que deben quedar (`expect_files`).

## Comprobar con el verificador

`tools/verify.py` necesita Python 3 y un compilador de C++20 en **macOS o Linux**. Comprueba un ejercicio, un rango o todos:

```sh
python3 tools/verify.py 001
python3 tools/verify.py 001-007
python3 tools/verify.py
```

Compila cada ejercicio con `-std=c++20 -Wall -Wextra -Wpedantic -Werror` y los sanitizers de direcciones y de comportamiento indefinido, lo ejecuta con cada caso de `casos.json` en una carpeta temporal y compara estado, salida y archivos. Si existe `pruebas.cpp`, lo compila con los `.cpp` del ejercicio que no son `main.cpp` y exige que termine con estado 0. Si tienes `clang-format`, comprueba también el formato definido en `.clang-format`; si no, avisa y sigue.

Por defecto llama al compilador con `c++`. Para elegir uno:

```sh
CXX=g++ python3 tools/verify.py 001
CXX=clang++ python3 tools/verify.py 001
```

Los sanitizers dependen de que tu compilador y tu sistema los admitan. En Windows puedes compilar cada ejercicio con la orden del libro y comparar la salida a mano, o usar un entorno Linux como WSL o Docker.

## Docker

Puedes verificar con GCC 14 sin instalarlo:

```sh
docker build -t cpp100-ejercicios .
docker run --rm -v "${PWD}:/workspace:ro" cpp100-ejercicios
docker run --rm -v "${PWD}:/workspace:ro" cpp100-ejercicios 001-008
```

La imagen contiene GCC 14, `clang-format` y Python 3, y ejecuta el verificador con un usuario sin privilegios. El código se monta solo para lectura; los binarios y temporales quedan dentro del contenedor, que se elimina al terminar. La versión de `clang-format` de la imagen puede no coincidir con la tuya: si discrepan en un archivo, manda la que se usó para formatear el código.

Para practicar dentro del contenedor:

```sh
docker run --rm -it -v "${PWD}:/workspace:ro" --entrypoint bash cpp100-ejercicios
```

Como la carpeta es de solo lectura, compila con `-o /tmp/programa` y ejecuta `/tmp/programa`.

## Recorrido y correspondencia con el libro

Las carpetas `ejercicios/001` a `ejercicios/100` conservan la numeración técnica; en el libro, los títulos usan 1–100. El [índice](docs/EJERCICIOS.md) muestra los quince bloques. El manifiesto de los ejercicios se mantiene en el proyecto del libro y el índice se genera desde él.

## Estado

Los cien ejercicios están escritos, revisados y sincronizados con el manuscrito. El [registro de verificación](VERIFICACION.md) documenta los resultados locales y las versiones usadas.

El workflow de [GitHub Actions](https://github.com/RigleGit/cpp100-ejercicios/actions) comprueba los ejercicios en Ubuntu con GCC 14 y en macOS con Apple Clang. Consulta allí el resultado de cada commit; la configuración del workflow no es una prueba superada.

El código está disponible sin registro. Puedes descargarlo desde **Code → Download ZIP** o clonarlo con Git. Para recibir avisos, usa **Watch** en GitHub.

Para comunicar un fallo, abre una [incidencia](https://github.com/RigleGit/cpp100-ejercicios/issues) con el número del ejercicio, la entrada, la salida esperada, la obtenida, tu sistema operativo y la primera línea de `g++ --version` o `clang++ --version`. Usa un ejemplo pequeño y no incluyas datos personales.

## Contribuir y licencia

Consulta [CONTRIBUTING.md](CONTRIBUTING.md). Si cambias una solución, debe seguir coincidiendo con su listado y su contrato en el libro.

El código se distribuye bajo la [licencia MIT](LICENSE). Esta licencia no se aplica al texto del libro.
