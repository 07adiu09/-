#include "stm32f10x.h"                  // Device header

#include"LED.h"
#include"Delay.h"
#include"Key.h"

int main(void)
{
	Key_Init();
	LED_Init();
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	while(1)	                                                    
	{                
		
		if (Key_GetFlag()==1)
		{
			LED_Turn();
	}
	
}
}
