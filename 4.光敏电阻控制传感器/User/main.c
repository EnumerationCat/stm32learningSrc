#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"


int main(void){
	LightSensor_Init();
	Buzzer_Init();
	while(1){
		if(LightSensor_Get() == 1){
			Buzzer_ON();
		}
		else{
			Buzzer_OFF();
		}
	}
}
