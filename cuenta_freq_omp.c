#include <omp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int 
main(int argc, char *argv[])
{
  char host[256];
  int frequencia0,frequencia1,frequencia2,frequencia3; // ACGT
  int seqsize;
  int i;
  char *seq;
  FILE *f;



  gethostname(host,256);  // unistd.h
  printf("Hello world! I am  at %s\n", host);

     if(argc!=2) 
     { 
       perror("No file selected. Use program: <filename>\n");
       exit(-1);
     }
     printf(" > Loading FILE %s \n", argv[1]);

     if((f=fopen(argv[1],"rt"))==NULL) 
     { 
       perror("Loading sequence File\n");
       exit(-1);
     }
     fscanf(f," %d ", &seqsize);
     printf(" > File size %d\n", seqsize);
     seq=(char*) malloc(sizeof(char)*seqsize);  
     for(i=0;i<seqsize;i++) fscanf(f," %c ",seq+i);
    


  frequencia0=0;
  frequencia1=0;
  frequencia2=0;
  frequencia3=0;

  omp_set_num_threads(4);	

#pragma omp parallel for private(i) shared(seq,seqsize) \
        reduction(+:frequencia0,frequencia1,frequencia2,frequencia3)
  for(i=0;i<seqsize;i++)
  {
   switch(seq[i])
   {
    case 'a': frequencia0++; break; 
    case 'c': frequencia1++; break;
    case 'g': frequencia2++; break;
    case 't': frequencia3++; break;
   }  
  }

     printf("  Frequencia  A : %d - %f %%\n",frequencia0,(float)frequencia0/seqsize*100); 
     printf("  Frequencia  C : %d - %f %%\n",frequencia1,(float)frequencia1/seqsize*100); 
     printf("  Frequencia  G : %d - %f %%\n",frequencia2,(float)frequencia2/seqsize*100); 
     printf("  Frequencia  T : %d - %f %%\n",frequencia3,(float)frequencia3/seqsize*100); 
     
  return 0;
}

