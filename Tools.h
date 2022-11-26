#pragma once
#include <stdint.h>
#include "task.h"

void quicksort(uint8_t* number, uint8_t first, uint8_t last);

void addTaskToSolU(sol_u* sol, task* t);

sol_u* allocateNewSolU();
