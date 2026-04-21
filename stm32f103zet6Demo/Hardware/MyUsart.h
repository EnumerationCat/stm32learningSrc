#ifndef _MYUSART_h
#define _MYUSART_h

void MyUsart1_Init(void);
void USART_SendString(USART_TypeDef* USARTx, char* str);
extern char rx_buf[];
extern uint8_t rx_len;
extern uint8_t send_en;
extern uint8_t rx_complete;
#endif
