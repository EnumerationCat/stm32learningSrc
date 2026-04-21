#ifndef __INFRAREDPSWITCH_H
#define __INFRAREDPSWITCH_H

#define Switch1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define Switch2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
#define Switch3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define Switch4 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define Switch5 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define Switch6 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define Switch7 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)
#define Switch8 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define Switch9 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define Switch10 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)

void InfraredPSwitch_Init(void);
void InfraredPSwitch_Check(void);
void EXTI_Config(void);

#endif
