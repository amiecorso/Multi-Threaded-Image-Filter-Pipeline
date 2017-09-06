#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

int THREADNUM         = 3;
int WORKLOAD          = 9000000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t* threads;

typedef struct 
{
    int    start;
    int    end;
    char** buffer;
} threadargs;

void*
printHello(void* args)
{
    threadargs* in = (threadargs*) args;
    
    int i;
    for(i = in->start;i < in->end; i++){
        sprintf(in->buffer[i], "%d", i+1);
    }
    return NULL;
}

void
joinThreads(void)
{
    int i;
    for(i = 0; i < THREADNUM; i++)
        pthread_join(threads[i],NULL); 
}

void
destroyBuffer(char** in)
{
    int i;
    for(i = 0; i < WORKLOAD; i++)
        if(in[i] != NULL){
            free(in[i]);
            in[i] = NULL;
        }

    if(in != NULL){
        free(in);
        in = NULL;
    }
}

void
printBuffer(char** in)
{
    int i;
    for(i = 0; i < WORKLOAD; i++)
        fprintf(stdout,"%s",in[i]);
    
    fprintf(stdout,"\n");
}

int
bufferChecker(char** in)
{
    int i;
    int true = 1;
    for(i = 0;i < WORKLOAD; i++)
        if(atoi(in[i]) != i+1)
            true = 0;
    
    return true;
}

int
main(int argc, char *argv[])
{
    //Initialize and create pthread here

    //NOTE: If you want to set custom threads when starting program first argument is workload, second is number of threads to work on the work

    int i;
    clock_t start = clock();
    char** printbuffer;

    if(argc > 1)
        WORKLOAD = atoi(argv[1]);
    
    if(argc > 2)
        THREADNUM = atoi(argv[2]);

    if((printbuffer = (char**) malloc(sizeof(char*) * WORKLOAD)) == NULL){
        perror("Failed to malloc for printbuffer ");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < WORKLOAD; i++){
        if((printbuffer[i] = (char*) malloc(sizeof(char) * 100)) == NULL){
            perror("Failed to malloc char* for printbuffer");
            destroyBuffer(printbuffer);
            exit(EXIT_FAILURE); 
        }
        memset(printbuffer[i],'\0',100);
    }
    
    threadargs arguments[THREADNUM];

    if((threads = (pthread_t*) malloc(sizeof(pthread_t) * THREADNUM)) == NULL){
        perror("Failed to malloc for threads ");
        destroyBuffer(printbuffer);
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < THREADNUM; i++){
        arguments[i].start  = (WORKLOAD / THREADNUM) * i;
        arguments[i].end    = (WORKLOAD / THREADNUM) * (i+1);
        arguments[i].buffer = printbuffer;
    }
    
    if(pthread_mutex_init(&mutex,NULL) != 0){
        perror("Mutex Init Error ");
        destroyBuffer(printbuffer);
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < THREADNUM; i++){
        if(pthread_create(&threads[i],NULL,printHello,(void*)&arguments[i]) != 0){
            perror("pthread_create failure ");
            joinThreads();
            pthread_mutex_destroy(&mutex);
            destroyBuffer(printbuffer);
            exit(EXIT_FAILURE);
        }
    }

    joinThreads();

    start = clock() - start;

    int msec = start * 1000 / CLOCKS_PER_SEC / THREADNUM;
    //printBuffer(printbuffer);
    fprintf(stdout,"Takse took about %d seconds and %d miliseconds per thread\n",msec/1000,msec%1000);
    fprintf(stdout,"The buffer was correctly made: %d\n",bufferChecker(printbuffer));

    free(threads);
    pthread_mutex_destroy(&mutex);
    destroyBuffer(printbuffer);

    return 0;
}
