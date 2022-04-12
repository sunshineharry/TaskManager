# 1. 简介

## 1.1 系统简介

基于循环时间的跨平台任务管理系统（可用于MCS51，STM32等单片机）

## 1.2 文件目录说明

- `TaskManager_c`：c语言实现的任务管理系统

- `TaskManager_cpp`：c++实现的任务管理系统

- `Demo`：提供多种示例，涵盖电脑模拟器（MSVC），STM32，8081等多种运行环境

# 2. 用法（C语言版）

## 2.1 API用法

**系统配置**（`TaskManager_config.h`）：

- `MAX_TASK_NUM`：最大任务数量，默认为10个，根据自己的需要修改

- `SYS_CYCLE_TIME`：系统的循环时间（单位为ms），默认为 1，表示1ms

**API接口**（`TaskManager_c`）：

- `TaskMsg`：【结构体】任务信息，结构体成员为 **任务函数，开始时间，周期时间，运行次数，PID**

    > 任务函数：只能是无参数，无返回值的函数
    >
    > 开始时间：任务开始运行的时间，`START_NOW` 表示立即开始运行
    >
    > 周期时间：任务每`周期时间`运行一次
    >
    > 运行次数：任务需要运行的次数，`RUN_FOREVER` 表示无穷次
    >
    > PID：任务变号，初始化的时候传入 `0`


- `void TM_init()`：系统初始化

- `uint32_t TM_add_task(TaskMsg* new_task_msg)`：添加任务

- `void TM_kill_by_PID(uint32_t PID)`：通过任务序号删除任务

- `void TM_kill_by_taskmsg(TaskMsg* task_msg)`：通过任务信息删除任务

- `void TM_run(void)`：运行系统

**示例代码**：

```c
#include "taskmanager.h"
#include "TaskManager_config.h"
#include "stdio.h"

// 任务1
void task1(void)
{
	printf("task1!\n");
}

// 任务2
void task2(void)
{
	printf("task2!\n");
}

void main(void)
{
	TM_init();
    // 任务1立即启动，每2ms中运行一次，无休无止的运行
	TaskMsg tasks_msg1 = { task1,START_NOW,2,RUN_FOREVER,0 };
	TM_add_task(&tasks_msg1);
    // 任务2在1ms之后启动，每4ms运行一次，运行5次自动结束
	TaskMsg tasks_msg2 = { task2,1,4,5,0 };
	TM_add_task(&tasks_msg2);
	while (1)
	{
		// 任务管理器启动
        TM_run();
	}
}
```



## 2.2 移植方法

将 `TaskManager_c` 添加到程序目录下，引用 `taskmanager.h` ， `TaskManager_config.h` 和 `systime.h` 并配置时钟即可。

以移植STM32F107为例，说明如下：


# 3. 系统原理

# 4. 碎碎念

## TODO

**欢迎大家一起完成！**

- [ ] 完成c++版本程序

- [ ] 支持带形参的任务

- [ ] 为更多平台提供移植 demo


## 联系我

bilibili：[小小up不会起名](https://space.bilibili.com/393609791)

邮箱：18221197@bjtu.edu.cn

