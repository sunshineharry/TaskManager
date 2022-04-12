#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_TASK_NUM     10         // 最大任务数量
#define SYS_CYCLE_TIME   1         // 系统循环时间，单位为 ms
#define WIN_MSVC

// 跨平台移植，处理编译器
#ifdef ARM_KILL         // kill编译器
    #include "stm32f10x_conf.h"
#endif

#ifdef WIN_MSVC             // msvc 编译器
    #include <windows.h>
	typedef int uint32_t;
	typedef int uint8_t;
#endif





#ifdef __cplusplus
}
#endif
#endif
