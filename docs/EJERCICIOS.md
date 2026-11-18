# Índice de ejercicios de C++

Ejecuta las órdenes desde la raíz del repositorio, junto a este README. La tabla copia la orden de compilación de cada capítulo; después ejecuta `./programa` con los argumentos y las entradas del enunciado.

Los ejercicios 93, 94, 99 y 100 incluyen además un `pruebas.cpp`: el capítulo explica cómo compilarlo. Los ejercicios 95–97 usan hilos y se compilan con `-pthread`.

Este índice se genera desde el manifiesto del libro; no lo edites a mano.

## Bloque 1: Primeros programas

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 1 | Hola, C++ | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/001/main.cpp` | [main.cpp](../ejercicios/001/main.cpp) |
| 2 | Variables y tipos | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/002/main.cpp` | [main.cpp](../ejercicios/002/main.cpp) |
| 3 | Leer nombre y edad | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/003/main.cpp` | [main.cpp](../ejercicios/003/main.cpp) |
| 4 | Segundos a horas, minutos y segundos | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/004/main.cpp` | [main.cpp](../ejercicios/004/main.cpp) |
| 5 | Área y perímetro del círculo | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/005/main.cpp` | [main.cpp](../ejercicios/005/main.cpp) |
| 6 | Media de tres enteros | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/006/main.cpp` | [main.cpp](../ejercicios/006/main.cpp) |
| 7 | Precio con IVA | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/007/main.cpp` | [main.cpp](../ejercicios/007/main.cpp) |

## Bloque 2: Decisiones y bucles

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 8 | Par o impar y signo | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/008/main.cpp` | [main.cpp](../ejercicios/008/main.cpp) |
| 9 | Calificación a partir de una nota | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/009/main.cpp` | [main.cpp](../ejercicios/009/main.cpp) |
| 10 | Calculadora con `switch` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/010/main.cpp` | [main.cpp](../ejercicios/010/main.cpp) |
| 11 | Tabla de multiplicar | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/011/main.cpp` | [main.cpp](../ejercicios/011/main.cpp) |
| 12 | Sumar hasta un centinela | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/012/main.cpp` | [main.cpp](../ejercicios/012/main.cpp) |
| 13 | Adivinar un número secreto | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/013/main.cpp` | [main.cpp](../ejercicios/013/main.cpp) |
| 14 | Primos hasta n | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/014/main.cpp` | [main.cpp](../ejercicios/014/main.cpp) |

## Bloque 3: Funciones

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 15 | Máximo de dos números | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/015/main.cpp` | [main.cpp](../ejercicios/015/main.cpp) |
| 16 | Áreas con sobrecarga | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/016/main.cpp` | [main.cpp](../ejercicios/016/main.cpp) |
| 17 | Formatear un precio con argumentos por defecto | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/017/main.cpp` | [main.cpp](../ejercicios/017/main.cpp) |
| 18 | Factorial recursivo con límite | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/018/main.cpp` | [main.cpp](../ejercicios/018/main.cpp) |
| 19 | Máximo común divisor y mínimo común múltiplo | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/019/main.cpp` | [main.cpp](../ejercicios/019/main.cpp) |
| 20 | División con cociente y resto | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/020/main.cpp` | [main.cpp](../ejercicios/020/main.cpp) |
| 21 | Cálculos comprobados al compilar | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/021/main.cpp` | [main.cpp](../ejercicios/021/main.cpp) |

## Bloque 4: Referencias, punteros y `const`

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 22 | Intercambiar dos valores | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/022/main.cpp` | [main.cpp](../ejercicios/022/main.cpp) |
| 23 | Contar vocales sin copiar el texto | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/023/main.cpp` | [main.cpp](../ejercicios/023/main.cpp) |
| 24 | Buscar un valor con punteros | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/024/main.cpp` | [main.cpp](../ejercicios/024/main.cpp) |
| 25 | Devolver una referencia para modificar | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/025/main.cpp` | [main.cpp](../ejercicios/025/main.cpp) |
| 26 | Array de C y `std::array` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/026/main.cpp` | [main.cpp](../ejercicios/026/main.cpp) |
| 27 | Sumar un tramo con `std::span` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/027/main.cpp` | [main.cpp](../ejercicios/027/main.cpp) |

## Bloque 5: Texto con `std::string`

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 28 | Longitud, concatenación y comparación | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/028/main.cpp` | [main.cpp](../ejercicios/028/main.cpp) |
| 29 | Invertir una palabra y detectar palíndromos | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/029/main.cpp` | [main.cpp](../ejercicios/029/main.cpp) |
| 30 | Contar palabras por línea | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/030/main.cpp` | [main.cpp](../ejercicios/030/main.cpp) |
| 31 | Buscar y reemplazar | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/031/main.cpp` | [main.cpp](../ejercicios/031/main.cpp) |
| 32 | Leer líneas y recortar espacios | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/032/main.cpp` | [main.cpp](../ejercicios/032/main.cpp) |
| 33 | Convertir texto en número con `std::from_chars` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/033/main.cpp` | [main.cpp](../ejercicios/033/main.cpp) |
| 34 | Cifrado César | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/034/main.cpp` | [main.cpp](../ejercicios/034/main.cpp) |

## Bloque 6: `std::vector` y `std::array`

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 35 | Suma y media de n números | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/035/main.cpp` | [main.cpp](../ejercicios/035/main.cpp) |
| 36 | Mínimo y máximo | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/036/main.cpp` | [main.cpp](../ejercicios/036/main.cpp) |
| 37 | Crecer con `push_back` y `reserve` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/037/main.cpp` | [main.cpp](../ejercicios/037/main.cpp) |
| 38 | Eliminar un elemento por índice | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/038/main.cpp` | [main.cpp](../ejercicios/038/main.cpp) |
| 39 | Matriz traspuesta | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/039/main.cpp` | [main.cpp](../ejercicios/039/main.cpp) |
| 40 | Borrar mientras recorres | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/040/main.cpp` | [main.cpp](../ejercicios/040/main.cpp) |
| 41 | Búsqueda binaria | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/041/main.cpp` | [main.cpp](../ejercicios/041/main.cpp) |

## Bloque 7: Algoritmos, lambdas y rangos

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 42 | Ordenar con un comparador | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/042/main.cpp` | [main.cpp](../ejercicios/042/main.cpp) |
| 43 | Contar y buscar con un criterio | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/043/main.cpp` | [main.cpp](../ejercicios/043/main.cpp) |
| 44 | Transformar y acumular | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/044/main.cpp` | [main.cpp](../ejercicios/044/main.cpp) |
| 45 | Capturar por valor y por referencia | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/045/main.cpp` | [main.cpp](../ejercicios/045/main.cpp) |
| 46 | Rangos y vistas | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/046/main.cpp` | [main.cpp](../ejercicios/046/main.cpp) |
| 47 | Quitar duplicados | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/047/main.cpp` | [main.cpp](../ejercicios/047/main.cpp) |
| 48 | Una tabla de operaciones | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/048/main.cpp` | [main.cpp](../ejercicios/048/main.cpp) |

## Bloque 8: Contenedores asociativos

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 49 | Frecuencia de palabras | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/049/main.cpp` | [main.cpp](../ejercicios/049/main.cpp) |
| 50 | Votos con un map sin orden | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/050/main.cpp` | [main.cpp](../ejercicios/050/main.cpp) |
| 51 | Conjuntos e intersección | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/051/main.cpp` | [main.cpp](../ejercicios/051/main.cpp) |
| 52 | Agenda: buscar sin insertar | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/052/main.cpp` | [main.cpp](../ejercicios/052/main.cpp) |
| 53 | Agrupar por inicial | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/053/main.cpp` | [main.cpp](../ejercicios/053/main.cpp) |
| 54 | Agrupar anagramas | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/054/main.cpp` | [main.cpp](../ejercicios/054/main.cpp) |

## Bloque 9: Clases

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 55 | Un rectángulo con funciones miembro | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/055/main.cpp` | [main.cpp](../ejercicios/055/main.cpp) |
| 56 | Una fracción que siempre está normalizada | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/056/main.cpp` | [main.cpp](../ejercicios/056/main.cpp) |
| 57 | Funciones miembro `const` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/057/main.cpp` | [main.cpp](../ejercicios/057/main.cpp) |
| 58 | Operadores para la fracción | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/058/main.cpp` | [main.cpp](../ejercicios/058/main.cpp) |
| 59 | Identificadores consecutivos con `static` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/059/main.cpp` | [main.cpp](../ejercicios/059/main.cpp) |
| 60 | Una cuenta con historial | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/060/main.cpp` | [main.cpp](../ejercicios/060/main.cpp) |
| 61 | Ordenar versiones con `operator<=>` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/061/main.cpp` | [main.cpp](../ejercicios/061/main.cpp) |

## Bloque 10: RAII, memoria y movimiento

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 62 | Constructor y destructor con trazas | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/062/main.cpp` | [main.cpp](../ejercicios/062/main.cpp) |
| 63 | Envolver un `FILE*` de C | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/063/main.cpp` | [main.cpp](../ejercicios/063/main.cpp) |
| 64 | Lista enlazada con `std::unique_ptr` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/064/main.cpp` | [main.cpp](../ejercicios/064/main.cpp) |
| 65 | `std::shared_ptr` y `std::weak_ptr`: romper un ciclo | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/065/main.cpp` | [main.cpp](../ejercicios/065/main.cpp) |
| 66 | Regla de cinco: búfer con copia profunda | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/066/main.cpp` | [main.cpp](../ejercicios/066/main.cpp) |
| 67 | Semántica de movimiento con trazas | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/067/main.cpp` | [main.cpp](../ejercicios/067/main.cpp) |
| 68 | Regla de cero: el búfer con `std::vector` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/068/main.cpp` | [main.cpp](../ejercicios/068/main.cpp) |

## Bloque 11: Errores

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 69 | Lanzar y capturar excepciones estándar | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/069/main.cpp` | [main.cpp](../ejercicios/069/main.cpp) |
| 70 | Jerarquía de excepciones propias | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/070/main.cpp` | [main.cpp](../ejercicios/070/main.cpp) |
| 71 | Transferencias que no se quedan a medias | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/071/main.cpp` | [main.cpp](../ejercicios/071/main.cpp) |
| 72 | `std::optional` para búsquedas sin resultado | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/072/main.cpp` | [main.cpp](../ejercicios/072/main.cpp) |
| 73 | `std::variant` y `std::visit`: resultado o error | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/073/main.cpp` | [main.cpp](../ejercicios/073/main.cpp) |
| 74 | Validar un formulario y acumular los errores | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/074/main.cpp` | [main.cpp](../ejercicios/074/main.cpp) |

## Bloque 12: Herencia y polimorfismo

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 75 | Herencia simple: empleado y gerente | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/075/main.cpp` | [main.cpp](../ejercicios/075/main.cpp) |
| 76 | Funciones `virtual` y `override`: figuras | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/076/main.cpp` | [main.cpp](../ejercicios/076/main.cpp) |
| 77 | Clases abstractas: exportar a texto y a CSV | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/077/main.cpp` | [main.cpp](../ejercicios/077/main.cpp) |
| 78 | Destructor virtual y `std::vector<std::unique_ptr<Figura>>` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/078/main.cpp` | [main.cpp](../ejercicios/078/main.cpp) |
| 79 | Estrategias: herencia frente a lambdas | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/079/main.cpp` | [main.cpp](../ejercicios/079/main.cpp) |
| 80 | Polimorfismo cerrado con `std::variant` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/080/main.cpp` | [main.cpp](../ejercicios/080/main.cpp) |

## Bloque 13: Plantillas y conceptos

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 81 | Plantillas de función: `maximo<T>` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/081/main.cpp` | [main.cpp](../ejercicios/081/main.cpp) |
| 82 | Plantilla de clase: pila genérica | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/082/main.cpp` | [main.cpp](../ejercicios/082/main.cpp) |
| 83 | Conceptos estándar y `requires`: solo números | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/083/main.cpp` | [main.cpp](../ejercicios/083/main.cpp) |
| 84 | Concepto propio: tipos que se pueden imprimir | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/084/main.cpp` | [main.cpp](../ejercicios/084/main.cpp) |
| 85 | Plantillas variádicas y expresiones *fold* | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/085/main.cpp` | [main.cpp](../ejercicios/085/main.cpp) |
| 86 | `if constexpr`: describir un tipo al compilar | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/086/main.cpp` | [main.cpp](../ejercicios/086/main.cpp) |

## Bloque 14: Archivos y flujos

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 87 | Escribir un archivo con `std::ofstream` | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/087/main.cpp` | [main.cpp](../ejercicios/087/main.cpp) |
| 88 | Leer líneas y contarlas | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/088/main.cpp` | [main.cpp](../ejercicios/088/main.cpp) |
| 89 | CSV de notas con líneas mal formadas | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/089/main.cpp` | [main.cpp](../ejercicios/089/main.cpp) |
| 90 | Copiar un archivo binario y comprobar el tamaño | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/090/main.cpp` | [main.cpp](../ejercicios/090/main.cpp) |
| 91 | `std::filesystem`: listar un directorio ordenado | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/091/main.cpp` | [main.cpp](../ejercicios/091/main.cpp) |
| 92 | Guardar y recuperar un inventario | `g++ -std=c++20 -Wall -Wextra -o programa ejercicios/092/main.cpp` | [main.cpp](../ejercicios/092/main.cpp) |

## Bloque 15: Proyectos finales

| Nº | Ejercicio | Orden de compilación | Archivos |
|---:|---|---|---|
| 93 | Varios archivos: una biblioteca de fracciones | `g++ -std=c++20 -Wall -Wextra -I ejercicios/093 -o programa ejercicios/093/main.cpp ejercicios/093/fraccion.cpp` | [main.cpp](../ejercicios/093/main.cpp), [fraccion.cpp](../ejercicios/093/fraccion.cpp), [fraccion.hpp](../ejercicios/093/fraccion.hpp), [pruebas.cpp](../ejercicios/093/pruebas.cpp) |
| 94 | Pruebas con `assert` y un `CMakeLists.txt` mínimo | `g++ -std=c++20 -Wall -Wextra -I ejercicios/094 -o programa ejercicios/094/main.cpp ejercicios/094/fecha.cpp` | [main.cpp](../ejercicios/094/main.cpp), [fecha.cpp](../ejercicios/094/fecha.cpp), [fecha.hpp](../ejercicios/094/fecha.hpp), [pruebas.cpp](../ejercicios/094/pruebas.cpp), [CMakeLists.txt](../ejercicios/094/CMakeLists.txt) |
| 95 | `std::thread` y `join`: suma por tramos | `g++ -std=c++20 -Wall -Wextra -pthread -o programa ejercicios/095/main.cpp` | [main.cpp](../ejercicios/095/main.cpp) |
| 96 | `std::mutex` y `std::lock_guard`: contador compartido | `g++ -std=c++20 -Wall -Wextra -pthread -o programa ejercicios/096/main.cpp` | [main.cpp](../ejercicios/096/main.cpp) |
| 97 | `std::async` y futuros | `g++ -std=c++20 -Wall -Wextra -pthread -o programa ejercicios/097/main.cpp` | [main.cpp](../ejercicios/097/main.cpp) |
| 98 | Gestor de tareas I: añadir, listar y completar | `g++ -std=c++20 -Wall -Wextra -I ejercicios/098 -o programa ejercicios/098/main.cpp ejercicios/098/tareas.cpp` | [main.cpp](../ejercicios/098/main.cpp), [tareas.cpp](../ejercicios/098/tareas.cpp), [tareas.hpp](../ejercicios/098/tareas.hpp) |
| 99 | Gestor de tareas II: filtros, orden y errores de uso | `g++ -std=c++20 -Wall -Wextra -I ejercicios/099 -o programa ejercicios/099/main.cpp ejercicios/099/tareas.cpp ejercicios/099/vista.cpp` | [main.cpp](../ejercicios/099/main.cpp), [tareas.cpp](../ejercicios/099/tareas.cpp), [tareas.hpp](../ejercicios/099/tareas.hpp), [vista.cpp](../ejercicios/099/vista.cpp), [vista.hpp](../ejercicios/099/vista.hpp), [pruebas.cpp](../ejercicios/099/pruebas.cpp) |
| 100 | Calculadora de expresiones | `g++ -std=c++20 -Wall -Wextra -I ejercicios/100 -o programa ejercicios/100/main.cpp ejercicios/100/lexico.cpp ejercicios/100/arbol.cpp` | [main.cpp](../ejercicios/100/main.cpp), [arbol.cpp](../ejercicios/100/arbol.cpp), [arbol.hpp](../ejercicios/100/arbol.hpp), [lexico.cpp](../ejercicios/100/lexico.cpp), [lexico.hpp](../ejercicios/100/lexico.hpp), [pruebas.cpp](../ejercicios/100/pruebas.cpp) |
