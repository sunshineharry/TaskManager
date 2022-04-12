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
- 编译器：目前支持的编译器为 `ARM_KILL` (AC5和AV6均可) 和 `WIN_MSVC`

**API接口**（`TaskManager_c`）：

- `TaskMsg`：【结构体】任务信息，结构体成员为 **任务函数，开始时间，周期时间，运行次数，PID**

    > 任务函数：只能是无参数，无返回值的函数，**不能是阻塞函数**
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

**示例代码1**：

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

**示例代码2** `[Demo/MSVC/c_language]`
```C
#include "../TaskManager/taskmanager.h"
#include "../TaskManager/TaskManager_config.h"

#include "stdio.h"

void task0(void)
{
	static i = 1;
	printf_s("\n%d:", i);
	i++;
}

void task1(void)
{
	printf_s("task1!");
}

void task2(void)
{
	printf_s("task2!");
}



void main(void)
{
	TM_init(1);
	TaskMsg tasks_msg0 = { task0,START_NOW,1,RUN_FOREVER,0 };
	int PID0 = TM_add_task(&tasks_msg0);
	TaskMsg tasks_msg1 = { task1,START_NOW,2,RUN_FOREVER,0 };
	int PID1 =  TM_add_task(&tasks_msg1);
	TaskMsg tasks_msg2 = { task2,START_NOW,4,RUN_FOREVER,0 };
	int PID2 = TM_add_task(&tasks_msg2);
	while (1)
	{
		TM_run();
		if (get_systime() > 10)
			tasks_msg1.period = 1;
		if (get_systime() > 20)
			TM_kill_by_PID(PID1);
		if (get_systime() > 30)
			TM_kill_by_taskmsg(&tasks_msg2);
		if (get_systime() > 40)
			return;
	}
}
```
运行结果:
```
1:task1!task2!
2:
3:task1!
4:
5:task1!task2!
6:
7:task1!
8:
9:task1!task2!
10:
11:task1!
12:
13:task1!task2!
14:task1!
15:task1!
16:task1!
17:task1!task2!
18:task1!
19:task1!
20:task1!
21:task2!
22:
23:
24:
25:task2!
26:
27:
28:
29:task2!
30:
31:
32:
33:
34:
35:
36:
37:
38:
39:
40:
C:\Users\Harry\Desktop\TaskManager\Demo\MSVC\c_language\Debug\c_language.exe (进程 41888)已退出，返回代码为: 0。
若要在调试停止时自动关闭控制台，请启用“工具”->“选项”->“调试”->“调试停止时自动关闭控制台”。
按任意键关闭此窗口...
```

## 2.2 移植方法

将 `TaskManager_c` 添加到程序目录下，引用 `taskmanager.h` ， `TaskManager_config.h` 和 `systime.h` 并配置时钟即可。

以移植STM32F107为例，说明如下：

**Step1:添加项目文件**

- 添加c文件到项目目录

<img src="readme.assets/image-20220412143641678.png" alt="image-20220412143641678" style="zoom: 67%;" />

- 添加头文件路径

  ![image-20220412144321772](readme.assets/image-20220412144321772.png)

  

**Step2: 更改系统头文件**

进入 `TaskManager_config.h` ，查看如下代码

```c
// 跨平台移植，处理编译器
#ifdef ARM_KILL         // kill编译器
    #include "stm32f10x_conf.h"
#endif
```

将 `stm32f10x_conf.h` 换成系统相关的文件（标准库）

如果使用HAL库，请根据以下内容自行修改

> 此头文件有以下用处：
>
> - 引入 `uint32_t` ，`uint8_t` 等数据类型定义
> - 系统时钟初始化，根据情况，更改 `TM_init()` 函数内 `SysTick_Config(SYS_CYCLE_TIME * 72000000 / 1000);`，完成系统初始化

**Step3: 更改滴答计时器的初始化**

在 `stm32f10x_it.c` 中，覆盖原有的 `SysTick_Handler` 中断服务函数

```C
#include "systime.h"

void SysTick_Handler(void)
{
  update_systime();
}
```

# 3. 系统原理【有机会重写】

![111](readme.assets/111.svg)

- 任务状态：系统在一个循环时间 `SYS_CYCLE_TIME`内，**根据时间 **判断任务是否处于就绪状态

  > 判断依据：每个任务都有一个【下次开始时间】的属性，判断该值是否等于系统现在的时间

  ```C
  for (uint32_t PID=0; PID<MAX_TASK_NUM; PID++)
  {
      if (task_list[PID]->start_time == systime)
      {
          ; // 执行相应任务
      }
  }
  ```

- 任务执行：系统在一个循环时间 `SYS_CYCLE_TIME`内，执行完所有就绪任务，并更新所有任务下次执行的时间

  > 所以，循环时间不能太小，否则系统溢出造成未知错误

- 其他：在一个循环时间内，如果所有任务执行完，还有额外的时间，系统空转。

# 4. 碎碎念

## 4.1 TODO

 **欢迎大家一起完成！**

- [x] 提供STM32标准库版本
- [ ] 提供 HAL 库版本
- [ ] 完成c++版本程序
- [ ] 支持带形参的任务
- [ ] 为更多平台提供移植 demo


## 4.2 联系我

bilibili：[小小up不会起名](https://space.bilibili.com/393609791)

邮箱：18221197@bjtu.edu.cn

