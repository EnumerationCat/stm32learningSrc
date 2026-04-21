#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

extern unsigned char flag_5s;       // 周期切换标志（0:0.5s周期 1:1s周期）
extern uint8_t send_flag;           // 串口发送标志
extern char send_str[10];           // 串口发送字符串
extern uint8_t led_force;           // LED强制控制标志（0:正常循环 1:强制控制）

void MyTIM3_Init(uint16_t arr,uint16_t psc);
void MyTIM3_PWM_Init(uint16_t arr,uint16_t psc);
#endif
