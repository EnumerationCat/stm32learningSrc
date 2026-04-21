#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "Led.h"
#include "Delay.h"



#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
uint8_t key_count = 0;            // 按键计数变量
uint8_t key_pressed = 0;

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
}

void Key_Scanf(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
	{
		Delay_ms(20);
		LED_Turn();
		
		
	}
	
}

// 按键外部中断初始化函数
void Key_EXTI_Init(void)
{
    // 1. 使能GPIOA和AFIO时钟（外部中断需AFIO辅助）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    
    // 2. 配置GPIOA.0为输入模式（上拉输入，默认高电平，按下接地为低电平）
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;          // 按键引脚PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      // 上拉输入（无外部上拉时启用）
    // 若按键外部接下拉电阻，可改为GPIO_Mode_IPD（下拉输入）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // 输入模式下速度无实际意义
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 3. 配置AFIO：将PA0映射到EXTI0中断线
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    
    // 4. 配置EXTI（外部中断线）
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;         // 中断线0（对应PA0）
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// 中断模式（非事件模式）
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发（按键按下时电平从高到低）
    // 若需支持按下+松开触发，可改为EXTI_Trigger_Rising_Falling（双边沿）
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;          // 使能中断线
    EXTI_Init(&EXTI_InitStructure);
    
    // 5. 配置NVIC（中断优先级控制器）
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;   // 对应EXTI0的中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级（0最高）
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     // 使能中断通道
    NVIC_Init(&NVIC_InitStructure);
}


void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		Delay_ms(20);  // 消抖
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		{
			key_pressed = 1;  // 置位按键标志
			LED_Turn();
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}