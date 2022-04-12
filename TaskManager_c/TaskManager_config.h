#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_TASK_NUM     10


// 跨平台移植，处理编译器
#ifdef STM32F10X_CL         // kill编译器
    #define ARM_KILL
    #include "stm32f10x_conf.h"
#endif

#ifdef _MSC_VER             // msvc 编译器
	#define WIN_MSVC
    #include <windows.h>
	typedef int uint32_t;
	typedef int uint8_t;
#endif





#ifdef __cplusplus
}
#endif
#endif
