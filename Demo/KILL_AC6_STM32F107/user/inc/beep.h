#ifndef __BEEP_H
#define __BEEP_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f10x_conf.h"
#define BeepOn GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define BeepOff GPIO_SetBits(GPIOA,GPIO_Pin_3)
void beep_init(void);
void beep_cycle(void);
#ifdef __cplusplus
}
#endif
#endif