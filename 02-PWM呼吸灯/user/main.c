#include "stm32f10x.h"                  // Device header

#include "pwm.h"
#include "delay.h"

int main(void)
{
   Init_PWM();

	
	while(1)	                                                    
	{                
		for(int i=0;i<=100;i++)
		{
		  TIM_SetCompare1( TIM2,i);
			Delay_ms(20);
		}
		for(int i=0;i<=100;i++)
		{
		  TIM_SetCompare1( TIM2,100-i);
			Delay_ms(20);
		}
		
	

}
}
