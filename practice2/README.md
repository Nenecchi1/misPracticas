# Second Project

Este proyecto consiste en un programa en lenguaje C que permite a un usuario calcular el promedio de sus calificaciones. La característica principal es que el programa **no se sabe cuántas calificaciones se van a registrar**, por lo que solicita memoria dinámica conforme se ingresan nuevas calificaciones.

## Características

- Permite ingresar calificaciones una a una.
- Utiliza memoria dinámica (`Calloc` y `Realloc`) para almacenar las calificaciones.
- Calcula y muestra el promedio de todas las calificaciones ingresadas.
- No hay límite predefinido en el número de calificaciones; el usuario decide cuándo finalizar.

Antes de usar este proyecto, asegurate de tener lo siguiente:

- **Conocimientos básicos de programación en C.**
- Un compilador de C instalado en tu sistema:

  - [GCC](https://gcc.gnu.org/) (recomendado para Linux)

  - [MinGW](http://www.mingw.org/) o [TDM-GCC](https://jmeubank.github.io/tdm-gcc/) 
  
  (recomendado para Windows)
- Un editor de texto o entorno de desarrollo (VS Code, Vim, Notepad++,entre otros que soporten C y C++)

## Cómo compilar y ejecutar

1. Abre una terminal y navega a la carpeta donde está el archivo fuente (por ejemplo, `promedio_incremental.c`).
2. Ejecuta el siguiente comando para compilar:
   ```bash
   gcc -o promedio promedio_incremental.c
   ```
3. Ejecuta el programa:
   ```bash
   ./promedio
   ```
4. Si estas usando Windows Solo abre tu IDE y selecciona el archivo con el nombre que lo guardaste  y corre el programa 



