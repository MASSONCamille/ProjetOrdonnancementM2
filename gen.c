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
	for (uint32_t i = 0; i < size; i++)
	{
		out[i] = (task**)calloc(JOBS * TASKS_PER_JOB, sizeof(task*));
        for (int j = 0; j < JOBS * TASKS_PER_JOB; j++)
        {
            //out[i][j]= (task*)calloc(1, sizeof(task));
        }
        if (out[i] == NULL)
            return NULL;

        shuffle(input, size);
        memcpy(out[i], input, size* JOBS * TASKS_PER_JOB);
	}
    
    //for (int i = 0; i < size; i++)
    //{
    //    printf("POP %d----------------------------------------\n", i);
    //    for (int j = 0; j < JOBS * TASKS_PER_JOB; j++)
    //    {
    //        
    //        if (printTask(out[i][j]) == -1)
    //            printf("GENERATION ERROR");
    //    }
    //}

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
    if (out == NULL||p1==NULL||p2==NULL|| p1[0]==NULL || p2[0]==NULL)
        return NULL;



    for (int i = 0; i < JOBS * TASKS_PER_JOB; i++)
    {
        if (i% 2 == 0)
        {
            out[i] = getFirstUnusedTask(out, p1);
        }
        else
        {
            out[i] = getFirstUnusedTask(out, p2);
        }
        //printf("p1\n");
        //printTask(p1[i]);
        //printf("p2\n");
        //printTask(p2[i]);
        //printf("out\n");
        //printTask(out[i]);
        //printTask(out[i]);
    }

    return out;
}

task* getFirstUnusedTask(task** dst, task** src)
{
    int i = 0;
    while(dst[i]!=NULL)
    {
        int isNotThere = 1;
        for(int j=0;j<JOBS*TASKS_PER_JOB; j++)
        {
            if (dst[j] == src[i])
            {
                isNotThere = 0;
                break;
            }
        }
        if (isNotThere==1)
        {
            return src[i];
        }
        i++;
    }

    return NULL;
}


sol_u* genetic(task*** input, size_t size, int nb_iter)
{
    
    sol_u** sols = (sol_u**)calloc(2 * size, sizeof(sol_u*));
    if (sols == NULL)
        exit(1);
    sol_u* out = allocateNewSolU();
    if (out == NULL)
        exit(1);
    for (uint16_t iter = 0; iter < nb_iter; iter++)
    {
        for (uint64_t i = 0; i < 2 * size; i++)
        {
            sols[i] = allocateNewSolU();
            if (sols[i] == NULL)
                return NULL;
        }
        task*** new_gen = (task***)calloc(2 * size, sizeof(task**));
        if (new_gen == NULL)
            exit(1);
        for (uint64_t i = 0; i < 2 * size; i++)
        {
            new_gen[i] = (task**)calloc(JOBS * TASKS_PER_JOB, sizeof(task*));
            if (new_gen[i] == NULL)
                exit(1);

            for (int k = 0; k < JOBS * TASKS_PER_JOB; k++)
            {
                new_gen[i][k] = (task*)calloc(1, sizeof(task));
                if (new_gen[i][k] == NULL)
                    exit(1);
            }
        }
        //printf("NEW ITER----------------------------------------------------------------------------------\n");
        for (uint16_t j = 0; j < size; j++)
        {
            srand(time(NULL));
            int i1 = rand() % size;
            int i2 = rand() % size;
            new_gen[2 * size - 1 - j] = input[j];
            new_gen[j]=crossover(new_gen[j],input[i1], input[i2]);
            
            if (rand() % 100 <= 5)
            {
                mutate(new_gen[j]);
            }
        }
        for (uint16_t i = 0; i < 2 * size; i++)
        {
            if (sols[i] == NULL)
                exit(1);
            if (*new_gen[i] == NULL)
                printf("ALED, NEW GEN NULL A I=%d\n", i);
            solution_decoding(sols[i], new_gen[i]);
        }

        qsort(sols, 2*size, sizeof(sol_u*), cmpSolU);

        for (uint64_t i = size; i < 2 * size; i++)
        {
            solution_encoding(input[i - size],sols[i - size]);
            for (int j = 0; j < TASKS_PER_JOB * JOBS; j++)
            {
                //printf("i=%lld j=%d %d\n", i, j, _CrtCheckMemory());
                //printTask(new_gen[i][j]);
                //free(new_gen[i][j]);
            }
            //free(new_gen[i]);
        }
        task*** aux = new_gen;
        //printf("new_gen avant realloc: %p, taille=%lld\n", new_gen, _msize(new_gen));
        new_gen = (task***)realloc(new_gen, size*sizeof(task**));
        if (new_gen == NULL)
        {
            free(aux);
            exit(1);
        }
        //printf("%d\n",_CrtCheckMemory());
        //printf("input: %p, taille=%lld\n", input, _msize(input));
        //printf("new_gen apres realloc: %p, taille=%lld\n", new_gen,_msize(new_gen));
        //for (uint64_t i = 0; i < size; i++)
        //{
        //    printf("NOUVEAU GENE------------------------------------------------------\n");
        //    for (uint16_t j = 0; j < TASKS_PER_JOB * JOBS; j++)
        //    {
        //        printTask(input[i][j]);
        //    }
        //}

        for (uint32_t i = 0; i < size; i++)
        {
            for (uint16_t j = 0; j < JOBS * TASKS_PER_JOB; j++)
            {
                //free(input[i][j]);
            }
            free(input[i]);
        }

        input = new_gen;
        //printf("input apres assignation a new_gen: %p, taille=%lld\n",input, _msize(input));
        //printf("input apres free new_gen: %p, taille=%lld\n", input, _msize(input));

        for (uint64_t i = 1; i < 2 * size; i++)
        {
            free(sols[i]);
            /*printf("%d\n", _CrtCheckMemory());*/
        }
        //printf("HEIN-------------------------------------------------------------------------------------------------\n");

        //for (uint64_t i = 0; i < size; i++)
        //{
        //    printf("NOUVEAU GENE------------------------------------------------------\n");
        //    for (uint16_t j = 0; j < TASKS_PER_JOB * JOBS; j++)
        //    {
        //        printTask(input[i][j]);
        //    }
        //}
    }

    out = sols[0];

    for (uint16_t i = 0; i < size; i++)
    {
        free(input[i]);
    }
    free(input);

    free(sols);

    return out;
    
}

void solution_encoding(task** dest, sol_u* input)
{
    int k = 0;
    for (int i = 0; i < TASKS_PER_JOB; i++)
    {
        for (int j = 0; j < JOBS; j++)
        {
            dest[k] = input->machine_list[i]->task_list[j];
            k++;
        }
    }

    qsort(dest, JOBS * TASKS_PER_JOB, sizeof(task*), cmpTask);
}

void solution_decoding(sol_u* dest,task** input)
{
    for (int i = 0; i < JOBS * TASKS_PER_JOB; i++)
    {
        //printf("SOLUTION DECODING LOOP %d-----------------------------------\n", i);
        //printTask(input[i]);
        addTaskToSolU(dest, input[i]);
    }

    dest->cmax = getResultCmax(input);
}