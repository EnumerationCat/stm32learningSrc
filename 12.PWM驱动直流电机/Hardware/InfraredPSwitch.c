#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "InfraredPSwitch.h"
//光电开关初始化
extern uint16_t flag1;
void InfraredPSwitch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);
}
//配置外部中断
void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
 
    // 使能AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
 
    // 配置光电开关引脚为外部中断
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
 
    // 配置外部中断线
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发或者EXTI_Trigger_Rising
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	//EXTI_ClearFlag(EXTI_Line0);
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_Init(&EXTI_InitStructure);
 
    // 配置中断优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}
//检查光电开关引脚电平
void InfraredPSwitch_Check(void)
{
	    OLED_Clear();
		OLED_ShowString(1,1,"d1:");
		OLED_ShowNum(1, 4, Switch1, 2);
		OLED_ShowString(2,1,"d2:");
		OLED_ShowNum(2, 4, Switch2, 2);
		OLED_ShowString(3,1,"flag3:");
		OLED_ShowNum(3, 4, Switch3, 2);
		OLED_ShowString(4,1,"d4:");
		OLED_ShowNum(4, 4, Switch4, 2);
		OLED_ShowString(4,6,"d5:");
		OLED_ShowNum(4,10, Switch5, 1);
}
// EXTIX中断服务程序
/*void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        // 执行中断处理代码
		

        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}*/
