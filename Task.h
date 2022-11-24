#pragma once
#include <stdint.h>
#define TASKS_PER_JOB 3
#define JOBS 4

typedef struct machine {
	task array[JOBS];
}malchine;

typedef struct task{
	uint8_t machine_number,job;
}task;

typedef struct sol_u {
	struct machine array[TASKS_PER_JOB];
}sol_u;

typedef struct sol_c {
	uint8_t array[TASKS_PER_JOB*JOBS];
}sol_c;

sol_c encoding(sol_u input);

sol_u decoding(sol_c input);