# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-but-set-variable -Wno-unused-parameter
OMPFLAGS = -fopenmp

# Archivos fuente y objetos
SRCS = leer_fasta.c
OBJS = leer_fasta.o
TARGETS = analiza_secuencia analiza_secuencia_omp analiza_secuencia_hilos crear_procesos crear_hilos

# Regla principal
all: $(TARGETS)

# Compilar leer_fasta.o de forma independiente
leer_fasta.o: leer_fasta.c leer_fasta.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilar analiza_secuencia sin OpenMP
analiza_secuencia: analiza_secuencia.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar analiza_secuencia_omp con OpenMP
analiza_secuencia_omp: analiza_secuencia_omp.c $(OBJS)
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ $^

# Compilar analiza_secuencia_hilos con pthreads
analiza_secuencia_hilos: analiza_secuencia_hilos.c $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $^

# Compilar
crear_procesos: crear_procesos.c 
	$(CC) $(CFLAGS) -o $@ $^
# Compilar
crear_hilos: crear_hilos.c 
	$(CC) $(CFLAGS) -pthread -o $@ $^

tests:
	@echo "time ./crear_procesos"
	@echo "time ./crear_hilos"
	@echo "time ./analiza_secuencia sequence.fasta"
	@echo "time ./analiza_secuencia_hilos sequence.fasta"
	@echo "time ./analiza_secuencia_omp sequence.fasta"

# Limpiar los ejecutables y archivos objeto
clean:
	rm -f $(TARGETS) $(OBJS)

