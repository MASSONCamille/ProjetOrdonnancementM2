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
	uint8_t machine_number, //where the task will be
		job, //which job the task is part of
		length, //how much time the task will take to be completed 
		start_date; //when will the task start on machine_number, INT8_MAX if not placed
}task;

typedef struct machine {
	struct task** task_list;//JOBS
}machine;

__declspec(align(2)) typedef struct sol_u {
	machine** machine_list;//TASKS PER JOBS
	uint16_t cmax;
	uint8_t pad[6];
}sol_u;

typedef struct job {
	task** task;
	uint8_t* length;
	uint8_t* num;
} job;

task** generateTasks(void);

task** generateTasksBis(void);

task** freeTasks(task** input);

int8_t printTask(task* t);