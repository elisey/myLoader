#include "flash_driver.h"
#include "stm32f10x.h"
#include <stdbool.h>
void FlashDriver_WriteBuffer(uint32_t *buf, uint16_t size, uint32_t* address)
{
	assert_param(IS_FLASH_ADDRESS((uint32_t)address));

	FLASH_Status status;
	uint16_t i;
	uint32_t *ptrSourse = buf;

	FLASH_Unlock();
	for (i = 0; i < (size / 4); ++i) {
		status = FLASH_ProgramWord((uint32_t)address, *ptrSourse);
		ptrSourse++;
		address++;
		if (status != FLASH_COMPLETE)	{
			while(1);
		}
	}
	FLASH_Lock();
}

void FlashDriver_ErasePage(uint32_t* address)
{
	assert_param(IS_FLASH_ADDRESS((uint32_t)address));

	if (FlashDriver_isPageErased(address) == true)	{
		return;
	}

	FLASH_Status status;

	FLASH_Unlock();
	status = FLASH_ErasePage( (uint32_t) address);
	FLASH_Lock();

	if (status != FLASH_COMPLETE)	{
		while(1);
	}
}

bool FlashDriver_isPageErased(uint32_t* address)
{
	uint16_t i;
	for (i = 0; i < (PAGE_SIZE / 4); ++i) {
		if (*address != 0xffffffff)	{
			return false;
		}
		address++;
	}
	return true;
}
