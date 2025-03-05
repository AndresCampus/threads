# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra 
OMPFLAGS = -fopenmp

# Archivos fuente y objetos
SRCS = leer_fasta.c
OBJS = leer_fasta.o
TARGETS = cuenta_freq cuenta_freq_omp

# Regla principal
all: $(TARGETS)

# Compilar leer_fasta.o de forma independiente
leer_fasta.o: leer_fasta.c leer_fasta.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilar cuenta_freq sin OpenMP
cuenta_freq: cuenta_freq.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar cuenta_freq_omp con OpenMP
cuenta_freq_omp: cuenta_freq_omp.c $(OBJS)
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $^

# Limpiar los ejecutables y archivos objeto
clean:
	rm -f $(TARGETS) $(OBJS)

