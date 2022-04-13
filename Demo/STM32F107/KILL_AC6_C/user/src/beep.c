#include "beep.h"

void beep_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    BeepOff;
}

void beep_cycle()
{
    static uint32_t beep_state = 0;
    if (!beep_state)
    {
        BeepOn;
        beep_state = 1;
    }
    else
    {
        BeepOff;
        beep_state = 0;
    }
        
}
