#pragma once
#include "Tools.h"

task*** pop_creation(task** input, size_t size);

void mutate(task** input);

task** crossover(task** out,task** p1, task** p2);

sol_u* genetic(sol_u* out, task*** input, size_t size, int nb_iter);

task* getFirstUnusedTask(task** dst, task** src);

static void shuffle(void* array, size_t n);

void solution_encoding(task** out, sol_u* input);

void solution_decoding(sol_u* dest, task** input);