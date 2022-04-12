

#include <iostream>
#include "taskmanager.hpp"


void task2()
{
	std::cout << "task2!\n";
}

class MyClass
{
public:
	void task1()
	{
		std::cout << this->a;
	}
private:
	int a = 0;

};



int main()
{
	TaskManager task_manager(1);
	MyClass myclass;
	tasks_msg tasks_msg1 = { myclass.task1, START_NOW, 2, RUN_FOREVER };
	task_manager.add_task(&tasks_msg1);
	tasks_msg tasks_msg2 = { task2, 4, 4, RUN_FOREVER };
	task_manager.add_task(&tasks_msg2);
	while (1)
	{
		task_manager.run();
		if (get_systime() > 10)
		{
			task_manager.delete_task(&tasks_msg1);
		}
	}
}


