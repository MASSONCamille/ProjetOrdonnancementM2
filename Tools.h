#pragma once
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "task.h"

void taskQS(task** tasklist, size_t taille);

int8_t addTaskToSolU(sol_u* sol, task* t);

sol_u* allocateNewSolU(void);

sol_u* freeSolU(sol_u* sol);

void* freeAll(sol_u* sol, task** tasks);

int8_t printSolutionU(sol_u* sol);

uint8_t searchArrayForIndex(uint8_t* arr, uint8_t size, uint8_t val);

int cmp(const void* a, const void* b);

int cmpInt(uint8_t a, uint8_t b);

void dumpSolutionUToFile(sol_u* sol);