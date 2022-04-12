#ifndef __SYSTIME_H
#define __SYSTIME_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f10x_conf.h"
uint32_t get_systime();
void update_systime(void);
#ifdef __cplusplus
}
#endif
#endif