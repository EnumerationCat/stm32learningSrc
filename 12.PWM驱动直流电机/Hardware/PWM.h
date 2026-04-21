#ifndef __PWM_H
#define __PWM_H

void PWM1_Init(void);
void PWM2_Init(void);

void PWM1_SetCompare1(uint16_t Compare);
void PWM1_SetCompare2(uint16_t Compare);
void PWM2_SetCompare3(uint16_t Compare);
void PWM2_SetCompare4(uint16_t Compare);
#endif
