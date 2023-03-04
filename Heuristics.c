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

	a* jobs = (a*)calloc(1, sizeof(a));
	jobs->arr = (uint8_t*)calloc(JOBS, sizeof(uint8_t));
	jobs->num = (uint8_t*)calloc(JOBS, sizeof(uint8_t));

	for (uint8_t i = 0; i < JOBS; i++)
	{
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

	uint8_t** sorted_jobs=(uint8_t**)calloc(JOBS*TASKS_PER_JOB,sizeof(uint8_t*));

	if(memcpy(sorted_jobs, &jobs->arr,JOBS*TASKS_PER_JOB) == NULL)
		return NULL;
	printf("%d\n", (sizeof(sorted_jobs))/(sizeof(uint8_t*)));
	qsort(sorted_jobs, (sizeof(sorted_jobs)) / (sizeof(uint8_t*)), sizeof(uint8_t*), cmp);

	sol_u* sol = allocateNewSolU();
	//wrong


	for (int i = 0; i < JOBS; i++) {
		uint8_t aux = searchArrayForIndex(jobs->arr, JOBS, sorted_jobs[i]);
		for (uint8_t j = 0; j < JOBS * TASKS_PER_JOB; j++) {
			if (input[j]->job == aux)
				addTaskToSolU(sol, input[j]);
		}
	}


	free(sorted_jobs);
	free(jobs->arr);
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