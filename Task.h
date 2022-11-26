#pragma once
#include <stdint.h>
#define TASKS_PER_JOB 3
#define JOBS 4

typedef struct task{
    uint8_t machine_number, //where the task will be
    job, //which job the task is part of
    length, //how much time the task will take to be completed
    start_date; //when will the task start on machine_number, null if not placed
}task;

typedef struct machine {
	struct task** task_list;//JOBS
}machine;

typedef struct sol_u {
	machine** machine_list;//TASKS PER JOBS
}sol_u;

typedef struct sol_c {
	uint8_t* array;//TASKS PER JOBS*JOBS
}sol_c;

sol_c* solution_encoding(sol_u* input);

sol_u* solution_decoding(sol_c* input);

uint8_t task_encoding(task input);

task task_decoding(uint8_t input);