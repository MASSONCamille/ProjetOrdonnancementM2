#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "Tools.h"
#include "Heuristics.h"

int main(void) {
    // task** data = generateTasks(); TODO: voir pk il renvoit plus de 3 taches par job ?
    task** data = generateTasksBis();

    for (int i = 0; i < TASKS_PER_JOB*JOBS; ++i) {
        printTask(data[i]);
        printf("\n");
    }
    printf("fin generation\n\n");

    sortableTask** listST = lslTaskTolstST(data, TASKS_PER_JOB*JOBS);

    for (int i = 0; i < TASKS_PER_JOB*JOBS; ++i) {
        printf("SortValue --> %d\n", listST[i]->sortValue);
        //printTask(listST[i]->t);
        printf("\n");
    }

    taskQS(listST, 0, (TASKS_PER_JOB*JOBS)-1);
    printf("Trie\n\n");

    for (int i = 0; i < TASKS_PER_JOB*JOBS; ++i) {
        printf("SortValue --> %d\n", listST[i]->sortValue);
        //printTask(listST[i]->t);
        printf("\n");
    }

    return 0;
}