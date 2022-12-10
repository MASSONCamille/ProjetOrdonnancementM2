#include "Tools.h"

void quicksort(uint8_t* number, uint8_t first, uint8_t last) {
    uint8_t i, j, pivot, temp;
    if (first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while (number[i] <= number[pivot] && i < last)
                i++;
            while (number[j] > number[pivot])
                j--;
            if (i < j) {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }
        temp = number[pivot];
        number[pivot] = number[j];
        number[j] = temp;
        quicksort(number, first, j - 1);
        quicksort(number, j + 1, last);
    }
}

int8_t addTaskToSolU(sol_u* sol, task* t) {
	uint8_t k = 0;
	t->start_date = 0;
	while (sol->machine_list[t->machine_number]->task_list[k]->start_date!= INT8_MAX)
    {
		k++;
    }

	uint8_t b = 0;

	for (uint8_t j = 0; j < TASKS_PER_JOB; j++)
	{
		for (uint8_t i = 0; i < JOBS; i++)
		{
			if (sol->machine_list[j]->task_list==NULL|| sol->machine_list[j]->task_list[i]==NULL)
			{
				return -1;
			}
			if (sol->machine_list[j]->task_list[i]->job == t->job)
			{
				if (b<t->start_date+t->length)
				{
					b = t->start_date + t->length;
				}
			}
		}
	}

	for (uint8_t i = 1; i < JOBS - 1; i++)
	{
		if (sol->machine_list[t->machine_number]->task_list[i] == NULL)
		{
			return -1;
		}
		uint8_t start = sol->machine_list[t->machine_number]->task_list[i]->start_date + sol->machine_list[t->machine_number]->task_list[i]->length;
		uint8_t end = UINT8_MAX;
		if (sol->machine_list[t->machine_number]->task_list[i + 1]) {
			end = sol->machine_list[t->machine_number]->task_list[i + 1]->start_date;
		}
		if (end - start >= t->length && start < b)
		{
			b = start;
		}
	}

	uint8_t a = 0;
	if (k != 0) {
		if (sol->machine_list[t->machine_number]->task_list[k - 1])
			a = sol->machine_list[t->machine_number]->task_list[k - 1]->start_date + sol->machine_list[t->machine_number]->task_list[k - 1]->length;
		}

	uint8_t start_date = (a > b) ? a : b;

	t->start_date = start_date;
	sol->machine_list[t->machine_number]->task_list[k] = t;

	return 1;
}

sol_u* allocateNewSolU(void)
{
	sol_u* sol = (sol_u*)calloc(1,sizeof(sol_u));
	if (sol == NULL)
	{
		return NULL;
	}

	sol->machine_list = (machine**)calloc(TASKS_PER_JOB, sizeof(machine*));

	if (sol->machine_list == NULL)
	{
		return NULL;
	}
	for (uint8_t i = 0; i < TASKS_PER_JOB; i++)
	{
		sol->machine_list[i] = (machine*)calloc(1, sizeof(machine));
	}

	if (sol->machine_list == NULL)
	{
		return NULL;
	}
	for (uint8_t i = 0; i < TASKS_PER_JOB; i++) {
		if (sol->machine_list[i] == NULL)
		{
			return NULL;
		}
		sol->machine_list[i]->task_list = (task**)calloc(JOBS, sizeof(task*));
		for (uint8_t j = 0; j < JOBS; j++)
		{
			if (sol->machine_list[i]->task_list == NULL)
				return NULL;
			sol->machine_list[i]->task_list[j] = (task*)calloc(1, sizeof(task));
			if (sol->machine_list[i]->task_list[j] == NULL)
				return NULL;
			sol->machine_list[i]->task_list[j]->start_date = INT8_MAX;
		}
	}

	return sol;
}

sol_u* freeSolU(sol_u* sol) {
	if (sol == NULL)
	{
		return NULL;
	}
	for (uint8_t i = 0; i < TASKS_PER_JOB; i++) {

		for (uint8_t j = 0; j < JOBS; j++)
		{
			free(sol->machine_list[i]->task_list[j]);
		}
		free(sol->machine_list[i]->task_list);
	}
	for (int8_t i = 0; i < TASKS_PER_JOB; i++) {
		free(sol->machine_list[i]);
	}
	free(sol->machine_list);
	free(sol);
	sol = NULL;
	
	return sol;
}

void* freeAll(sol_u* sol, task** tasks) {
	for (int i = 0; i < TASKS_PER_JOB; i++) {
		for (int j = 0; j < JOBS; j++) {
			sol->machine_list[i]->task_list[j] = NULL;
		}
	}

	if (freeSolU(sol) != NULL)
		exit(1);
	if (freeTasks(tasks) != NULL)
		exit(1);
	return NULL;
}

int8_t printSolutionU(sol_u* sol) {
	if (sol == NULL)
		return -1;

	for (uint8_t i = 0; i < TASKS_PER_JOB; i++)
	{
		printf("Machine: %d \n", i + 1);
		for (uint8_t j = 0; j < JOBS; j++)
		{
			if (printTask(sol->machine_list[i]->task_list[j]) == -1)
				return -1;
		}
	}

	return 1;
}

