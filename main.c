#include <stdio.h>
#include <stdlib.h>
#include "Task.h"

int main(void) {
    printf("Hello, World!\n");
    char* oui = (char*)calloc(12, sizeof(char));
    (void)scanf_s("%c", oui, 1);
    free(oui);
    return 0;
}
