#include "stm32f10x.h"                  // Device header
#include "MyUsart.h"
#include "Key.h"
#include "MyTim.h"
#include "Led.h"
// 新增接收缓冲区
char rx_buf[50];
uint8_t rx_len = 0;
uint8_t rx_complete = 0;
uint8_t send_en = 0;  // 发送使能标志（0:接收模式 1:发送模式）


void MyUsart1_Init(void)
{
	 // 1. 使能时钟（USART1和GPIOA）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
    
    // 2. 配置GPIO（TX:PA9复用推挽，RX:PA10浮空输入）
    GPIO_InitTypeDef GPIO_InitStruct;
    // TX引脚（PA9）：复用推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽（串口功能）
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	
    // RX引脚（PA10）：浮空输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // 浮空输入（接收数据）
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 3. 配置USART参数（波特率、数据位、停止位等）
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 115200;         // 波特率115200
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;  // 8位数据
    USART_InitStruct.USART_StopBits = USART_StopBits_1;      // 1位停止位
    USART_InitStruct.USART_Parity = USART_Parity_No;         // 无校验
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // 无硬件流控
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 收发模式
    USART_Init(USART1, &USART_InitStruct);  // 初始化USART1
    
    // 4. （可选）配置中断（如接收中断）
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;  // USART1中断通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;  // 抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;         // 子优先级
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  // 使能接收中断（数据非空）
    
    // 5. 使能USART1
    USART_Cmd(USART1, ENABLE);
	
}

// 新增字符串发送函数
void USART_SendString(USART_TypeDef* USARTx, char* str)
{
	while(*str != '\0')
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
		USART_SendData(USARTx, *str);
		str++;
	}
	// 发送换行符
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(USARTx, '\r');
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(USARTx, '\n');
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		uint8_t data = USART_ReceiveData(USART1);
		
		if(send_en == 0)  // 接收模式处理命令
		{
			// 处理字符串命令（以回车换行结束）
			if(data == '\r' || data == '\n')
			{
				rx_buf[rx_len] = '\0';
				rx_complete = 1;
				rx_len = 0;
			}
			else
			{
				rx_buf[rx_len++] = data;
				if(rx_len >= 49) rx_len = 0;  // 防止溢出
			}
			
			// 处理16进制命令
			if(data == 0x01)       // 接收0x01：开启循环
			{
				led_force = 0;
			}
			else if(data == 0x02)  // 接收0x02：关闭LED
			{
				led_force = 1;
				LED_Off();
			}
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


/*处理按键按下事件
		if(key_pressed == 1)
		{
			Delay_ms(20);  // 二次消抖
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
			{
				key_count++;
				if(key_count % 2 == 1)  // 奇数次按下：启动发送
				{
					send_en = 1;
				}
				else  // 偶数次按下：停止发送，进入接收模式
				{
					send_en = 0;
				}
			}
			key_pressed = 0;  // 清零标志
		}
		
		// 处理串口发送
		if(send_en == 1 && send_flag == 1)
		{
			USART_SendString(USART1, send_str);
			send_flag = 0;
		}
		
		// 处理串口接收命令
		if(send_en == 0 && rx_complete == 1)
		{
			if(strcmp(rx_buf, "ON") == 0)  // 接收"ON"：开启循环
			{
				led_force = 0;
			}
			else if(strcmp(rx_buf, "OFF") == 0)  // 接收"OFF"：关闭LED
			{
				led_force = 1;
				LED_Off();
			}
			rx_complete = 0;  // 清零标志
		}*/


