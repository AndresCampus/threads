
# Comparación entre Procesos y Hilos

Este repositorio contiene varios programas en C diseñados para comparar el rendimiento de la creación de procesos mediante `fork()` frente a la creación de hilos (`pthread`). El objetivo es explorar cómo estos mecanismos de concurrencia afectan al rendimiento en aplicaciones de múltiples tareas y cómo la paralelización con hilos y OpenMP puede optimizar el tiempo de ejecución en comparación con la ejecución secuencial.

## Contenido del repositorio

### 1. Comparación de tiempos de creación
Se incluyen dos programas que miden el tiempo necesario para crear múltiples instancias utilizando:
- **Procesos** (`fork`): `crear_procesos.c`
- **Hilos** (`pthread`): `crear_hilos.c`

Estos programas permiten analizar la eficiencia de cada método en términos de tiempo de ejecución. **Para medir los tiempos, ejecuta los programas usando `time` en la línea de comandos**.

### 2. Ejecución en paralelo con hilos
Existen tres programas adicionales que ilustran la ejecución en paralelo:
- **Implementación con pthreads**: `analiza_secuencia_hilos.c`
- **Implementación con OpenMP**: `analiza_secuencia_omp.c`
- **Implementación secuencial** (para comparación): `analiza_secuencia.c`

Estos programas permiten observar diferencias de rendimiento entre las distintas metodologías de paralelización. La comparación entre `pthread` y `OpenMP` es relevante para comprender cómo estas bibliotecas manejan la ejecución paralela.

## Requisitos

Para compilar y ejecutar los programas, es necesario contar con:
- Un compilador compatible con `gcc`
- La biblioteca pthreads (`libpthread`)
- Soporte para OpenMP

## Compilación y ejecución

El repositorio incluye un `Makefile` para compilar todos los programas. Para compilar los programas, ejecuta:

```bash
make
```

Una vez compilados, puedes ejecutar los programas de la siguiente manera, usando `time` para medir el tiempo de ejecución:

```bash
time ./crear_procesos      # Ejecuta la prueba con procesos
time ./crear_hilos         # Ejecuta la prueba con hilos
time ./analiza_secuencia   # Ejecuta la versión secuencial
time ./analiza_secuencia_hilos  # Ejecuta la versión con hilos (pthread)
time ./analiza_secuencia_omp    # Ejecuta la versión con OpenMP
```

Para limpiar los archivos generados, usa:

```bash
make clean
```

## Interpretación de resultados

Cuando ejecutes los programas con el comando `time`, se mostrará el tiempo total que tarda cada programa en completarse. Puedes comparar los tiempos de ejecución entre los diferentes métodos (procesos, hilos, y paralelización) para evaluar el rendimiento de cada uno.

## Autores

Desarrollado por [AndresCampus](https://github.com/AndresCampus).

## Licencia

Este proyecto se distribuye bajo la licencia MIT.
