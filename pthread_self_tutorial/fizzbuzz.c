#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
fizz(char** in)//Maybe add more parameters?
{
    return;
} 

int
main(void)
{
    int BUFFSIZE = 100;

    char **fizzbuzzarr = (char**) malloc(sizeof(char*) * BUFFSIZE);

    //This is just setting 1 through BUFFSIZE for fizzbuzz
    int i;
    for(i = 0; i < BUFFSIZE; i++){
        fizzbuzzarr[i] = (char*) malloc(sizeof(char) * BUFFSIZE);
        memset(fizzbuzzarr[i],'\0',BUFFSIZE);
        sprintf(fizzbuzzarr[i],"%d\n",i);
    }

    //HINT: Split this into different workloads using different params for for loops..?
    fizz(fizzbuzzarr);

    //Printing out result
    for(i = 0; i < BUFFSIZE; i++)
        fprintf(stdout,"%s",fizzbuzzarr[i]);
}
