#include <stdio.h>
#include <stdlib.h>
#include "Heuristics.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u* jobs_increasing_time(task* input) {
	uint8_t* sums = (uint8_t*)calloc(JOBS, sizeof(uint8_t));

	for (int i = 0; i < TASKS_PER_JOB * JOBS; i++) {
		if (sums != NULL)
		{
			sums[input[i].job - 1] += input[i].length;
		}
		else
		{
			return NULL;
		}
	}

	uint8_t* sorted_jobs = sums;

	quicksort(sorted_jobs, 0, JOBS - 1);

	sol_u* sol = allocateNewSolU();

	for (int i = 0; i < JOBS; i++) {
		uint8_t aux = sorted_jobs[i];
		for (int j = 0; j < TASKS_PER_JOB; j++) {
			if (addTaskToSolU(sol, &input[aux + j]) == -1)
			{
				return NULL;
			}
		}
	}
	free(sums);

	return sol;
}

sol_u* increasing_task_length(task* input){
	return NULL;
}