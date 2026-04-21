#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void){
	//1流水灯配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	//2蜂鸣器配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure2;
	GPIO_Initstructure2.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure2.GPIO_Pin = GPIO_Pin_12;
	GPIO_Initstructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure2);
	
	while(1){
		GPIO_Write(GPIOA,~0x0001);//0000 0000 0000 0001
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0002);//0000 0000 0000 0010
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0004);//0000 0000 0000 0100
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0008);//0000 0000 0000 1000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0010);//0000 0000 0001 0000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0020);//0000 0000 0010 0000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0040);//0000 0000 0100 0000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0080);//0000 0000 1000 0000
		Delay_ms(500);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
		Delay_ms(700);
	}
}
