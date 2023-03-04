#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "Task.h"
#include "Tools.h"
#include "Heuristics.h"


int main(void) {
    task** data = generateTasksBis();

    for (int i = 0; i < TASKS_PER_JOB*JOBS; ++i) {
        printTask(data[i]);
        printf("\n");
    }
    printf("fin generation\n\n");

    /*uint8_t** a = (uint8_t**)malloc((TASKS_PER_JOB*JOBS) * sizeof(uint8_t *));
    if (a == NULL){
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (int i = 0; i < (TASKS_PER_JOB*JOBS); ++i) {
        a[i] = (uint8_t*)malloc(2* sizeof(uint8_t));
        if (a[i] == NULL){
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    for (int i = 0; i < TASKS_PER_JOB*JOBS; ++i) {
        a[i][0] = data[i]->length;
        a[i][1] = i;
    }

    for (int r = 0; r < (TASKS_PER_JOB*JOBS); r++)
    {
        for (int c = 0; c < 2; c++) {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }
    printf("\n");

    qsort (a, (TASKS_PER_JOB*JOBS), sizeof *a, cmp);

    for (int r = 0; r < (TASKS_PER_JOB*JOBS); r++)
    {
        for (int c = 0; c < 2; c++) {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }

    task** dataBis = (task**)calloc(JOBS * TASKS_PER_JOB, sizeof(task*));
    for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
        dataBis[i] = (task*)calloc(1, sizeof(task));
        dataBis[i] = data[ a[i][1] ];
    }
    data = dataBis;

    for (int i = 0; i < (TASKS_PER_JOB*JOBS); i++) {
        free(a[i]);
    }
    free(a);*/

    taskQS(data, TASKS_PER_JOB*JOBS);

    for (int i = 0; i < TASKS_PER_JOB*JOBS; ++i) {
        printTask(data[i]);
        printf("\n");
    }



    return 0;
}