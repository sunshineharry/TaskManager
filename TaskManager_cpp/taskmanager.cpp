#ifdef _MSC_VER
#include <windows.h>
#else
#include "stm32f10x_conf.h"
#include "systime.h"
#endif

#include "taskmanager.hpp"
#include <iostream>

#ifdef _MSC_VER
uint32_t get_systime()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	static uint32_t thistime = (sys.wMinute * 60) + (sys.wSecond);
	return (sys.wMinute * 60) + (sys.wSecond) - thistime;
}
#endif

TaskManager::TaskManager(uint32_t sys_cycle_time)
{
#ifndef _MSC_VER
	SysTick_Config(sys_cycle_time * 72000000 / 1000);
#else
	;
#endif
}

void TaskManager::add_task(tasks_msg* new_task_msg)
{
	this->tasks.push_back(new_task_msg);
}


void TaskManager::delete_task(tasks_msg* delete_task_msg)
{
	this->tasks.remove(delete_task_msg);
}

void TaskManager::run()
{
	static uint32_t systime_old = 0;

	// ����ʱ��
	this->systime = get_systime();
	if (this->systime == systime_old)
		return;
	else
		systime_old = this->systime;

	// ѭ��
	std::cout << this->systime << std::endl;
	for (std::list<tasks_msg*>::iterator itr = this->tasks.begin(); itr != this->tasks.end(); itr++)
	{
		if ((*(*itr)).start_time == this->systime)
		{
			// ����ʱ���ˣ���������
			(*(*itr)).task_fun();
			// ������������ѭ��
			if ((*(*itr)).remain_count != RUN_FOREVER)
			{
				// ������һ������ʱ��
				(*(*itr)).start_time = this->systime + (*(*itr)).period;
			}
			else
			{
				// ������һ������ʱ��
				(*(*itr)).start_time = this->systime + (*(*itr)).period;
				// ʣ������Լ�
				(*(*itr)).remain_count -= 1;
				// ��ʣ�����Ϊ0������ɾ��
				if ((*(*itr)).remain_count == 0)
					this->tasks.remove(*itr);
			}

		}
	}
}