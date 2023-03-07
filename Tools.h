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

uint8_t getCmax(task **tasklist, task *taskToAdd);

uint8_t getJobRestant(task **tasklist, task *taskToAdd);

uint8_t nbTachePasPlacee(task **tasklist);

uint8_t getResultCmax(task **taskList);

task getTaskH3(task **input);

task getTaskH4(task **input);

task** cloneListTask(task** taskList);

sol_u* lstTaskToSolu(task** taskList);

void printLstTask(task** taskList);

int8_t addTaskToSolU(sol_u* sol, task* t);

sol_u* allocateNewSolU(void);

sol_u* freeSolU(sol_u* sol);

void* freeAll(sol_u* sol, task** tasks);

int8_t printSolutionU(sol_u* sol);

uint8_t searchArrayForIndex(uint8_t* arr, uint8_t size, uint8_t val);

int cmp(const void* a, const void* b);

int cmpInt(const void* a,const void* b);

int cmpSolU(const void* a, const void* b);

int cmpTask(const void* a, const void* b);

int cmpJob(const void* a, const void* b);

void dumpSolutionUToFile(sol_u* sol);

task* getIthTask(sol_u* sol, uint8_t index);