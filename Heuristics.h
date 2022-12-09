#pragma once
#include "Task.h"

sol_u* jobs_increasing_time(task** input);

sol_u* FIFO(task* input);

sol_u* minimizing_Cmax(task* input);

sol_u* increasing_task_length(task* input);