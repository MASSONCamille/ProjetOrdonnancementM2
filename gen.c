#include <time.h>
#include "gen.h"

//https://stackoverflow.com/a/6127606 with slight modifications
static void shuffle(void* array, size_t n) {
    const size_t size = sizeof(task*);
    char tmp[sizeof(task*)];
    char* arr = array;
    size_t stride = size * sizeof(char);

    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; ++i) {
            size_t rnd = (size_t)rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

            memcpy(tmp, arr + j * stride, size);
            memcpy(arr + j * stride, arr + i * stride, size);
            memcpy(arr + i * stride, tmp, size);
        }
    }
}

task*** pop_creation(task** input, size_t size)
{
	task*** out = (task***)calloc(size,sizeof(task**));
    if (out == NULL)
        return NULL;
	for (uint8_t i = 0; i < size; i++)
	{
		out[i] = (task**)calloc(1, sizeof(task*));
        if (out[i] == NULL)
            return NULL;

        shuffle(input, size);
        memcpy(out[i], input, size);
	}
	
    return out;
}

void mutate(task** input)
{
    srand(time(NULL));
    int i1 = rand() % JOBS * TASKS_PER_JOB;
    int i2 = rand() % JOBS * TASKS_PER_JOB;

    task* tmp = input[i1];
    input[i1] = input[i2];
    input[i2] = tmp;
}

task** crossover(task** out,task** p1, task** p2) 
{
    if (out == NULL)
        return NULL;
    for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++)
    {
        int isSet = 0;
        int offset = 0;
        (i % 2 == 0 ? getFirstUnusedTask(out, p1) : getFirstUnusedTask(out, p2));
        printTask(out[i]);
    }

    return out;
}

task* getFirstUnusedTask(task** dst, task** src)
{
    int i = 0;
    while(dst[i]!=NULL)
    {
        int j = 0;
        int isNotThere = 1;
        for(int j=0;j<JOBS*TASKS_PER_JOB; j++)
        {
            if (dst[j] == src[i])
            {
                isNotThere = 0;
                break;
            }
        }
        if (!isNotThere)
        {
            return src[i];
        }
        i++;
    }

    return NULL;
}


sol_u* genetic(sol_u* out, task*** input, size_t size, int nb_iter)
{
    sol_u** sols = (sol_u**)calloc(2 * size, sizeof(sol_u*));
    if (sols == NULL)
        exit(1);
    for (int i = 0; i < 2 * size; i++)
    {
        sols[i] = (sol_u*)calloc(1, sizeof(sol_u));
        if (sols[i] == NULL)
            return NULL;
    }
    
    for (int i = 0; i < nb_iter; i++)
    {
        task*** new_gen = (task***)calloc(2*size, sizeof(task**));
        if (new_gen == NULL)
            exit(1);
        for (int i = 0; i < 2*size; i++)
        {
            new_gen[i] = (task**)calloc(JOBS*TASKS_PER_JOB, sizeof(task*));
            if (new_gen[i] == NULL)
                exit(1);

            for (int k = 0; k < JOBS * TASKS_PER_JOB; k++)
            {
                new_gen[i][k] = (task*)calloc(1, sizeof(task));
            }
        }

        for (int j = 0; j < size; j++)
        {
            srand(time(NULL));
            int i1 = rand() % size;
            int i2 = rand() % size;
            new_gen[2 * size - 1 - i] = input[i];
            crossover(new_gen[i],input[i1], input[i2]);
            
            if (rand() % 100 <= 5)
            {
                mutate(new_gen[i]);
            }
        }
        for (int i = 0; i < 2 * size; i++)
        {
            if (sols[i] == NULL)
                exit(1);
            if (new_gen[i] == NULL)
                printf("ALED, NEW GEN NULL A I=%d\n", i);
            solution_decoding(sols[i], new_gen[i]);
        }

        qsort(sols, 2*size, sizeof(sol_u*), cmpSolU);

        for (int i = size; i < 2 * size; i++)
        {
            solution_encoding(input[i - size],sols[i - size]);
            for (int j = 0; j < TASKS_PER_JOB * JOBS; i++)
            {
                free(new_gen[i][j]);
            }
            free(new_gen[i]);
        }
        new_gen = (task***)realloc(size, sizeof(task**));
        for (int i = 0; i < size; i++)
        {
            free(input[i]);
        }
        free(input);
        input = new_gen;
    }

    out = input[0];


    for (int i = 1; i < size; i++)
    {
        free(input[i]);
    }

    free(input);
    
}

void solution_encoding(task** dest, sol_u* input)
{

    for (int i = 0; i < JOBS * TASKS_PER_JOB; i++)
    {
        dest[i] = input->machine_list + i;
    }

    qsort(dest, JOBS * TASKS_PER_JOB, sizeof(task*), cmpTask);
}

void solution_decoding(sol_u* dest,task** input)
{
    for (int i = 0; i < JOBS * TASKS_PER_JOB; i++)
    {
        if (addTaskToSolU(dest, input[i]) != 1)
            exit(1);
    }

    dest->cmax = getResultCmax(input);
}