#include "Heuristics.h"
#include "stdlib.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u jobs_increasing_time(task* input){
	uint8_t sums[JOBS] = (uint8_t*)calloc(JOBS, sizeof(uint8_t));

	for (int i = 0; i < TASKS_PER_JOB* JOBS; i++){
		sums[input[i].job-1] += input[i].length;
	}

	int sorted_jobs[JOBS];


	sol_u* sol = (sol_u*)malloc(sizeof(sol_u));

	free(sums);

	return *sol;
}