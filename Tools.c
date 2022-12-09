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
    while (sol->machine_list[t->machine_number]->task_list[k])
    {
		k++;
    }

	uint8_t b = 0;

	for (uint8_t i = 0; i < JOBS; i++)
	{
		for (uint8_t j = 0; j < TASKS_PER_JOB; j++)
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

	for (uint8_t i = 1; i < JOBS; i++)
	{
		if (sol->machine_list[t->machine_number]->task_list[i] == NULL)
		{
			return -1;
		}
		uint8_t start = sol->machine_list[t->machine_number]->task_list[i]->start_date + sol->machine_list[t->machine_number]->task_list[i]->length;
		uint8_t end = sol->machine_list[t->machine_number]->task_list[i+1]->start_date;
		if (end - start >= t->length && start < b)
		{
			b = start;
		}
	}

	uint8_t a = sol->machine_list[t->machine_number]->task_list[k-1]->start_date+ sol->machine_list[t->machine_number]->task_list[k-1]->length;
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
		for (uint8_t j = 0; j < TASKS_PER_JOB; j++)
		{
			if (sol->machine_list[i]->task_list == NULL)
				return NULL;
			sol->machine_list[i]->task_list[j] = (task*)calloc(1, sizeof(task));
		}
	}

	return sol;
}

sol_u* freeSolU(sol_u* sol) {
	if (sol == NULL)
	{
		return NULL;
	}
	for (int8_t i = 0; i < TASKS_PER_JOB; i++) {

		for (int8_t j = 0; j < TASKS_PER_JOB; j++)
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

task** generateTasks(void){
	task** data = (task**)calloc(JOBS * TASKS_PER_JOB, sizeof(task*));
	if (data == NULL)
		return NULL;
	for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
		data[i] = (task*)calloc(1, sizeof(task));
		if (data[i] == NULL)
			return NULL;
	}
	srand((unsigned int)time(NULL));

	for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
		data[i]->job = (uint8_t)floor((double)i / TASKS_PER_JOB )+1;
		data[i]->length = (uint8_t)rand();
		data[i]->machine_number = (uint8_t)floor((double)i / JOBS)+1;
		printf("%d\n", i);
	}

	return data;
}


task** freeTasks(task** input) {
	if (input == NULL)
		return NULL;
	for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
		free(input[i]);
	}
	free(input);
	input = NULL;
	return input;
}

int8_t printTask(task* t) {
	if (t == NULL)
		return -1;
	printf("Job: %d\nStart: %d\nLength: %d\n", t->job, t->start_date, t->length);
	return 1;
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

