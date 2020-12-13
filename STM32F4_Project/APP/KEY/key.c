#include "key.h"
#include "SysTick.h"

void KeyInit()
{
	 //初始化GPIO时钟
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOA,ENABLE);
	 //初始化GPIO端口
	 GPIO_InitTypeDef  GPIO_InitStruct;
	 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;                                  //输入模式
	 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	 GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;                                     //上拉 
	 GPIO_Init((GPIO_TypeDef*) GPIOE,(GPIO_InitTypeDef *)  &GPIO_InitStruct);
	
	 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ;
	 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	 GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;                                   //下拉
	 GPIO_Init((GPIO_TypeDef*) GPIOA,(GPIO_InitTypeDef *)  &GPIO_InitStruct);
}

uint8_t ReadKeyUpValue,ReadKey0Value,ReadKey1Value;
uint8_t keyPressFlag=1;
u8 KeyScan()
{	
	ReadKeyUpValue = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);                    //读取三个端口的值
	ReadKey0Value  = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3);
	ReadKey1Value  = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4);
	if(ReadKeyUpValue==1||ReadKey0Value==0||ReadKey1Value==0)  keyPressFlag=1;   //有任何一个键按下，标志位置1
	ReadKeyUpValue = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);                    //再次读取三个端口的值
	ReadKey0Value  = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3);
	ReadKey1Value  = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4);
	if(keyPressFlag==1&&(ReadKeyUpValue==1||ReadKey0Value==0||ReadKey1Value==0))  //只有当标志位为1且有键按下时，则确实有键按下
	{
		keyPressFlag=0;
		if(ReadKeyUpValue==1)     return KEYUP_PRESS;
		else if(ReadKey0Value==0) return KEY0_PRESS;
		else if(ReadKey1Value==0) return KEY1_PRESS;
	}
	return 0;
}
