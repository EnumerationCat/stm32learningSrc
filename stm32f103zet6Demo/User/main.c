
#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "Led.h"
#include "MyTim.h"

#include "oled.h"

#include "MyUsart.h"
#include "string.h"
#include "Delay.h"

 
int main(void) 
{ 
	 
	
	OLED_Init();
	 // 清屏
  OLED_Clear();

    // 显示字符串
  OLED_ShowString(0, 0, "Hello OLED!", 16);  // 在(0,0)显示16号字体
  OLED_ShowString(0, 20, "STM32F103", 12);    // 在(0,20)显示12号字体
	OLED_Refresh_Gram();  		
	
	while(1)
	{
		
	}
}
