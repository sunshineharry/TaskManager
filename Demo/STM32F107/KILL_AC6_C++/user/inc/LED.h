#ifndef __LED_H
#define __LED_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f10x_conf.h"
void led_init(void);
void led_cycle(void);
#ifdef __cplusplus
}
#endif
#endif