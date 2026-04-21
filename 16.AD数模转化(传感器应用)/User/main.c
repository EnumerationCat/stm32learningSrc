#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

void ShowVoltage(void)
{
	uint16_t ADValue0;
	float Voltage;
	//测电压
	ADValue0=AD_GetValue(ADC_Channel_0);
	Voltage=(float)ADValue0/4095*3.3;
	OLED_ShowNum(1,9,Voltage,1);
	OLED_ShowNum(1,11,(uint16_t)(Voltage*100)%100,2);
}
void ShowLight(void)
{
	uint16_t ADValue1;
	float Light;
	//光强
	ADValue1=AD_GetValue(ADC_Channel_1);
	Light=(3.3-(float)ADValue1/4095*3.3)/3.3*330;
	//Light=10240000/(1.1*ADValue1)-2500;
	OLED_ShowNum(2,7,Light,3);
	//OLED_ShowNum(2,9,(uint16_t)(Light*100)%100,2);
}
void ShowTem(void)
{
	uint16_t ADValue2;
	float Tem;
	//温度
	ADValue2=AD_GetValue(ADC_Channel_2);
	Tem=(3.3-(float)ADValue2/4095*3.3)*3;
	//Light=10240000/(1.1*ADValue1)-2500;
	OLED_ShowNum(3,5,Tem,2);
	OLED_ShowNum(3,8,(uint16_t)(Tem*10)%10,1);
}
int main(void){
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"Voltage:0.00V");
	OLED_ShowString(2,1,"Lingt:000Lux");
	OLED_ShowString(3,1,"Tem:00.0C");
	OLED_ShowString(4,1,"distance:0000");

	while(1){
		ShowVoltage();
		ShowLight();
		ShowTem();
		OLED_ShowNum(4,10,AD_GetValue(ADC_Channel_3),4);
		
		Delay_ms(100);
		
    }
}
