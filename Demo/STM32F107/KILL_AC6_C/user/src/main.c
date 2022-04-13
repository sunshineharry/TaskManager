#include "LED.h"
#include "stm32f10x_conf.h"
#include "beep.h"
#include "taskmanager.h"

int main(void)
{
	TM_init();
	// beep_init();
	led_init();
    uint32_t cycle_time = 500;
    // TaskMsg tasks_msg1 = {beep_cycle,START_NOW,cycle_time,4,PID_INIT};
    // TM_add_task(&tasks_msg1);
    TaskMsg tasks_msg2 = {led_cycle,NOW,cycle_time,8,PID_INIT};
    TM_add_task(&tasks_msg2);
	while(1)
	{
        TM_run();
        if(TM_is_no_task())
        {
            cycle_time = cycle_time+500;
            TaskMsg tasks_msg2 = {led_cycle,NOW+cycle_time,cycle_time,8,PID_INIT};
            TM_add_task(&tasks_msg2);
        }
	}		

}
