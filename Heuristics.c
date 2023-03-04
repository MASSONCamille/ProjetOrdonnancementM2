#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "Heuristics.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u *jobs_increasing_time(task **input) {
    typedef struct a {
        uint8_t *arr;
        uint8_t *num;
    } a;

    a *jobs = (a *) calloc(1, sizeof(a));
    jobs->arr = (uint8_t *) calloc(JOBS, sizeof(uint8_t));
    jobs->num = (uint8_t *) calloc(JOBS, sizeof(uint8_t));

    for (uint8_t i = 0; i < JOBS; i++) {
        jobs->num[i] = i;
    }


    for (uint8_t i = 0; i < TASKS_PER_JOB * JOBS; i++) {
        if (jobs->arr != NULL) {
            jobs->arr[input[i]->job - 1] += input[i]->length;
        } else {
            return NULL;
        }
    }

    uint8_t *sorted_jobs = (uint8_t **) calloc(JOBS * TASKS_PER_JOB, sizeof(uint8_t));

    if (memcpy(sorted_jobs, jobs->arr, JOBS * TASKS_PER_JOB) == NULL)
        return NULL;
    qsort(sorted_jobs, JOBS * TASKS_PER_JOB, sizeof(uint8_t *), cmpInt);

    sol_u *sol = allocateNewSolU();
    //wrong


    for (int i = 0; i < JOBS; i++) {
        uint8_t aux = searchArrayForIndex(jobs->arr, JOBS, sorted_jobs[i]);
        for (uint8_t j = 0; j < JOBS * TASKS_PER_JOB; j++) {
            if (input[j]->job == aux)
                addTaskToSolU(sol, input[j]);
        }
    }


    free(sorted_jobs);
    free(jobs->num);
    free(jobs);

    return sol;
}

sol_u *FIFO(task *input) {
    return NULL;
}

task getTaskMinimizing_Cmax(task **input) {
    task res;

    int tailleTemp = 0;
    task **temp = (task **) calloc(JOBS * TASKS_PER_JOB, sizeof(task *));
    if (temp == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
        temp[i] = (task *) calloc(1, sizeof(task));
        if (temp[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }

    }
    //Verification égalité durée op
    uint8_t minlength = INT8_MAX;
    do {
        if (tailleTemp + 1 == TASKS_PER_JOB * JOBS) {
            break;
        }
        if (input[tailleTemp]->start_date == INT8_MAX) {
            minlength = input[tailleTemp]->length;
            temp[tailleTemp] = input[tailleTemp];
        }
        tailleTemp++;
    } while (minlength == input[tailleTemp]->length);

    //Une durée op mini
    if (tailleTemp == 1) {
        res = *temp[0];
        free(temp);
        return res;
    }

    //Min Cmax du tableau tailleTemp
    uint8_t *tabMinCmax = (uint8_t *) calloc(tailleTemp, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp; ++i) {
        task *test = temp[i];
        tabMinCmax[i] = getCmax(input, test);
    }
    //EGALITE Cmax
    int minCmax = INT8_MAX;
    for (int i = 0; i < tailleTemp; ++i) {
        if (tabMinCmax[i] < minCmax) {
            minCmax = tabMinCmax[i];
        }
    }

    task **temp2 = (task **) calloc(tailleTemp, sizeof(task *));
    if (temp2 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < tailleTemp; i++) {
        temp2[i] = (task *) calloc(1, sizeof(task));
        if (temp2[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }

    int tailleTemp2 = 0;
    for (int i = 0; i < tailleTemp; ++i) {
        if (tabMinCmax[i] == minCmax) {
            temp2[i] = temp[i];
            tailleTemp2++;
        }
    }

    //Un Cmax mini
    if (tailleTemp2 == 1) {
        res = *temp2[0];
        free(temp);
        free(temp2);
        return res;
    }

    uint8_t *tabMinJobRestant = (uint8_t *) calloc(tailleTemp2, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp2; ++i) {
        task *test = temp2[i];
        tabMinJobRestant[i] = getJobRestant(input, test);
    }

    int minJobRestant = INT8_MAX;
    for (int i = 0; i < tailleTemp2; ++i) {
        if (tabMinJobRestant[i] < minJobRestant) {
            minJobRestant = tabMinJobRestant[i];
        }
    }
    for (int i = 0; i < tailleTemp2; ++i) {
        if (tabMinJobRestant[i] == minJobRestant) {
            res = *temp2[0];
            free(temp);
            free(temp2);
            return res;
        }
    }
}

sol_u *minimizing_Cmax(task **input) {
    for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
        printTask(input[i]);
        printf("\n");
    }
    printf("fin generation\n\n");

    taskQS(input, TASKS_PER_JOB * JOBS);

    task buffer = getTaskMinimizing_Cmax(input);
    for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
        if((buffer.job == input[i]->job) && (buffer.machine_number == input[i]->machine_number)){
            input[i]->start_date = getCmax(input, &buffer)-buffer.length;
        }
    }


    buffer = getTaskMinimizing_Cmax(input);
    for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
        if((buffer.job == input[i]->job) && (buffer.machine_number == input[i]->machine_number)){
            input[i]->start_date = getCmax(input, &buffer)-buffer.length;
        }
    }

    /*int inc = 0;
    while (nbTachePasPlacee(input) != 0) {
        task buffer = getTaskMinimizing_Cmax(input);
        for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
            if((buffer.job == input[i]->job) && (buffer.machine_number == input[i]->machine_number)){
                input[i]->start_date = getCmax(input, &buffer)-buffer.length;
            }
        }
        inc++;
        printf("%d\n", inc);
    }*/

    for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
        printTask(input[i]);
        printf("\n");
    }
    printf("fin placement\n\n");

    return NULL;
}

sol_u *increasing_task_length(task *input) {
    return NULL;
}