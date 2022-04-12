#include "LED.h"
#include "stm32f10x_conf.h"
#include "beep.h"
#include "taskmanager.h"

int main(void)
{
	TM_init();
	// beep_init();
	led_init();
    // TaskMsg tasks_msg1 = {beep_cycle,START_NOW,2000,RUN_FOREVER,0};
    // TM_add_task(&tasks_msg1);
    TaskMsg tasks_msg2 = {led_cycle,START_NOW,100,RUN_FOREVER,0};
    TM_add_task(&tasks_msg2);
	while(1)
	{
        TM_run();
	}		

}
