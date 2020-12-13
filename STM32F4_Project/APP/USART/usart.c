#include "usart.h"
#include "stm32f4xx.h"
void UsartInit()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef  USART_InitStruct;
    
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode =USART_Mode_Tx|USART_Mode_Rx ;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = 1;
	USART_InitStruct.USART_WordLength = 8;
	USART_Init(USART1,  &USART_InitStruct);
    
    USART_Cmd(USART1,ENABLE);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
    
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

unsigned char num=0;
void USART1_IRQHandler()
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE))
    {
        num++;
        USART_SendData(USART1,USART_ReceiveData(USART1)); 
    }
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}
