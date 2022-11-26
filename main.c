#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "Tools.h"

int main(void) {
	_CrtMemState s1,s2,s3;
	_CrtMemCheckpoint(&s1);
	sol_u* test = allocateNewSolU();
	printf("%d\n", test->machine_list[0]->task_list[0]->length);
	freeSolU(test);
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
}
