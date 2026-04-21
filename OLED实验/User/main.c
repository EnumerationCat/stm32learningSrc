#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "AD.h"

uint8_t led_state=0;

/*Key_GetNum();
		if( KeyNum==1)
		{
			led_state=0;
			LED_Off();
			
		}
		if( KeyNum==2)
		{
			led_state=1;
			LED_On();
		}
		
		if(!led_state)
		{
			OLED_ShowString(4,1,"LED STATUS:OFF");
		}
		
		else
		{
			OLED_ShowString(4,1,"LED STATUS: ON");
		}*/
		//OLED_ShowString(1,1,"SDUST");
	
  //OLED_ShowString(2,1,"Name:Hao");
	
	//OLED_ShowString(3,1,"ID:202311110703");
	//LED_Off();
void ShowVoltage(void)
{
	uint16_t ADValue0;
	float Voltage;
	//≤‚µÁ—π
	ADValue0=AD_GetValue(ADC_Channel_0);
	Voltage=(float)ADValue0/4095*3.3;
	OLED_ShowNum(1,9,Voltage,1);
	OLED_ShowNum(1,11,(uint16_t)(Voltage*100)%100,2);
}


int main(void){
	
	LED_Init();
	Key_Init();
	
	OLED_Init();
	
	
	
	AD_Init();
	OLED_ShowString(1,1,"Voltage:0.00V");

	while(1){
		
		
		ShowVoltage();
		Delay_ms(100);
  }
}
