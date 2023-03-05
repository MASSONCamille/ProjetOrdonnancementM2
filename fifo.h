#pragma once
#include "Task.h"
#include "Tools.h"
//TAD FIFO

typedef struct slist {
    task *val;
    struct slist * suc;

} tlist;

tlist * consVide();
tlist * cons(tlist * l , task * v);
tlist *succ(tlist * l);
task * extract (tlist * l);
void lib (tlist *l);