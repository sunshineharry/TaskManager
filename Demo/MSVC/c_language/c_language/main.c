#include "../TaskManager/taskmanager.h"
#include "../TaskManager/TaskManager_config.h"

#include "stdio.h"


void task0(void)
{
	static i = 1;
	printf_s("\n%d:", i);
	i++;
}

void task1(void)
{
	printf_s("task1!");
}

void task2(void)
{
	printf_s("task2!");
}



void main(void)
{
	TM_init(1);
	TaskMsg tasks_msg0 = { task0,START_NOW,1,RUN_FOREVER,0 };
	int PID0 = TM_add_task(&tasks_msg0);
	TaskMsg tasks_msg1 = { task1,START_NOW,2,RUN_FOREVER,0 };
	int PID1 =  TM_add_task(&tasks_msg1);
	TaskMsg tasks_msg2 = { task2,START_NOW,4,RUN_FOREVER,0 };
	int PID2 = TM_add_task(&tasks_msg2);
	while (1)
	{
		TM_run();
		if (get_systime() > 10)
			tasks_msg1.period = 1;
		if (get_systime() > 20)
			TM_kill_by_PID(PID1);
		if (get_systime() > 30)
			TM_kill_by_taskmsg(&tasks_msg2);
		if (get_systime() > 40)
			return;
	}
}