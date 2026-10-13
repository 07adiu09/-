#include "stm32f10x.h"                  // Device header

void Init_PWM()
{
	//初始化TIM2时钟
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2,ENABLE);
	//使用内部时钟作为时基单元的时钟
  TIM_InternalClockConfig(TIM2);	
	//初始化GPIOA时钟
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE );
	//初始化GPIOA的Pin0口
	 GPIO_InitTypeDef GPIO_InitStruct;
	 GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF_PP;
	 GPIO_InitStruct.GPIO_Pin =GPIO_Pin_0;
	 GPIO_InitStruct.GPIO_Speed  =GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period =100;
	TIM_TimeBaseInitStruct.TIM_Prescaler =720-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter =0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1 ;
	TIM_OCInitStruct.TIM_OCPolarity =TIM_OCPolarity_High ;
	TIM_OCInitStruct.TIM_OutputState =TIM_OutputState_Enable ;
	TIM_OCInitStruct.TIM_Pulse =0;
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	TIM_Cmd( TIM2, ENABLE);
}
