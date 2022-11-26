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

uint8_t addTaskToSolU(sol_u* sol, task* t) {
    uint8_t k = 0;
    while (sol->array[t->machine_number]->array[k])
    {
		k++;
    }

	uint8_t b = 0;

	for (uint8_t i = 0; i < TASKS_PER_JOB; i++)
	{
		for (uint8_t j = 0; j < JOBS; j++)
		{
			if (sol->array[j]->array[i] ==NULL || sol->array[j]->array[i]->job == NULL)
			{
				return -1;
			}
			if (sol->array[j]->array[i]->job == t->job)
			{
				if (b<t->start_date+t->length)
				{
					b = t->start_date + t->length;
				}
			}
		}
	}

	uint8_t a = sol->array[t->machine_number]->array[k-1]->start_date+ sol->array[t->machine_number]->array[k-1]->length;
	uint8_t start_date = (a > b) ? a : b;

	t->start_date = start_date;
	sol->array[t->machine_number]->array[k] = t;

	return 1;
}

sol_u* allocateNewSolU()
{
	sol_u* sol = (sol_u*)malloc(sizeof(sol_u));
	if (sol == NULL)
	{
		return NULL;
	}
	sol->array = (machine**)calloc(TASKS_PER_JOB, sizeof(machine*));

	if (sol->array == NULL)
	{
		return NULL;
	}
	for (uint8_t i = 0; i < TASKS_PER_JOB; i++)
	{
		sol->array[i] = (machine*)calloc(1, sizeof(machine));
	}

	if (sol->array == NULL)
	{
		return NULL;
	}
	for (uint8_t i = 0; i < TASKS_PER_JOB; i++) {
		if (sol->array[i] == NULL)
		{
			return NULL;
		}
		sol->array[i]->array = (task**)calloc(JOBS, sizeof(task*));
		for (uint8_t j = 0; j < TASKS_PER_JOB; j++)
		{
			if (sol->array[i]->array == NULL || sol->array[i]->array[j] == NULL)
			{
				return NULL;
			}
			sol->array[i]->array[j] = (task*)calloc(1, sizeof(task));
		}
	}

	return sol;
}