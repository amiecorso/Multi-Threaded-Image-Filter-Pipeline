#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int THREADNUM         = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t* threads;

void*
printHello(void* args)
{
    int i = 0;
    pthread_mutex_lock(&mutex);
    for(;i < 1000000; i++){
        fprintf(stdout,"Hello ");
        fprintf(stdout,"World!\n");
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void
joinThreads(void)
{
    int i;
    for(i = 0; i < THREADNUM; i++)
        pthread_join(threads[i],NULL); 
}

int
main(void)
{
    //Initialize and create pthread here

    clock_t start = clock();

    if((threads = (pthread_t*) malloc(sizeof(pthread_t) * THREADNUM)) == NULL){
        perror("Failed to malloc for threads ");
        exit(EXIT_FAILURE);
    }
    
    
    if(pthread_mutex_init(&mutex,NULL) != 0){
        perror("Mutex Init Error ");
        exit(EXIT_FAILURE);
    }

    int i;
    for(i = 0; i < THREADNUM; i++){
        if(pthread_create(&threads[i],NULL,printHello,NULL) != 0){
            perror("pthread_create failure ");
            joinThreads();
            exit(EXIT_FAILURE);
        }
    }

    joinThreads();

    start = clock() - start;

    int msec = start * 1000 / CLOCKS_PER_SEC / THREADNUM;
    fprintf(stdout,"Takse took about %d seconds and %d miliseconds per thread\n",msec/1000,msec%1000);

    free(threads);
    pthread_mutex_destroy(&mutex);

    return 0;
}
