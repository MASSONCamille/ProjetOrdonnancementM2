#include "Tools.h"

int cmpInt(uint8_t a, uint8_t b){
	return a-b;
}

int cmp (const void *a, const void *b)
{
    uint8_t *x = *(uint8_t **)a;
    uint8_t *y = *(uint8_t **)b;

    return x[0] - y[0];
}

void taskQS(task** tasklist, size_t taille){
    uint8_t** a = (uint8_t**)malloc(taille * sizeof(uint8_t *));
    if (a == NULL){
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < taille; ++i) {
        a[i] = (uint8_t*)malloc(2* sizeof(uint8_t));
        if (a[i] == NULL){
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    for (uint8_t i = 0; i < taille; ++i) {
        a[i][0] = tasklist[i]->length;
        a[i][1] = i;
    }

    /*for (int r = 0; r < (taille); r++)
    {
        for (int c = 0; c < 2; c++) {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }
    printf("\n");*/

    qsort (a, taille, sizeof *a, cmp);   /* qsort array of pointers */

    /*for (int r = 0; r < (taille); r++)
    {
        for (int c = 0; c < 2; c++) {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }
    printf("\n");*/

    task** buffer = (task**)calloc(taille, sizeof(task*));
    for (uint8_t i = 0; i < taille; i++) {
        buffer[i] = tasklist[i];
    }

    for (uint8_t i = 0; i < taille; i++) {
        tasklist[i] = buffer[ a[i][1] ];
    }

    for (uint8_t i = 0; i < taille; i++) {
        free(a[i]);
    }
    free(a);
    free(buffer);

}

int8_t addTaskToSolU(sol_u* sol, task* t) {
	uint8_t k = 0;
	t->start_date = 0;
	//printSolutionU(sol);
	while (sol->machine_list[t->machine_number]->task_list[k] != NULL && sol->machine_list[t->machine_number]->task_list[k]->start_date != INT8_MAX && k<TASKS_PER_JOB)
	{
		k++;
	}
	//printf("%d %s\n", k,"fin boucle");
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
					b = t->start_date + sol->machine_list[j]->task_list[i]->length;
				}
			}
		}
	}

	for (uint8_t i = 0; i < JOBS - 1; i++)
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
		for (uint8_t j = 0; j < JOBS; j++)
		{
			if (printTask(sol->machine_list[i]->task_list[j]) == -1)
				return -1;
		}
	}

	return 1;
}

uint8_t searchArrayForIndex(uint8_t* arr, uint8_t size, uint8_t val) {
	for (uint8_t i = 0; i < size; i++)
	{
		if (arr[i] == val)
			return i;
	}
	
	return UINT8_MAX;
}

void dumpSolutionUToFile(sol_u* sol)
{
	FILE* f = fopen("dump", "w");
	if (f == NULL)
		exit(1);
	for (uint8_t i = 0; i < TASKS_PER_JOB; i++)
	{

		for (uint8_t j = 0; j < JOBS; j++)
		{
			int length = 0;
			char* str;
			task* aux = sol->machine_list[i]->task_list[j];
			fputs("\nNEW TASK\n", f);
			fputs("JOB: ", f);
			length = snprintf(NULL, 0, "%d", aux->job);
			str = malloc(length + 1);
			if (str == NULL)
			{
				printf("DUMP FAILURE"); 
				exit(-1);
			}
				
			snprintf(str, length + 1, "%d", aux->job);
			fputs(str, f);
			fputs("\nMACHINE: ", f);
			free(str);
			length = snprintf(NULL, 0, "%d", aux->machine_number);
			str = malloc(length + 1);
			if (str == NULL)
			{
				printf("DUMP FAILURE");
				exit(-1);
			}

			snprintf(str, length + 1, "%d", aux->machine_number);
			fputs(str, f);
			fputs("\nSTART DATE :", f);
			free(str);
			length = snprintf(NULL, 0, "%d", aux->start_date);
			str = malloc(length + 1);
			if (str == NULL)
			{
				printf("DUMP FAILURE");
				exit(-1);
			}

			snprintf(str, length + 1, "%d", aux->start_date);
			fputs(str, f);
			fputs("\nLENGTH: ", f);
			free(str);
			length = snprintf(NULL, 0, "%d", aux->length);
			str = malloc(length + 1);
			if (str == NULL)
			{
				printf("DUMP FAILURE");
				exit(-1);
			}

			snprintf(str, length + 1, "%d", aux->length);
			fputs(str, f);
			free(str);
		}
	}
	fclose(f);
}
