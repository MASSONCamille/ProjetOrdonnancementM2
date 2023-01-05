#pragma once
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "task.h"

void quicksort(uint8_t* number, uint8_t first, uint8_t last);

int8_t addTaskToSolU(sol_u* sol, task* t);

sol_u* allocateNewSolU(void);

sol_u* freeSolU(sol_u* sol);

void* freeAll(sol_u* sol, task** tasks);

int8_t printSolutionU(sol_u* sol);

uint8_t searchArrayForIndex(uint8_t* arr, uint8_t size, uint8_t val);