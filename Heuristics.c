#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "Heuristics.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u* jobs_increasing_time(task** input) {
	typedef struct a {
		uint8_t* arr;
		uint8_t* num;
	}a;

	task** dcopy=(task**)calloc(JOBS * TASKS_PER_JOB,sizeof(task*));
	if (dcopy == NULL)
		return NULL;

	for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++)
	{
		task* t = (task*)calloc(1, sizeof(task));
		if (t == NULL)
			return NULL;
		t->job = input[i]->job;
		t->length = input[i]->length;
		t->machine_number = input[i]->machine_number;
		t->start_date = input[i]->start_date;
		dcopy[i] = t;
	}

	a* jobs = (a*)calloc(1, sizeof(a));
	jobs->arr = (uint8_t*)calloc(JOBS, sizeof(uint8_t));
	jobs->num = (uint8_t*)calloc(JOBS, sizeof(uint8_t));

	for (uint8_t i = 0; i < JOBS; i++)
	{
		jobs->num[i] = i;
	}


	for (uint8_t i = 0; i < TASKS_PER_JOB * JOBS; i++) {
		if (jobs->arr != NULL){
			jobs->arr[dcopy[i]->job - 1] += dcopy[i]->length;
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

	sol_u* sol = allocateNewSolU();
	//wrong


	for (int i = 0; i < JOBS; i++) {
		uint8_t aux = searchArrayForIndex(jobs->arr, JOBS, sorted_jobs[i]);
		for (uint8_t j = 0; j < JOBS * TASKS_PER_JOB; j++) {
			if (dcopy[j]->job == aux)
				addTaskToSolU(sol, dcopy[j]);
		}
	}


	free(sorted_jobs);
	free(jobs->num);
	free(jobs);

	return sol;
}

sol_u* FIFO(task* input){
    return NULL;
}

sol_u* minimizing_Cmax(task* input){
    return NULL;
}

sol_u* increasing_task_length(task* input){
    return NULL;
}