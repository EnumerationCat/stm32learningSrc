#include "stm32f10x.h"                  // Device header

#include "Delay.h"
int main(void){
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//GPIO_InitTypeDef GPIO_Initstructure;
	//GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_Initstructure.GPIO_Pin = GPIO_Pin_13;
	//GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOC,&GPIO_Initstructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);
	//GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	while(1){
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(500);
	}
}
