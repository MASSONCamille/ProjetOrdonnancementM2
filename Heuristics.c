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
	}

	uint8_t* sorted_jobs = sums;

	quicksort(sorted_jobs, 0, JOBS - 1);

	sol_u* sol = (sol_u*)malloc(sizeof(sol_u));
	if (sol != NULL)
	{
		sol->array = (machine*)calloc(TASKS_PER_JOB, sizeof(machine));
	}
	for (int i = 0; i < TASKS_PER_JOB; i++) {
		if (sol != NULL && sol->array != NULL)
		{
			sol->array[i].array = (task*)calloc(JOBS, sizeof(task));
		}
	}

	for (int i = 0; i < JOBS; i++) {

	}

	free(sums);
	if (sol != NULL)
	{
		return sol;
	}
	else
	{
		return NULL;
	}
}
//
//        }
//    }
//}

sol_u* increasing_task_length(task* input){
	return NULL;
}