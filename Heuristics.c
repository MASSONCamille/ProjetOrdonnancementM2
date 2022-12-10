#include <stdio.h>
#include <stdlib.h>
#include "Heuristics.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u* jobs_increasing_time(task** input) {
	typedef struct a {
		uint8_t* arr;
		uint8_t* num;
	}a;

	a* jobs = (a*)calloc(1, sizeof(a));
	jobs->arr = (uint8_t*)calloc(TASKS_PER_JOB, sizeof(uint8_t));
	jobs->num = (uint8_t*)calloc(TASKS_PER_JOB, sizeof(uint8_t));

	for (int i = 0; i < TASKS_PER_JOB; i++)
	{
		jobs->num[i] = i;
	}


	for (int i = 0; i < TASKS_PER_JOB * JOBS; i++) {
		if (jobs->arr != NULL)
		{
			jobs->arr[input[i]->job - 1] += input[i]->length;
		}
		else
		{
			return NULL;
		}
	}

	uint8_t* sorted_jobs = jobs->arr;

	quicksort(sorted_jobs, 0, JOBS - 1);

	sol_u* sol = allocateNewSolU();
	//wrong
	for (int i = 0; i < JOBS; i++) {
		uint8_t aux = sorted_jobs[i];
		for (int j = 0; j < TASKS_PER_JOB; j++) {
			if (addTaskToSolU(sol, input[aux + j]) == -1)
			{
				return NULL;
			}
		}
	}
	//free(sums);

	return sol;
}

sol_u* increasing_task_length(task* input){
	return NULL;
}