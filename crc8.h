#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void Crc8_Init();
uint8_t Crc8_Step(uint8_t byte);
uint8_t Crc8_GetData();
uint8_t Crc8(uint8_t *buffer, size_t size);

#ifdef __cplusplus
}
#endif
