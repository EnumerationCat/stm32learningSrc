#ifndef __MOTOR_H
#define __MOTOR_H

void Motor1_Init(void);
void Motor2_Init(void);
void Motor3_Init(void);
void Motor4_Init(void);
	
void Motor1_Forward(int8_t Speed);
void Motor1_Back(int8_t Speed);
void Motor2_Forward(int8_t Speed);
void Motor2_Back(int8_t Speed);
void Motor3_Forward(int8_t Speed);
void Motor3_Back(int8_t Speed);
void Motor4_Forward(int8_t Speed);
void Motor4_Back(int8_t Speed);

void Motor_SetSpeed(int8_t Speed1,int8_t Speed2,int8_t Speed3,int8_t Speed4);
void Car_Forward(int8_t Speed);
void Car_Backward(void);
void Car_Stop(void);

void Car_Transleft(void);
void Car_Transright(void);

#endif
