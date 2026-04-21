#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	//使用引脚的方式
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);低电平
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);高电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	//GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStruct.TIM_Period = 65536-1;//ARR   周期计数溢出值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1-1;//PSC 预分频几个72Mhz计数1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;
	//TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	//TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;
	
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3,ENABLE);
}
int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	
	return Temp;

}
