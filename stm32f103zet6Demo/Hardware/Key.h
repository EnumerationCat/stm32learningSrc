#ifndef _KEY_H
#define _KEY_H

extern uint8_t key_pressed;
extern uint8_t key_count;           // 按键按下次数计数

void Key_Init(void);
void Key_Scanf(void);
void Key_EXTI_Init(void);
#endif
