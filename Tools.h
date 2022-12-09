#pragma once
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include "task.h"

void quicksort(uint8_t* number, uint8_t first, uint8_t last);

int8_t addTaskToSolU(sol_u* sol, task* t);

sol_u* allocateNewSolU(void);

sol_u* freeSolU(sol_u* sol);

task** generateTasks(void);

task** freeTasks(task** input);

int8_t printSolutionU(sol_u* sol);

int8_t printTask(task* t);