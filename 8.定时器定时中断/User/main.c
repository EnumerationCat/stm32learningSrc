#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Sec=0;
uint16_t Min=0;
uint16_t Hour=0;


int main(void){
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Sec:");
	OLED_ShowString(2,1,"Min:");
	OLED_ShowString(3,1,"Hour:");
	OLED_ShowString(4,1,"Time:");
	OLED_ShowString(4,8,":");
	OLED_ShowString(4,11,":");

	while(1){
		OLED_ShowNum(1,5,Sec,5);
		OLED_ShowNum(2,5,Min,5);
		OLED_ShowNum(3,6,Hour,4);
		OLED_ShowNum(4,6,Hour,2);
		OLED_ShowNum(4,9,Min,2);
		OLED_ShowNum(4,12,Sec,2);
    }
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Sec++;
		
		if(Sec>=60)
		{
			Sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hour++;
				if(Hour==24){
					Hour=0;				
				}
			}				
		}		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
}
