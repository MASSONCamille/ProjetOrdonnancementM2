#include "Heuristics.h"
#include "stdlib.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u jobs_increasing_time(task* input){
	uint8_t sums[JOBS] = (uint8_t*)calloc(JOBS, sizeof(uint8_t));

	for (int i = 0; i < TASKS_PER_JOB* JOBS; i++){
		sums[input[i].job-1] += input[i].length;
	}

	uint8_t sorted_jobs[JOBS] = sums[JOBS];

	quicksort(sorted_jobs, 0, JOBS - 1);

	sol_u* sol = (sol_u*)malloc(sizeof(sol_u));
	for (int i = 0; i < JOBS; i++) {
		sol->array = (machine*)calloc(JOBS, sizeof(machine));
	}

	for (int i = 0; i < JOBS; i++) {

	}

	free(sums);

	return *sol;
}