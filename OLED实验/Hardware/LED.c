#include "stm32f10x.h"                  // Device header
void LED_Init(void){
	//LED配置初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//时钟开启
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_Initstructure);
	//使用引脚的方式
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);低电平
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);高电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	GPIO_SetBits(GPIOC,GPIO_Pin_5);
}

void LED_On(void){
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
void LED_Off(void){
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}
void LED_Turn(void)
{
	static uint8_t LED=0;
  LED = !LED;
  if(LED)
	{
			LED_On();
	}else{
			LED_Off();
	}
}
