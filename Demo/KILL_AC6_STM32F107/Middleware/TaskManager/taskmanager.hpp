#pragma once
#include <list>
#include "systime.h"
#define RUN_FOREVER 0xFFFFFFFF
#define START_NOW   (get_systime()+1)

#ifdef _MSC_VER
uint32_t get_systime();
#endif


// ϵͳ������Ϣ�����������������͡���һ��ִ�д������ʱ�䡿
// Ŀǰֻ�ܽ��ܺ��� void function(void);
// TODO �ɱ����
typedef struct s_tasks_msg
{
	void(*task_fun)(void);
	uint32_t start_time;
	uint32_t period;
	uint32_t remain_count;
}tasks_msg;


class TaskManager
{
public:
	TaskManager(uint32_t sys_cycle_time);
	void add_task(tasks_msg* new_task_msg);
	void delete_task(tasks_msg* delete_task_msg);
	void run(void);
private:
	std::list<tasks_msg*> tasks;
	uint32_t systime;
};