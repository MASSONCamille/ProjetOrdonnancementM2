#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "Tools.h"

int main(void) {
	#ifdef _WIN32
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	#endif
	task** data = generateTasks();
	sol_u* test = allocateNewSolU();

	for (int8_t i = 0; i < JOBS * TASKS_PER_JOB; i++)
	{
		printf("%d\n", addTaskToSolU(test, data[i]));
	}

	printf("%d", printSolutionU(test));
	freeSolU(test);
	freeTasks(data);
	#ifdef _WIN32
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
	#endif
}
