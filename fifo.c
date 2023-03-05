//
// Created by vince on 05/03/2023.
//
#pragma once
#include "fifo.h"
tlist * consVide(){
    return NULL;
}
tlist * cons(tlist * l , task* v){
    tlist * c= (tlist *)malloc(1*sizeof(tlist) );
    c -> val=v;
    c-> suc=l;
    return c;
}
tlist *succ(tlist * l){
    return l->suc;

}

task * extract (tlist * l){
    task *c = l->val;
    tlist * v = l;
    l= l->suc;
    v->suc=NULL;
    return c;
}
void lib (tlist *l){
    tlist * c = l->suc;
    while(c){
        free(l);
        l=c;
        c=c->suc;
    }
    free(l);
}
