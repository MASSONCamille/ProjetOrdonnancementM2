#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "Heuristics.h"
#include "Tools.h"
#include "fifo.h"

//convention: *input is an array of tasks sorted on jobs
sol_u *jobs_increasing_time(task **input) {
    typedef struct a {
        uint8_t *arr;
        uint8_t *num;
    } a;

	a* jobs = (a*)calloc(1, sizeof(a));
	jobs->arr = (uint8_t*)calloc(JOBS, sizeof(uint8_t));
	jobs->num = (uint8_t*)calloc(JOBS, sizeof(uint8_t));
    for (uint8_t i = 0; i < JOBS; i++) {
        jobs->num[i] = i;
    }


	for (uint8_t i = 0; i < TASKS_PER_JOB * JOBS; i++) {
		if (jobs->arr != NULL){
			jobs->arr[input[i]->job - 1] += input[i]->length;
		}
		else
		{
			return NULL;
		}
	}

	uint8_t* sorted_jobs=(uint8_t*)calloc(JOBS*TASKS_PER_JOB,sizeof(uint8_t));

	if(memcpy(sorted_jobs, jobs->arr,JOBS*TASKS_PER_JOB) == NULL)
		return NULL;
	qsort(sorted_jobs, JOBS*TASKS_PER_JOB, sizeof(uint8_t), cmpInt);

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

sol_u* FIFO(task** input) {
    sol_u *sol = allocateNewSolU();
    tlist *listTasks = consVide();
    for (int i = 0; i < TASKS_PER_JOB * JOBS; i++) { //permet d'ajouter les taches dans la liste
        listTasks = cons(listTasks, input[i]);
        addTaskToSolU(sol, extract(listTasks));
    }
    return sol;
}

sol_u *increasing_task_length(task **input) {
    int inc = 0;
    while (nbTachePasPlacee(input) != 0) {
        task buffer = getTaskH3(input);
        for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
            if((buffer.job == input[i]->job) && (buffer.machine_number == input[i]->machine_number)){
                input[i]->start_date = getCmax(input, &buffer)-buffer.length;
            }
        }
        inc++;
        if (inc > 12){
            fprintf(stderr, "trop d'iteration");
            return NULL;
        }
    }

    return lstTaskToSolu(input);
}

sol_u *minimizing_Cmax(task **input) {
    int inc = 0;
    while (nbTachePasPlacee(input) != 0) {
        task buffer = getTaskH4(input);
        for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
            if((buffer.job == input[i]->job) && (buffer.machine_number == input[i]->machine_number)){
                input[i]->start_date = getCmax(input, &buffer)-buffer.length;
            }
        }
        inc++;
        if (inc > 12){
            fprintf(stderr, "trop d'iteration");
            return NULL;
        }
    }

    return lstTaskToSolu(input);
}