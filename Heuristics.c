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

task getTaskMinimizing_Cmax(task **input) { // warning "input" most be short
    task res; // instance de retour

    // -------------------------
    // --- Test Start is max ---

    task **temp0 = (task **) calloc(JOBS * TASKS_PER_JOB, sizeof(task *));
    if (temp0 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
        temp0[i] = (task *) calloc(1, sizeof(task));
        if (temp0[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp0 = 0;

    for (int i = 0; i < JOBS * TASKS_PER_JOB; ++i) { // recup de tous les Length min
        if (input[i]->start_date == INT8_MAX) {
            temp0[tailleTemp0] = input[i];
            tailleTemp0++;
        }
    }

    //Une durée op mini
    if (tailleTemp0 == 1) {
        printf("return lv1\n|\n");
        res = *temp0[0];
        free(temp0);
        return res;
    }

    // -----------------------
    // --- Test Min Length ---

    int minLength = INT8_MAX;
    for (int i = 0; i < tailleTemp0; ++i) { // recup du min Length (val)
        if (temp0[i]->length < minLength) {
            minLength = temp0[i]->length;
        }
    }

    task **temp1 = (task **) calloc(tailleTemp0, sizeof(task *));
    if (temp1 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < tailleTemp0; i++) {
        temp1[i] = (task *) calloc(1, sizeof(task));
        if (temp1[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp1 = 0;

    for (int i = 0; i < tailleTemp0; ++i) { // recup de tous les Length min
        if (temp0[i]->length == minLength) {
            temp1[tailleTemp1] = temp0[i];
            tailleTemp1++;
        }
    }

    //Une durée op mini
    if (tailleTemp1 == 1) {
        res = *temp1[0];
        free(temp0);
        free(temp1);
        printf("return lv2\n|\n");
        return res;
    }

    // ---------------------
    // --- Test Min Cmax ---

    uint8_t *tabMinCmax = (uint8_t *) calloc(tailleTemp1, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp1; ++i) { // recup lst Cmax
        task *test = temp1[i];
        tabMinCmax[i] = getCmax(input, test);
    }

    int minCmax = INT8_MAX;
    for (int i = 0; i < tailleTemp1; ++i) { // recup du min Cmax (val)
        if (tabMinCmax[i] < minCmax){
            minCmax = tabMinCmax[i];
        }
    }

    printf("valeur CMAX: ");
    for (int i = 0; i < tailleTemp1; ++i){
        printf("%d ",tabMinCmax[i]);
    }
    printf("\nmin(CMAX) --> %d\n",minCmax);

    for (int i = 0; i < JOBS*TASKS_PER_JOB; ++i) {
        printTask(input[i]);
        printf("|\n");
    }


    task **temp2 = (task **) calloc(tailleTemp1, sizeof(task *));
    if (temp2 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < tailleTemp1; i++) {
        temp2[i] = (task *) calloc(1, sizeof(task));
        if (temp2[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp2 = 0;

    for (int i = 0; i < tailleTemp1; ++i) { // recup de tous les Cmax min
        if (tabMinCmax[i] == minCmax) {
            temp2[tailleTemp2] = temp1[i];
            tailleTemp2++;
        }
    }

    //Un Cmax mini
    if (tailleTemp2 == 1) {
        res = *temp2[0];
        free(temp0);
        free(temp1);
        free(temp2);
        printf("return lv3\n|\n");
        return res;
    }

    // ----------------------------
    // --- Test Min Job Restant ---

    uint8_t *tabMinJobRestant = (uint8_t *) calloc(tailleTemp2, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp2; ++i) { // recup lst Job Restant
        task *test = temp2[i];
        tabMinJobRestant[i] = getJobRestant(input, test);
    }

    int minJobRestant = INT8_MAX;
    for (int i = 0; i < tailleTemp2; ++i) { // recup min Job Restant (val)
        if (tabMinJobRestant[i] < minJobRestant) {
            minJobRestant = tabMinJobRestant[i];
        }
    }
    for (int i = 0; i < tailleTemp2; ++i) { // recup le 1er parmi tous les Job Restant min
        if (tabMinJobRestant[i] == minJobRestant) {
            res = *temp2[0];
            free(temp0);
            free(temp1);
            free(temp2);
            printf("return lv4\n|\n");
            return res;
        }
    }
}

sol_u *minimizing_Cmax(task **input) {
    /*for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) { // print all task
        printTask(input[i]);
        printf("\n");
    }*/
    printf("fin generation\n\n");

    taskQS(input, TASKS_PER_JOB * JOBS);
    /*for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) { // print all task
        printTask(input[i]);
        printf("\n");
    }*/
    printf("fin trie\nreste %d task\n\n", nbTachePasPlacee(input));

    int inc = 0;
    while (nbTachePasPlacee(input) != 0) {
        task buffer = getTaskMinimizing_Cmax(input);
        printTask(&buffer);
        printf("|\n");
        for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
            if((buffer.job == input[i]->job) && (buffer.machine_number == input[i]->machine_number)){
                input[i]->start_date = getCmax(input, &buffer)-buffer.length;
                /*for (int x = 0; x < TASKS_PER_JOB * JOBS; ++x) {
                    printTask(input[x]);
                    printf("|\n");
                }*/
                printf("|\ncmax = %d\n|\n", getCmax(input, &buffer));
            }
        }
        inc++;
        printf("Iteration %d\nreste %d task\n\n", inc, nbTachePasPlacee(input));
        if (inc > 12) break;
    }

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