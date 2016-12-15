#pragma once
#include <stdint.h>
#include <stdbool.h>

void Uart_Init();
void Uart_Deinit();
void Uart_SendByte(uint8_t byte);
void Uart_SendBuffer(uint8_t* buffer, uint16_t bufferSize);

bool Uart_GetByte(uint8_t *ptrData);
