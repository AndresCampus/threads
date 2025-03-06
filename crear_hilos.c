#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 10000

void *do_nothing(void *null) {
int i;
i=0;
pthread_exit(NULL);
}                      

int main() {
int rc, j;
pthread_t tid;

printf("Vamos a crear %d hilos\n",NTHREADS);

for (j=0; j<NTHREADS; j++) {
  rc = pthread_create(&tid, NULL, do_nothing, NULL);
  if (rc) {              
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }

  /* Wait for the thread */
  rc = pthread_join(tid, NULL);
  if (rc) {
    printf("ERROR; return code from pthread_join() is %d\n", rc);
    exit(-1);
    }
  }

exit(0);

}
