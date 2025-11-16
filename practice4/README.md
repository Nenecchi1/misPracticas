# Sistema básico de gestión de estudiantes (C - estructuras con punteros)

Descripción
-----------
Proyecto de ejemplo en C que implementa un sistema básico de gestión de estudiantes usando estructuras y punteros. Permite almacenar información académica de los estudiantes, realizar operaciones simples (cálculo de promedio, búsqueda, listado) y demostrar el uso de memoria dinámica y punteros a estructuras.

Objetivos
---------
- Practicar el uso de estructuras (struct) en C.
- Manejar memoria dinámica con malloc/free para almacenar registros de estudiantes.
- Usar punteros a estructuras para enlazar operaciones y (opcional) formar una lista enlazada simple.
- Implementar cálculos simples (promedio, estado por nota).
- Proveer una interfaz de consola simple para probar las funcionalidades.

Características
---------------
- Estructuras para representar a un Estudiante y su información académica.
- Almacenamiento dinámico (array dinámico o lista enlazada) usando punteros.
- Funciones para:
  - Crear y liberar estudiantes.
  - Mostrar todos los estudiantes.
  - Calcular promedio y estado académico (aprobado/reprobado).

  Requisitos
----------
- Compilador C compatible (gcc, clang).
- Sistema operativo: Linux / macOS / Windows (con MinGW o similar).
- Make (opcional).

Compilación
-----------
Ejemplo usando gcc:

```bash
gcc -std=c11 -Wall -Wextra -pedantic -o gestion_estudiantes main.c estudiantes.c utils.c
```

Si usas un solo archivo `main.c`:

```bash
gcc -std=c11 -Wall -Wextra -pedantic -o gestion_estudiantes main.c
```

Ejecución
---------
```bash
./gestion_estudiantes
```

### Opción 2: Windows con Visual Studio (MSVC - cl)

Abre **Developer Command Prompt for VS** y ejecuta:

```cmd
cl /Fe:gestion_estudiantes.exe main.c
gestion_estudiantes.exe
```





