#include "stm32f10x.h"                  // Device header
#include "Motor.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Motor_Init();
	
	Car_Forward(500);
	//Car_Backward(500);
	//Car_TurnLeft(500);
	//Car_TurnRight(500);
	//Car_TransLeft(500);
	//Car_TransRight(500);
	while(1)
	{
		
	}
}


