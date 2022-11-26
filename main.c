#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "Tools.h"

int main(void) {
	sol_u* test = allocateNewSolU();
	printf("%d", test->machine_list[0]->task_list[0]->length);
}
