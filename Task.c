#include "Task.h"

task** generateTasks(void) {
    task** data = (task**)calloc(JOBS * TASKS_PER_JOB, sizeof(task*));
    if (data == NULL)
        return NULL;
    for (uint16_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
        data[i] = (task*)calloc(1, sizeof(task));
        if (data[i] == NULL)
            return NULL;
    }
    srand((unsigned int)time(NULL));

    for (uint16_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
        data[i]->job = (uint16_t)floor((double)i / TASKS_PER_JOB);
        data[i]->length = (uint16_t)floor((rand()% MAX_TASK_LENGTH)+1);
        data[i]->machine_number = (uint16_t)floor(i % TASKS_PER_JOB);
        data[i]->start_date = INT16_MAX;
    }

    return data;
}

task** freeTasks(task** input) {
	if (input == NULL)
		return NULL;
	for (uint16_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
		free(input[i]);
	}
	free(input);
	input = NULL;
	return input;
}

int16_t printTask(task* t) {
	if (t == NULL)
		return -1;
	printf("Job: %d\nStart: %d\nLength: %d\nMachine: %d\n", t->job, t->start_date, t->length, t->machine_number);
	return 1;
}
