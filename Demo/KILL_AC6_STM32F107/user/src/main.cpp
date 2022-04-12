#include "LED.h"
#include "stm32f10x_conf.h"
#include "beep.h"
#include "taskmanager.hpp"

int main(void)
{
	TaskManager task_manager(1);
	beep_init();
	led_init();
    tasks_msg tasks_msg1 = {beep_cycle,START_NOW,2000,RUN_FOREVER};
    task_manager.add_task(&tasks_msg1);
    tasks_msg tasks_msg2 = {led_cycle,START_NOW,2200,RUN_FOREVER};
    task_manager.add_task(&tasks_msg2);
	while(1)
	{
        task_manager.run();
	}		

}
