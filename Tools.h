#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdint.h>
#include "task.h"

void quicksort(uint8_t* number, uint8_t first, uint8_t last);

int8_t addTaskToSolU(sol_u* sol, task* t);

sol_u* allocateNewSolU(void);

sol_u* freeSolU(sol_u* sol);