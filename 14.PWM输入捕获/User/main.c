#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint8_t i;

int main(void){
	OLED_Init();
	PWM_Init();
	IC_Init();
	
	OLED_ShowString(1,1,"Freq:00000HZ");
	OLED_ShowString(2,1,"Duty:00%");
	PWM_SetPrescaler(720-1);//freq=72M/(psc+1)/arr(100)
	PWM_SetCompare1(50);    //Duty=ccr/arr(100)

	while(1){
		
		OLED_ShowNum(1,6,IC_GetFreq(),5);
		OLED_ShowNum(2,6,IC_GetDuty(),2);
    }
}
