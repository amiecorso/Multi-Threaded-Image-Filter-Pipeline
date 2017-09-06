#include <stdio.h>

void 
printHello(void)
{
    int i = 0;
    for(;i < 100; i++){
        fprintf(stdout,"Hello ");
        fprintf(stdout,"World!\n");
    }

}

int
main(void)
{
    //Initialize and create pthread here

    printHello();
    printHello();
    printHello();

    return 0;
}
