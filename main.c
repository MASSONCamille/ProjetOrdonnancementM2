#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "Tools.h"
#include "Heuristics.h"
#include "gen.h"

int main(void) {
#ifdef _WIN32
    _CrtMemState s1, s2, s3;
    _CrtMemCheckpoint(&s1);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    int tmp;
    tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmp = (tmp & 0x0000FFFF) | _CRTDBG_CHECK_ALWAYS_DF;
    _CrtSetDbgFlag(tmp);
#endif

    task **data = generateTasksBis();
    sol_u *test = allocateNewSolU();


    printf("\n---------------------\nincreasing_task_length\n\n");
    task **input = cloneListTask(data);
    test = increasing_task_length(input);
    //printLstTask(input);
    printSolutionU(test);
    printf("Resultat: %d\n", getResultCmax(input));
    freeTasks(input);


    printf("\n---------------\nminimizing_Cmax\n\n");
    input = cloneListTask(data);
    test = minimizing_Cmax(input);
    //printLstTask(input);
    printSolutionU(test);
    printf("Resultat: %d\n", getResultCmax(input));
    freeTasks(input);

    printf("\n--------------------\njobs_increasing_time\n\n");
    input = cloneListTask(data);
    test = jobs_increasing_time(input);
    //printLstTask(input);
    printSolutionU(test);
    printf("Resultat: %d\n", getResultCmax(input));
    freeTasks(input);

    printf("\n----\nFIFO\n\n");
    input = cloneListTask(data);
    test = FIFO(input);
    printSolutionU(test);
    printf("Resultat: %d\n", getResultCmax(input));

    printf("\n--------------------\ngenetic\n\n");
    input = cloneListTask(data);
    test=genetic(pop_creation(input, 8),8, 50);
    printSolutionU(test);
    printf("Resultat: %d\n", getResultCmax(input));

	//printSolutionU(test);
	dumpSolutionUToFile(test);

	//freeAll(test, data);
	freeTasks(data);
	freeSolU(test);

	#ifdef _WIN32
	_CrtMemCheckpoint(&s2);
    printf("%d\n",_CrtCheckMemory());
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
	#endif


	printf("\nFIN");
	return 0;
}
