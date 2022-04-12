#include "../TaskManager/taskmanager.h"
#include "../TaskManager/TaskManager_config.h"

#include "stdio.h"

void task1(void)
{
	printf_s("task1!\n");
}

void task2(void)
{
	printf_s("task2!\n");
}

void main(void)
{
	TM_init(1);
	TaskMsg tasks_msg1 = { task1,START_NOW,2,RUN_FOREVER,0 };
	TM_add_task(&tasks_msg1);
	TaskMsg tasks_msg2 = { task2,START_NOW,4,RUN_FOREVER,0 };
	TM_add_task(&tasks_msg2);
	while (1)
	{
		TM_run();
	}
}