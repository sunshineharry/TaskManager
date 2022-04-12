#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H
#ifdef __cplusplus
extern "C"
{
#endif

// 导入
#include "systime.h"
#include "TaskManager_config.h"

// 宏定义
#define RUN_FOREVER 0xFFFFFFFF
#define START_NOW   (get_systime()+SYS_CYCLE_TIME)


typedef struct s_tasks_msg
{
	void(*task_fun)(void);
	uint32_t start_time;
	uint32_t period;
	uint32_t remain_count;
    uint32_t PID;
}TaskMsg;

void TM_init();
uint32_t TM_add_task(TaskMsg* new_task_msg);
void TM_kill_by_PID(uint32_t PID);
void TM_kill_by_taskmsg(TaskMsg* task_msg);
void TM_run(void);



#ifdef __cplusplus
}
#endif
#endif