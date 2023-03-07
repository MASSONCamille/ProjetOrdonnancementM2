#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "Heuristics.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u *jobs_increasing_time(task **input) {

    job** jobs = (job**)calloc(JOBS, sizeof(job*));
    //printf("\n");
    if (jobs == NULL)
        return NULL;
    for (int i = 0; i < JOBS; i++) {
        jobs[i] = (job*)malloc(sizeof(job));
        //printf("%d\n", _CrtCheckMemory());
        if (jobs[i] == NULL)
            return NULL;
        jobs[i]->task = (task**)calloc(TASKS_PER_JOB, sizeof(task*));
        //printf("%d\n", _CrtCheckMemory());
        if (jobs[i]->task == NULL)
            return NULL;
        jobs[i]->length = (uint8_t*)calloc(1,sizeof(uint8_t));
        //printf("%d\n", _CrtCheckMemory());
        jobs[i]->num = (uint8_t*)calloc(1,sizeof(uint8_t));
        //printf("%d\n", _CrtCheckMemory());
        for (int j = 0; j < TASKS_PER_JOB; j++)
        {
            jobs[i]->task[j] = (task*)malloc(sizeof(task));
            //printf("%d\n", _CrtCheckMemory());
            if (jobs[i]->task[j] == NULL)
                return NULL;
        }
    }

    //for (int i = 0; i < TASKS_PER_JOB * JOBS; i++) {
    //    printTask(input[i]);
    //}

    int oui[JOBS];
    int non[JOBS];
    for (int i = 0; i < JOBS; i++)
    {
        oui[i] = 0;
        non[i] = 0;
    }
	for (int i = 0; i < TASKS_PER_JOB * JOBS; i++) {
		jobs[input[i]->job]->length = &(oui[input[i]->job]);
        //printf("%d\n", _CrtCheckMemory());
        oui[input[i]->job] += input[i]->length;
        //printf("%d\n", _CrtCheckMemory());
        //printf("job: %d, %p\n", input[i]->job, (void*)jobs[input[i]->job]->task);
        jobs[input[i]->job]->task[i% TASKS_PER_JOB] = input[i];
        //printf("%d\n", _CrtCheckMemory());
        non[input[i]->job] = input[i]->job;
        jobs[input[i]->job]->num = &(non[input[i]->job]);
        //printf("job num: %d, aux:%d, correct: %d\n", *jobs[input[i]->job]->num, non[input[i]->job], input[i]->job);
        //printf("%d\n", _CrtCheckMemory());
	}

    //for (int i = 0; i < TASKS_PER_JOB * JOBS; i++) {
    //    printTask(input[i]);
    //}
    //printf("%d\n", _CrtCheckMemory());

    //for (int i = 0; i < JOBS; i++) {
    //    printf("%d ", *(jobs[i]->length));
    //}
    //printf("\n");

	//if(memcpy(sorted_jobs, jobs->arr,JOBS*TASKS_PER_JOB) == NULL)
	//	return NULL;
	qsort(jobs, JOBS, sizeof(job*), cmpJob);


    //for (uint8_t i = 0; i < JOBS; i++) {
    //    printf("%d ", *(jobs[i]->length));
    //}
    //printf("\n");
    sol_u *sol = allocateNewSolU();


    //for (uint8_t i = 0; i < JOBS; i++) {
    //    printf("%d ", *(jobs[i]->num));
    //}
    //printf("\n");
	for (int i = 0; i < JOBS; i++) {
        //throw duplicates when 2 values are equals
		for (int j = 0; j < JOBS * TASKS_PER_JOB; j++) {
            if (input[j]->start_date == INT8_MAX)
            {
                if (input[j]->job == *(jobs[i]->num))
                    //printf("%d %d\n", input[j]->job, input[j]->start_date);
                //printTask(input[j]);
                addTaskToSolU(sol, input[j]);
            }

		}
	}


    //for (int i = 0; i < JOBS; i++) {
    //    free(jobs[i]);
    //}
    //    
    //free(jobs);

    return sol;
}

sol_u* FIFO(task** input) {
    sol_u *sol = allocateNewSolU();
    for (int i = 0; i < TASKS_PER_JOB * JOBS; i++) { //permet d'ajouter les taches dans la liste
        addTaskToSolU(sol, input[i]);
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