#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x.h"		//for PAGE_SIZE

#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL)	|| defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
	#define PAGE_SIZE  (uint16_t)0x400  /* Page size = 1KByte */
#elif defined (STM32F10X_HD) || defined (STM32F10X_CL)
	#define flash_addressingPAGE_SIZE  (uint16_t)0x800  /* Page size = 2KByte */
#endif


void FlashDriver_WriteBuffer(uint32_t *buf, uint16_t size, uint32_t* address);
void FlashDriver_ErasePage(uint32_t* address);
bool FlashDriver_isPageErased(uint32_t* address);
