#include "taskmanager.h"
#include "systime.h"

TaskMsg* task_list[MAX_TASK_NUM];
uint8_t task_list_state[MAX_TASK_NUM];

// ��list���ҵ�һ��������������λ��
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

// ��list��ɾ������
void _delete(PID)
{
    task_list_state[PID]=0;
}

void _add(PID)
{
    task_list_state[PID]=1;
}


void TM_init(uint32_t sys_cycle_time)
{
    #ifdef ARM_KILL
        SysTick_Config(sys_cycle_time * 72000000 / 1000);
    #else
        ;
    #endif
}

uint32_t TM_add_task(TaskMsg *new_task_msg)
{
    uint32_t PID = _get_pos_to_add();
    new_task_msg->PID = PID;
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

	// ����ʱ��
	uint32_t systime = get_systime();
	if (systime == systime_old)
		return;
	else
		systime_old = systime;

	// ѭ��
	for (uint32_t PID=0; PID<MAX_TASK_NUM; PID++)
	{
		if(task_list_state[PID]==0)
            continue;

        if (task_list[PID]->start_time == systime)
		{
			// ����ʱ���ˣ���������
			task_list[PID]->task_fun();
			// ������������ѭ��
			if (task_list[PID]->remain_count != RUN_FOREVER)
			{
				// ������һ������ʱ��
				task_list[PID]->start_time = systime + task_list[PID]->period;
			}
			else
			{
				// ������һ������ʱ��
				task_list[PID]->start_time = systime + task_list[PID]->period;
				// ʣ������Լ�
				task_list[PID]->remain_count -= 1;
				// ��ʣ�����Ϊ0������ɾ��
				if (task_list[PID]->remain_count == 0)
                    TM_kill_by_PID(PID);
			}

		}
	}
}