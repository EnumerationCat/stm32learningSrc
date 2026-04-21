#include "stm32f10x.h"                  // Device header
#include "PWM.h"

//电机1初始化
void Motor1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//时钟开启
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	PWM1_Init();
}
//电机2初始化
void Motor2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//时钟开启
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	PWM1_Init();
}
//电机3初始化
void Motor3_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//时钟开启
	//引脚重映射
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	PWM2_Init();
}
//电机4初始化
void Motor4_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//时钟开启
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	PWM2_Init();
}

void Motor1_Forward(int8_t Speed)
{
	
	GPIO_SetBits(GPIOA,GPIO_Pin_2 );
	GPIO_ResetBits(GPIOA,GPIO_Pin_3 );
	PWM1_SetCompare1(Speed);		
				
}
void Motor1_Back(int8_t Speed)
{
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_2 );
	GPIO_SetBits(GPIOA,GPIO_Pin_3 );
	PWM1_SetCompare1(Speed);		
				
}
void Motor2_Forward(int8_t Speed)
{
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	PWM1_SetCompare2(Speed); 
	
}
void Motor2_Back(int8_t Speed)
{
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	PWM1_SetCompare2(Speed); 
	
}

void Motor3_Forward(int8_t Speed)
{   
	GPIO_SetBits(GPIOB,GPIO_Pin_3);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	PWM2_SetCompare3(Speed);    
}
void Motor3_Back(int8_t Speed)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	GPIO_SetBits(GPIOB,GPIO_Pin_4);
	PWM2_SetCompare3(Speed);    
}
void Motor4_Forward(int8_t Speed)
{   
	GPIO_SetBits(GPIOB,GPIO_Pin_5 );
	GPIO_ResetBits(GPIOB,GPIO_Pin_6 );
	PWM2_SetCompare4(Speed);    
}
void Motor4_Back(int8_t Speed)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5 );
	GPIO_SetBits(GPIOB,GPIO_Pin_6 );
	PWM2_SetCompare4(Speed);    
}
//单独设置四个轮子正反转
void Motor_SetSpeed(int8_t Speed1,int8_t Speed2,int8_t Speed3,int8_t Speed4)
{
	if(Speed1>0)
	{
		Motor1_Forward(Speed1);
	}
	else
	{
		Motor1_Back(-Speed1);
	}
	if(Speed2>0)
	{
		Motor2_Forward(Speed2);
	}
	else
	{
		Motor2_Back(-Speed2);
	}
	if(Speed3>0)
	{
		Motor3_Forward(Speed3);
	}
	else
	{
		Motor3_Back(-Speed3);
	}
	if(Speed4>0)
	{
		Motor4_Forward(Speed4);
	}
	else
	{
		Motor4_Back(-Speed4);
	}
}
void Car_Forward(int8_t Speed)
{
	Motor1_Forward(Speed);
	Motor2_Forward(Speed);
	Motor3_Forward(Speed);
	Motor4_Forward(Speed);
}
void Car_Backward(void)
{
	Motor1_Back(40);
	Motor2_Back(40);
	Motor3_Back(40);
	Motor4_Back(40);
}
void Car_Stop(void)
{
	Motor1_Forward(0);
	Motor2_Forward(0);
	Motor3_Forward(0);
	Motor4_Forward(0);
}
void Car_Transleft(void)
{	
	Motor_SetSpeed(-40,40,40,-40);
	
}
void Car_Transright(void)
{
	Motor_SetSpeed(40,-40,-40,40);
}
