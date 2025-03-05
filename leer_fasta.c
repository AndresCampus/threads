#include "leer_fasta.h"


char *leer_fasta(const char *nombre_archivo, int *size) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        perror("Error abriendo el archivo");
        return NULL;
    }

    char *linea= (char*)malloc(2048);  
    linea=fgets(linea, sizeof(linea), archivo);  // Leer y descartar la cabecera

    // Calcular el tamaño de la secuencia (ignorando saltos de línea)
    int tamaño = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        for (int i = 0; linea[i] != '\0'; i++) {
            if (isalpha(linea[i])) tamaño++;  // Contar solo letras (A, C, G, T)
        }
    }
    *size=tamaño;
    // Reservar memoria para la secuencia
    char *secuencia = (char *)malloc(tamaño + 1);
    if (!secuencia) {
        perror("Error al reservar memoria");
        fclose(archivo);
        return NULL;
    }

    // Reiniciar el archivo para leer la secuencia
    rewind(archivo);
    linea=fgets(linea, sizeof(linea), archivo);  // Saltar la cabecera nuevamente

    // Leer la secuencia
    size_t pos = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        for (int i = 0; linea[i] != '\0'; i++) {
            if (isalpha(linea[i])) {
                secuencia[pos++] = linea[i];
            }
        }
    }
    secuencia[pos] = '\0';  // Finalizar la cadena
    fclose(archivo);
    free(linea);
    return secuencia;
}


