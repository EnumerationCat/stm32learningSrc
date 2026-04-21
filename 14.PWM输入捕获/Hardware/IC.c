#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_6;
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
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//PSC 预分频几个72Mhz计数1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	//自动交叉反向配置
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
	
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFreq(void)
{
	return 1000000/(TIM_GetCapture1(TIM3)+1);
}

uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
}
