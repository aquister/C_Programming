#include "myheader.h"
#include <pthread.h>
#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
    int tid;
    tid = *((int *)threadid);
    sleep((tid + 1) * 2);
    printf("Hello World! It's me, thread #%d!\n", tid);
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int tids[NUM_THREADS];
    int rc;
    int t;
    for(t = 0; t < NUM_THREADS; t++) {
        tids[t] = t;
        printf("In main: creating thread %d\n", tids[t]);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&tids[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
