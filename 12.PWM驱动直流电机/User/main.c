#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"   
#include "InfraredPSwitch.h"
#include "PWM.h"

uint16_t flag1;
int8_t Speed;
int main(void){
	OLED_Init();
	InfraredPSwitch_Init();
	EXTI_Config();
	Motor1_Init(); 
	Motor2_Init();
	Motor3_Init();
	Motor4_Init();
	while(1){
		InfraredPSwitch_Check();
		
		while(Switch1==0)
		{
			Car_Forward(40);
		}
	    //Car_Transright();
		//Car_Transleft();
		/*if(flag1==0)
		{
			Car_Forward(40);
		}
		if(flag1>0)
		{
			Car_Transleft();
		}*/
		

    }
}
//EXTI0中断服务程序
void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        // 执行中断处理代码
		while(Switch1==1)
		{
			Car_Transleft();
        // 清除中断标志位
		}
        EXTI_ClearITPendingBit(EXTI_Line0);
    

   }
}
void EXTI1_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
        // 执行中断处理代码
		while(Switch2==0){
		
			Car_Backward();
		}
		
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line1);
    }

}
void EXTI2_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
        // 执行中断处理代码
		while(Switch3==1)
		{
			Car_Transleft();
		}
		
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line2);
    }

}
