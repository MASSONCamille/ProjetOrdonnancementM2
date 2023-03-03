#include <stdio.h>

int main(void){

    int test[2] ={1, 2};
    int **testp = &test;

    printf("%d - %d\n", test[0], test[1]);
    printf("%d - %d\n", testp[0], testp[1]);
    printf("\n");

    test[0] = 5;

    printf("%d - %d\n", test[0], test[1]);
    printf("%d - %d\n", testp[0], testp[1]);
    printf("\n");

    testp[1] = 10;

    printf("%d - %d\n", test[0], test[1]);
    printf("%d - %d\n", testp[0], testp[1]);
    printf("\n");
}