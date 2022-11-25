#include <stdio.h>
#include <stdlib.h>
#include "Heuristics.h"
#include "Tools.h"

//convention: *input is an array of tasks sorted on jobs
sol_u jobs_increasing_time(task* input){
	uint8_t* sums = (uint8_t*)calloc(JOBS, sizeof(uint8_t));

	for (int i = 0; i < TASKS_PER_JOB* JOBS; i++){
		sums[input[i].job-1] += input[i].length;
	}

	uint8_t* sorted_jobs = sums[JOBS];

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

//task* sort_mim_pj(task* input){
//    task lst_res[TASKS_PER_JOB*JOBS];
//    for (int i = 0; i < TASKS_PER_JOB*JOBS; ++i) {
//        if (i==0){
//
//        }
//    }
//}

sol_u increasing_task_length(task* input){

}