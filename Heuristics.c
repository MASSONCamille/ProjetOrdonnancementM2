#include "Heuristics.h"
#include "stdlib.h"
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


// Function to get the largest element from an array
int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

// Using counting sort to sort the elements in the basis of significant places
void countingSort(int array[], int size, int place) {
    int output[size + 1];
    int max = (array[0] / place) % 10;

    for (int i = 1; i < size; i++) {
        if (((array[i] / place) % 10) > max)
            max = array[i];
    }
    int count[max + 1];

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    // Calculate count of elements
    for (int i = 0; i < size; i++)
        count[(array[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];
}

// Main function to implement radix sort
void radixsort(int array[], int size) {
    // Get maximum element
    int max = getMax(array, size);

    // Apply counting sort to sort elements based on place value.
    for (int place = 1; max / place > 0; place *= 10)
        countingSort(array, size, place);
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