#include "taskmanager.h"
#include "systime.h"

TaskMsg* task_list[MAX_TASK_NUM];
uint8_t task_list_state[MAX_TASK_NUM];

// 在list中找到一个可以添加任务的位置
uint32_t _get_pos_to_add(void)
{
    for(uint32_t PID=0; PID<MAX_TASK_NUM; PID++)
    {
        if(task_list_state[PID]==0)
        {
            task_list_state[PID]=1;
            return PID;
        }
    }
}

// 从list中删除任务
void _delete(PID)
{
    task_list_state[PID]=0;
}

void _add(PID)
{
    task_list_state[PID]=1;
}


void TM_init()
{
    #ifdef ARM_KILL
        SysTick_Config(SYS_CYCLE_TIME * 72000000 / 1000);
    #else
        ;
    #endif
}

uint32_t TM_add_task(TaskMsg *new_task_msg)
{
    uint32_t PID = _get_pos_to_add();
    new_task_msg->PID = PID;
    // 将绝对时间更新到系统节拍
    new_task_msg->start_time = (new_task_msg->start_time / SYS_CYCLE_TIME);
    new_task_msg->period = (new_task_msg->period / SYS_CYCLE_TIME);
    task_list[PID] = new_task_msg;
    _add(PID);
    return PID;
}


void TM_kill_by_PID(uint32_t PID)
{
    task_list[PID] = (TaskMsg*)0;
    _delete(PID);
}

void TM_kill_by_taskmsg(TaskMsg* task_msg)
{
    for(uint32_t PID=0; PID<MAX_TASK_NUM; PID++)
    {
        if(task_list[PID]==task_msg)
        {
            task_list[PID] = (TaskMsg*)0;
            _delete(PID);
        }
    }
}

void TM_run(void)
{
	static uint32_t systime_old = 0;

	// 更新时间
	uint32_t systime = get_systime();
	if (systime == systime_old)
		return;
	else
		systime_old = systime;

	// 循环
	for (uint32_t PID=0; PID<MAX_TASK_NUM; PID++)
	{
		if(task_list_state[PID]==0)
            continue;

        if (task_list[PID]->start_time == systime)
		{
			// 当到时间了，运行任务
			task_list[PID]->task_fun();
			// 无限任务无限循环
			if (task_list[PID]->remain_count == RUN_FOREVER)
			{
				// 更新下一次任务时间
				task_list[PID]->start_time = systime + task_list[PID]->period;
			}
			else
			{
				// 更新下一次任务时间
				task_list[PID]->start_time = systime + task_list[PID]->period;
				// 剩余次数自减
				task_list[PID]->remain_count -= 1;
				// 当剩余次数为0，将其删除
				if (task_list[PID]->remain_count == 0)
                    TM_kill_by_PID(PID);
			}

		}
	}
}