#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define TASKS_PER_JOB 3
#define JOBS 4
#define MAX_TASK_LENGTH 6

typedef struct task{
	uint16_t machine_number, //where the task will be
		job, //which job the task is part of
		length, //how much time the task will take to be completed 
		start_date; //when will the task start on machine_number, INT16_MAX if not placed
}task;

typedef struct machine {
	struct task** task_list;//JOBS
}machine;

typedef struct sol_u {
	machine** machine_list;//TASKS PER JOBS
	uint16_t cmax;
	uint16_t pad[6];
}sol_u;

typedef struct job {
	task** task;
	uint16_t* length;
	uint16_t* num;
} job;

task** generateTasks(void);

task** freeTasks(task** input);

int16_t printTask(task* t);