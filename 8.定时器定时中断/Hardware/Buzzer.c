#include "stm32f10x.h"                  // Device header
void Buzzer_Init(void){
	//蜂鸣器配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	//使用引脚的方式
	//GPIO_SetBits(GPIOB,GPIO_Pin_0);低电平
	//GPIO_ResetBits(GPIOB,GPIO_Pin_0);高电平
	//GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}
void Buzzer_ON(void){
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
void Buzzer_OFF(void){
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}
void Buzzer_Turn(void){
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}
