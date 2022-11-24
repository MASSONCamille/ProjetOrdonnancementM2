#include <stdio.h>
#include <stdlib.h>
#include "Task.h"

int main() {
    printf("Hello, World!\n");
    char* oui = (char*)calloc(12, sizeof(char));
    (void)scanf("%c", oui);
    free(oui);
}
