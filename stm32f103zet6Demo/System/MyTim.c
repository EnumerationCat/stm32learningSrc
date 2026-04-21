#include "MyTim.h"
#include "Led.h"
#include <string.h>

unsigned char time_1ms=0;
unsigned char flag_5s=0;            // 修正为外部变量
unsigned char time_5s=0;
uint8_t send_flag=0;
char send_str[10];
uint8_t led_force=0;                // 初始不强制控制

void MyTIM3_Init(uint16_t arr,uint16_t psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;
	TIM_TimeBaseStructure.TIM_Prescaler =psc-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);						 
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		time_1ms++;
		time_5s++;

		// 5秒后切换到1秒周期
		if(time_5s == 5000)
		{
			flag_5s = 1;            // 修正赋值错误（==改为=）
			time_5s = 0;
		}

		// 根据周期标志控制LED翻转
		if(flag_5s == 0)           // 0.5秒周期
		{
			if(time_1ms == 500)
			{
				if(led_force == 0)   // 未强制控制时才翻转
					LED_Turn();
				time_1ms = 0;
				send_flag = 1;
				strcpy(send_str, "0.5S");  // 设置发送内容
			}
		}
		else                        // 1秒周期
		{
			if(time_1ms == 1000)
			{
				if(led_force == 0)
					LED_Turn();
				time_1ms = 0;
				send_flag = 1;
				strcpy(send_str, "1S");
			}
		}
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

// PWM初始化函数保持不变
void MyTIM3_PWM_Init(uint16_t arr,uint16_t psc)
{  
	// 原有代码不变
}
