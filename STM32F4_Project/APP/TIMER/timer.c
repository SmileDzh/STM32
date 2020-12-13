#include "timer.h"
#include "stm32f4xx.h"

void TimerInit()
{
    NVIC_InitTypeDef NVIC_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
	
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 2500 - 1;            
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8400 - 1;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); 
    
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //开启定时器中断
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM_Cmd(TIM3,ENABLE); //使能定时器
    
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
    
}
unsigned int count=0;
void TIM3_IRQHandler()
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)) 
    {
        count++;
    }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
