#include "uart.h"
#include "stm32f10x.h"

void Uart_Init()
{
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE );

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef gpio;

	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init( USART2, &USART_InitStructure );
	USART_Cmd(USART2, ENABLE);
}

void Uart_Deinit()
{
	GPIO_DeInit(GPIOA);
	USART_DeInit(USART2);
}

void Uart_SendByte(uint8_t byte)
{
	USART_SendData( USART2, byte );
	while ( USART_GetFlagStatus( USART2, USART_FLAG_TXE ) == RESET ) {
	}
}

void Uart_SendBuffer(uint8_t* buffer, uint16_t bufferSize)
{
	int i;
	for (i = 0; i < bufferSize; ++i) {
		Uart_SendByte(buffer[i]);
	}
}

bool Uart_GetByte(uint8_t *ptrData)
{
	if ( USART_GetFlagStatus( USART2, USART_FLAG_RXNE ) != RESET ) {
		*ptrData = (uint8_t) USART2->DR;
		return true;
	}
	else {
		return false;
	}
}
