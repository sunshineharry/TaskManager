#include "stm32f10x_conf.h"
#include "LED.h"


void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2); 
}

void next_Led(uint32_t LED_num)
{
    switch (LED_num)
    {
    case 0:
        GPIO_SetBits(GPIOD, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
        GPIO_ResetBits(GPIOD, GPIO_Pin_2);
        break;
    case 1:
        GPIO_SetBits(GPIOD, GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_7);
        GPIO_ResetBits(GPIOD, GPIO_Pin_3);
        break;
    case 2:
        GPIO_SetBits(GPIOD, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_7);
        GPIO_ResetBits(GPIOD, GPIO_Pin_4);
        break;
    case 3:
        GPIO_SetBits(GPIOD, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
        GPIO_ResetBits(GPIOD, GPIO_Pin_7);
        break;
    default:
        break;
    }
}

void led_cycle(void)
{
    static uint32_t led_state = 1;
    next_Led(led_state);
    led_state = (led_state+1)%4;
}