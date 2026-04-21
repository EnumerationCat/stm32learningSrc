#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOE,&GPIO_Initstructure);
}
uint8_t KeyNum = 0;

uint8_t Key_GetNum(void){
	
	
	
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0){
		Delay_ms(200);//按键消抖
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0);
		
		KeyNum = 1;
	
	}
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0){
		Delay_ms(200);//按键消抖
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0);

		KeyNum = 2;
	
	}
	return KeyNum;
}
