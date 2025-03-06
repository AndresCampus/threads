#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "leer_fasta.h"

#define NUM_THREADS 4

int tamaño = 0;
char *secuencia;

typedef struct {
    int frequencia0;
    int frequencia1;
    int frequencia2;
    int frequencia3;
} Frequencias;

// Función que cada hilo ejecutará
void *contar_frecuencia(void *arg) {
    int start = *((int *)arg);
    int end = start + (tamaño / NUM_THREADS);
    if (end > tamaño) end = tamaño;

    Frequencias *resultados = (Frequencias *)malloc(sizeof(Frequencias));
    resultados->frequencia0 = 0;
    resultados->frequencia1 = 0;
    resultados->frequencia2 = 0;
    resultados->frequencia3 = 0;

    for (int i = start; i < end; i++) {
        switch (secuencia[i]) {
            case 'A': resultados->frequencia0++; break;
            case 'C': resultados->frequencia1++; break;
            case 'G': resultados->frequencia2++; break;
            case 'T': resultados->frequencia3++; break;
        }
    }

    return (void *)resultados;
}

int main(int argc, char *argv[]) {
    char host[256];
    
    gethostname(host, 256);  // unistd.h
    printf("Hello world! ejecutando en %s\n", host);
    printf("Número máximo de hilos disponibles: %d\n", NUM_THREADS);
    printf("Usando hilos de pthreads\n");

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo_fasta>\n", argv[0]);
        return 1;
    }
    printf(" > Cargando fichero: %s\n", argv[1]);

    secuencia = leer_fasta(argv[1], &tamaño);
    if (!secuencia) {
        return 1;
    }

    printf(" > Tamaño secuencia %d\n", tamaño);

    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS];
    Frequencias resultados_totales = {0, 0, 0, 0};

    // Asignamos a cada hilo un rango de la secuencia
    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i * (tamaño / NUM_THREADS);
        pthread_create(&threads[i], NULL, contar_frecuencia, (void *)&indices[i]);
    }

    // Esperamos que todos los hilos terminen y sumamos los resultados parciales
    for (int i = 0; i < NUM_THREADS; i++) {
        Frequencias *resultados_hilo;
        pthread_join(threads[i], (void **)&resultados_hilo);

        // Reducir resultados del hilo al total
        resultados_totales.frequencia0 += resultados_hilo->frequencia0;
        resultados_totales.frequencia1 += resultados_hilo->frequencia1;
        resultados_totales.frequencia2 += resultados_hilo->frequencia2;
        resultados_totales.frequencia3 += resultados_hilo->frequencia3;

        free(resultados_hilo); // Liberar memoria de los resultados parciales
    }

    // Mostrar resultados
    printf("  Frequencia  A : %d - %f %%\n", resultados_totales.frequencia0, (float)resultados_totales.frequencia0 / tamaño * 100);
    printf("  Frequencia  C : %d - %f %%\n", resultados_totales.frequencia1, (float)resultados_totales.frequencia1 / tamaño * 100);
    printf("  Frequencia  G : %d - %f %%\n", resultados_totales.frequencia2, (float)resultados_totales.frequencia2 / tamaño * 100);
    printf("  Frequencia  T : %d - %f %%\n", resultados_totales.frequencia3, (float)resultados_totales.frequencia3 / tamaño * 100);

    free(secuencia);  // Liberar memoria

    return 0;
}

