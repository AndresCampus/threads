#include <omp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "leer_fasta.h"

int main(int argc, char *argv[])
{
  char host[256];
  int frequencia0,frequencia1,frequencia2,frequencia3; // ACGT
  int tamaño=0;
  int i;
  
  gethostname(host,256);  // unistd.h
  printf("Hello world! ejecutando en %s\n", host);
  printf("Número máximo de hilos disponibles: %d\n", omp_get_max_threads());


  if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo_fasta>\n", argv[0]);
        return 1;
   }
  printf(" > Cargando fichero: %s\n", argv[1]);

  char *secuencia = leer_fasta(argv[1], &tamaño);
  if (!secuencia) {
      return 1;
  }

  printf(" > Tamaño secuencia %d\n", tamaño);

  frequencia0=0;
  frequencia1=0;
  frequencia2=0;
  frequencia3=0;

  omp_set_num_threads(4);	

#pragma omp parallel for private(i) shared(secuencia,tamaño) \
        reduction(+:frequencia0,frequencia1,frequencia2,frequencia3)
  for(i=0;i<tamaño;i++)
  {
   switch(secuencia[i])
   {
    case 'A': frequencia0++; break; 
    case 'C': frequencia1++; break;
    case 'G': frequencia2++; break;
    case 'T': frequencia3++; break;
   }  
  }

  printf("  Frequencia  A : %d - %f %%\n",frequencia0,(float)frequencia0/tamaño*100); 
  printf("  Frequencia  C : %d - %f %%\n",frequencia1,(float)frequencia1/tamaño*100); 
  printf("  Frequencia  G : %d - %f %%\n",frequencia2,(float)frequencia2/tamaño*100); 
  printf("  Frequencia  T : %d - %f %%\n",frequencia3,(float)frequencia3/tamaño*100); 
  

  free(secuencia);  // Liberar memoria

  return 0;
}
