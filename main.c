#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "Tools.h"

int main(void) {
#ifdef _WIN32
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif
	task** data = generateTasks();
	sol_u* test = allocateNewSolU();

	for (int8_t i = 0; i < JOBS * TASKS_PER_JOB; i++)
	{
		//printTask(data[i]);
		addTaskToSolU(test, data[i]);
		//printSolutionU(test);
	}

	//sprintSolutionU(test);
	freeTasks(data);
	freeSolU(test);
	#ifdef _WIN32
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
	#endif

	return 0;
}
