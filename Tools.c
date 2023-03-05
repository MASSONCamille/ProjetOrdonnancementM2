#include <stdbool.h>
#include "Tools.h"

int cmpInt(uint8_t a, uint8_t b) {
    return a - b;
}

int cmp(const void *a, const void *b) {
    uint8_t *x = *(uint8_t **) a;
    uint8_t *y = *(uint8_t **) b;

    return x[0] - y[0];
}

// Minimum PJ -> Minimum Cmax -> Minimum JobRestant -> Hasard
task getTaskH3(task **input) { // warning "input" most be short
    task res; // instance de retour

    // -------------------------
    // --- Test Start is max ---

    task **temp0 = (task **) calloc(JOBS * TASKS_PER_JOB, sizeof(task *));
    if (temp0 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
        temp0[i] = (task *) calloc(1, sizeof(task));
        if (temp0[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp0 = 0;

    for (int i = 0; i < JOBS * TASKS_PER_JOB; ++i) { // recup tache non placé
        if (input[i]->start_date == INT8_MAX) {
            temp0[tailleTemp0] = input[i];
            tailleTemp0++;
        }
    }

    //Dernière tache
    if (tailleTemp0 == 1) {
        res = *temp0[0];
        free(temp0);
        return res;
    }

    // -----------------------
    // --- Test Min Length ---

    int minLength = INT8_MAX;
    for (int i = 0; i < tailleTemp0; ++i) { // recup du min Length (val)
        if (temp0[i]->length < minLength) {
            minLength = temp0[i]->length;
        }
    }

    task **temp1 = (task **) calloc(tailleTemp0, sizeof(task *));
    if (temp1 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < tailleTemp0; i++) {
        temp1[i] = (task *) calloc(1, sizeof(task));
        if (temp1[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp1 = 0;

    for (int i = 0; i < tailleTemp0; ++i) { // recup de tous les Length min
        if (temp0[i]->length == minLength) {
            temp1[tailleTemp1] = temp0[i];
            tailleTemp1++;
        }
    }

    //Une durée op mini
    if (tailleTemp1 == 1) {
        res = *temp1[0];
        free(temp0);
        free(temp1);
        return res;
    }

    // ---------------------
    // --- Test Min Cmax ---

    uint8_t *tabMinCmax = (uint8_t *) calloc(tailleTemp1, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp1; ++i) { // recup lst Cmax
        task *test = temp1[i];
        tabMinCmax[i] = getCmax(input, test);
    }

    int minCmax = INT8_MAX;
    for (int i = 0; i < tailleTemp1; ++i) { // recup du min Cmax (val)
        if (tabMinCmax[i] < minCmax){
            minCmax = tabMinCmax[i];
        }
    }

    task **temp2 = (task **) calloc(tailleTemp1, sizeof(task *));
    if (temp2 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < tailleTemp1; i++) {
        temp2[i] = (task *) calloc(1, sizeof(task));
        if (temp2[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp2 = 0;

    for (int i = 0; i < tailleTemp1; ++i) { // recup de tous les Cmax min
        if (tabMinCmax[i] == minCmax) {
            temp2[tailleTemp2] = temp1[i];
            tailleTemp2++;
        }
    }

    //Un Cmax mini
    if (tailleTemp2 == 1) {
        res = *temp2[0];
        free(temp0);
        free(temp1);
        free(temp2);
        return res;
    }

    // ----------------------------
    // --- Test Min Job Restant ---

    uint8_t *tabMinJobRestant = (uint8_t *) calloc(tailleTemp2, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp2; ++i) { // recup lst Job Restant
        task *test = temp2[i];
        tabMinJobRestant[i] = getJobRestant(input, test);
    }

    int minJobRestant = INT8_MAX;
    for (int i = 0; i < tailleTemp2; ++i) { // recup min Job Restant (val)
        if (tabMinJobRestant[i] < minJobRestant) {
            minJobRestant = tabMinJobRestant[i];
        }
    }
    for (int i = 0; i < tailleTemp2; ++i) { // recup le 1er parmi tous les Job Restant min
        if (tabMinJobRestant[i] == minJobRestant) {
            res = *temp2[0];
            free(temp0);
            free(temp1);
            free(temp2);
            return res;
        }
    }
}

// Minimum Cmax -> Minimum JobRestant -> Minimum PJ -> Hasard
task getTaskH4(task **input){
    task res; // instance de retour

    // -------------------------
    // --- Test Start is max ---

    task **temp0 = (task **) calloc(JOBS * TASKS_PER_JOB, sizeof(task *));
    if (temp0 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++) {
        temp0[i] = (task *) calloc(1, sizeof(task));
        if (temp0[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp0 = 0;

    for (int i = 0; i < JOBS * TASKS_PER_JOB; ++i) { // recup de tous les non placées
        if (input[i]->start_date == INT8_MAX) {
            temp0[tailleTemp0] = input[i];
            tailleTemp0++;
        }
    }

    //Dernière tache
    if (tailleTemp0 == 1) {
        res = *temp0[0];
        free(temp0);
        return res;
    }

    // ---------------------
    // --- Test Min Cmax ---

    uint8_t *tabMinCmax = (uint8_t *) calloc(tailleTemp0, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp0; ++i) { // recup lst Cmax
        task *test = temp0[i];
        tabMinCmax[i] = getCmax(input, test);
    }

    int minCmax = INT8_MAX;
    for (int i = 0; i < tailleTemp0; ++i) { // recup du min Cmax (val)
        if (tabMinCmax[i] < minCmax){
            minCmax = tabMinCmax[i];
        }
    }

    task **temp1 = (task **) calloc(tailleTemp0, sizeof(task *));
    if (temp1 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < tailleTemp0; i++) {
        temp1[i] = (task *) calloc(1, sizeof(task));
        if (temp1[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp1 = 0;

    for (int i = 0; i < tailleTemp0; ++i) { // recup de tous les Cmax min
        if (tabMinCmax[i] == minCmax) {
            temp1[tailleTemp1] = temp0[i];
            tailleTemp1++;
        }
    }

    //Un Cmax mini
    if (tailleTemp1 == 1) {
        res = *temp1[0];
        free(temp0);
        free(temp1);
        return res;
    }

    // ----------------------------
    // --- Test Min Job Restant ---

    uint8_t *tabMinJobRestant = (uint8_t *) calloc(tailleTemp1, sizeof(uint8_t));
    for (int i = 0; i < tailleTemp1; ++i) { // recup lst Job Restant
        task *test = temp1[i];
        tabMinJobRestant[i] = getJobRestant(input, test);
    }

    int minJobRestant = INT8_MAX;
    for (int i = 0; i < tailleTemp1; ++i) { // recup min Job Restant (val)
        if (tabMinJobRestant[i] < minJobRestant) {
            minJobRestant = tabMinJobRestant[i];
        }
    }

    task **temp2 = (task **) calloc(tailleTemp1, sizeof(task *));
    if (temp2 == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (uint8_t i = 0; i < tailleTemp1; i++) {
        temp2[i] = (task *) calloc(1, sizeof(task));
        if (temp2[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    int tailleTemp2 = 0;

    for (int i = 0; i < tailleTemp1; ++i) { // recup de tous les jobs restant min
        if (tabMinJobRestant[i] == minJobRestant) {
            temp2[tailleTemp2] = temp1[i];
            tailleTemp2++;
        }
    }

    //Un jobRestant mini
    if (tailleTemp2 == 1) {
        res = *temp2[0];
        free(temp0);
        free(temp1);
        free(temp2);
        return res;
    }

    // -----------------------
    // --- Test Min Length ---

    int minLength = INT8_MAX;
    for (int i = 0; i < tailleTemp2; ++i) { // recup du min Length (val)
        if (temp2[i]->length < minLength) {
            minLength = temp2[i]->length;
        }
    }

    for (int i = 0; i < tailleTemp2; ++i) {
        if(temp2[i]->length == minLength){
            res = *temp2[i];
            free(temp0);
            free(temp1);
            free(temp2);
            return res;
        }
    }
}

task** cloneListTask(task** taskList){
    task** dcopy=(task**)calloc(JOBS * TASKS_PER_JOB,sizeof(task*));
    if (dcopy == NULL)
        return NULL;

    for (uint8_t i = 0; i < JOBS * TASKS_PER_JOB; i++)
    {
        task* t = (task*)calloc(1, sizeof(task));
        if (t == NULL)
            return NULL;
        t->job = taskList[i]->job;
        t->length = taskList[i]->length;
        t->machine_number = taskList[i]->machine_number;
        t->start_date = taskList[i]->start_date;
        dcopy[i] = t;
    }
    return dcopy;
}

sol_u* lstTaskToSolu(task** taskList){
    int verifend = nbTachePasPlacee(taskList);
    if (verifend > 0){
        fprintf(stderr, "%d no-ended task",verifend);
        return NULL;
    }

    sol_u *solres = allocateNewSolU();

    for (int iterMachine = 0; iterMachine < TASKS_PER_JOB; ++iterMachine) { // iterMachine -> num machine a check
        int taskInCurrentMachine = 0;
        for (int iterTask = 0; iterTask < TASKS_PER_JOB*JOBS; ++iterTask) {
            if (taskList[iterTask]->machine_number == iterMachine){
                solres->machine_list[iterMachine]->task_list[taskInCurrentMachine]->machine_number =
                        taskList[iterTask]->machine_number;
                solres->machine_list[iterMachine]->task_list[taskInCurrentMachine]->job =
                        taskList[iterTask]->job;
                solres->machine_list[iterMachine]->task_list[taskInCurrentMachine]->length =
                        taskList[iterTask]->length;
                solres->machine_list[iterMachine]->task_list[taskInCurrentMachine]->start_date =
                        taskList[iterTask]->start_date;
                taskInCurrentMachine++;
            }
        }
    }

    return solres;
}

void printLstTask(task** taskList){
    for (int i = 0; i < JOBS * TASKS_PER_JOB; ++i) { // print all task
        printTask(taskList[i]);
        printf("\n");
    }

    int taskreste = nbTachePasPlacee(taskList);
    if(taskreste <=0 ){
        printf("Resultat: %d\n",getResultCmax(taskList));
    } else {
        printf("Il reste %d a placer\n",taskreste);
    }
}

uint8_t getResultCmax(task **taskList){
    int numJob;
    int cMax;
    int result = 0;
    for (int i = 0; i < JOBS; ++i) {
        numJob = i;
        cMax = 0;
        for (int j = 0; j < JOBS * TASKS_PER_JOB; ++j) {
            if((taskList[j]->job == numJob) && ((taskList[j]->start_date + taskList[j]->length) > cMax)){
               cMax = taskList[j]->start_date + taskList[j]->length;
            }
        }
        result += cMax;
    }
    return result;
}

uint8_t getCmax(task **tasklist, task *taskToAdd) {
    int startdate = 0;
    int nbMachine = taskToAdd->machine_number;

    for (int j = 0; j < TASKS_PER_JOB * JOBS; j++) {
        if (tasklist[j]->machine_number == nbMachine) {
            if (tasklist[j]->start_date != INT8_MAX) {
                if ((tasklist[j]->start_date + tasklist[j]->length) > startdate) {
                    startdate = tasklist[j]->start_date + tasklist[j]->length;
                }
            }
        }
    }

    int nbJob = taskToAdd->job;
    for (int j = 0; j < TASKS_PER_JOB * JOBS; j++) {
        if (tasklist[j]->job == nbJob) {
            if (tasklist[j]->start_date != INT8_MAX) {
                if ((tasklist[j]->start_date + tasklist[j]->length) > startdate) {
                    startdate = tasklist[j]->start_date + tasklist[j]->length;
                }
            }
        }
    }
    return (startdate+taskToAdd->length);
}

uint8_t nbTachePasPlacee(task **tasklist){
    int nbTache = 0;
    for (int i = 0; i < TASKS_PER_JOB * JOBS; ++i) {
        if(tasklist[i]->start_date == INT8_MAX){
            nbTache++;
        }
    }
    return nbTache;
}

uint8_t getJobRestant(task **tasklist, task *taskToAdd){
    int lenJobRestant = 0;
    int numJob = taskToAdd->job;
    for (int i = 0; i < JOBS*TASKS_PER_JOB; ++i) {
        if((tasklist[i]->job == numJob) && (tasklist[i]->start_date == INT8_MAX)){
            lenJobRestant += tasklist[i]->length;
        }
    }
    return lenJobRestant;
}

void taskQS(task **tasklist, size_t taille) {
    uint8_t **a = (uint8_t **) malloc(taille * sizeof(uint8_t *));
    if (a == NULL) {
        fprintf(stderr, "Out of memory");
        exit(0);
    }
    for (int i = 0; i < taille; ++i) {
        a[i] = (uint8_t *) malloc(2 * sizeof(uint8_t));
        if (a[i] == NULL) {
            fprintf(stderr, "Out of memory");
            exit(0);
        }
    }
    for (int i = 0; i < taille; ++i) {
        a[i][0] = tasklist[i]->length;
        a[i][1] = i;
    }

    /*for (int r = 0; r < (taille); r++)
    {
        for (int c = 0; c < 2; c++) {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }
    printf("\n");*/

    qsort(a, taille, sizeof *a, cmp);   /* qsort array of pointers */

    /*for (int r = 0; r < (taille); r++)
    {
        for (int c = 0; c < 2; c++) {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }
    printf("\n");*/

    task **buffer = (task **) calloc(taille, sizeof(task *));
    for (uint8_t i = 0; i < taille; i++) {
        buffer[i] = tasklist[i];
    }

    for (uint8_t i = 0; i < taille; i++) {
        tasklist[i] = buffer[a[i][1]];
    }

    for (int i = 0; i < taille; i++) {
        free(a[i]);
    }
    free(a);
    free(buffer);

}

int8_t addTaskToSolU(sol_u *sol, task *t) {
    uint8_t k = 0;
    t->start_date = 0;
    //printSolutionU(sol);
    while (sol->machine_list[t->machine_number]->task_list[k] != NULL &&
           sol->machine_list[t->machine_number]->task_list[k]->start_date != INT8_MAX && k < TASKS_PER_JOB) {
        k++;
    }
    //printf("%d %s\n", k,"fin boucle");
    uint8_t b = 0;

    for (uint8_t j = 0; j < TASKS_PER_JOB; j++) {
        for (uint8_t i = 0; i < JOBS; i++) {
            if (sol->machine_list[j]->task_list == NULL || sol->machine_list[j]->task_list[i] == NULL) {
                return -1;
            }
            if (sol->machine_list[j]->task_list[i]->job == t->job) {
                if (b < t->start_date + t->length) {
                    b = t->start_date + t->length;
                }
            }
        }
    }

    for (uint8_t i = 1; i < JOBS - 1; i++) {
        if (sol->machine_list[t->machine_number]->task_list[i] == NULL) {
            return -1;
        }
        uint8_t start = sol->machine_list[t->machine_number]->task_list[i]->start_date +
                        sol->machine_list[t->machine_number]->task_list[i]->length;
        uint8_t end = UINT8_MAX;
        if (sol->machine_list[t->machine_number]->task_list[i + 1]) {
            end = sol->machine_list[t->machine_number]->task_list[i + 1]->start_date;
        }
        if (end - start >= t->length && start < b) {
            b = start;
        }
    }

    uint8_t a = 0;
    if (k != 0) {
        if (sol->machine_list[t->machine_number]->task_list[k - 1])
            a = sol->machine_list[t->machine_number]->task_list[k - 1]->start_date +
                sol->machine_list[t->machine_number]->task_list[k - 1]->length;
    }

    uint8_t start_date = (a > b) ? a : b;

    t->start_date = start_date;
    sol->machine_list[t->machine_number]->task_list[k] = t;

    return 1;
}

sol_u *allocateNewSolU(void) {
    sol_u *sol = (sol_u *) calloc(1, sizeof(sol_u));
    if (sol == NULL) {
        return NULL;
    }

    sol->machine_list = (machine **) calloc(TASKS_PER_JOB, sizeof(machine *));

    if (sol->machine_list == NULL) {
        return NULL;
    }
    for (uint8_t i = 0; i < TASKS_PER_JOB; i++) {
        sol->machine_list[i] = (machine *) calloc(1, sizeof(machine));
    }

    if (sol->machine_list == NULL) {
        return NULL;
    }
    for (uint8_t i = 0; i < TASKS_PER_JOB; i++) {
        if (sol->machine_list[i] == NULL) {
            return NULL;
        }
        sol->machine_list[i]->task_list = (task **) calloc(JOBS, sizeof(task *));
        for (uint8_t j = 0; j < JOBS; j++) {
            if (sol->machine_list[i]->task_list == NULL)
                return NULL;
            sol->machine_list[i]->task_list[j] = (task *) calloc(1, sizeof(task));
            if (sol->machine_list[i]->task_list[j] == NULL)
                return NULL;
            sol->machine_list[i]->task_list[j]->start_date = INT8_MAX;
        }
    }

    return sol;
}

sol_u *freeSolU(sol_u *sol) {
    if (sol == NULL) {
        return NULL;
    }
    for (uint8_t i = 0; i < TASKS_PER_JOB; i++) {

        for (uint8_t j = 0; j < JOBS; j++) {
            free(sol->machine_list[i]->task_list[j]);
        }
        free(sol->machine_list[i]->task_list);
    }
    for (int8_t i = 0; i < TASKS_PER_JOB; i++) {
        free(sol->machine_list[i]);
    }
    free(sol->machine_list);
    free(sol);
    sol = NULL;

    return sol;
}

void *freeAll(sol_u *sol, task **tasks) {
    for (int i = 0; i < TASKS_PER_JOB; i++) {
        for (int j = 0; j < JOBS; j++) {
            sol->machine_list[i]->task_list[j] = NULL;
        }
    }

    if (freeSolU(sol) != NULL)
        exit(1);
    if (freeTasks(tasks) != NULL)
        exit(1);
    return NULL;
}

int8_t printSolutionU(sol_u *sol) {
    if (sol == NULL)
        return -1;

    for (uint8_t i = 0; i < TASKS_PER_JOB; i++) {
        for (uint8_t j = 0; j < JOBS; j++) {
            if (printTask(sol->machine_list[i]->task_list[j]) == -1)
                return -1;
        }
    }

    return 1;
}

uint8_t searchArrayForIndex(uint8_t *arr, uint8_t size, uint8_t val) {
    for (uint8_t i = 0; i < size; i++) {
        if (arr[i] == val)
            return i;
    }

    return UINT8_MAX;
}
