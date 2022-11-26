#pragma once
#include <stdint.h>
#include "task.h"

void quicksort(uint8_t* number, uint8_t first, uint8_t last);

uint8_t addTaskToSolU(sol_u* sol, task* t);

sol_u* allocateNewSolU(void);

sol_u* freeSolU(sol_u* sol);