#include "loader.h"
#include "uart.h"
#include "flash_driver.h"

static uint8_t getByte();
static void sendAck();
static void sendNack();
static void jumpToCode();

#define USER_APP_ADDRESS	0x8001400
uint8_t rxBuffer[PAGE_SIZE];



void Loader_Process()
{
	uint8_t crc = 0;

	while(1)
	{
		Crc8_Init();
		uint8_t data = getByte();

		if (data == 1)	{
			data = getByte();

			if (Crc8_GetData() == data)	{
				sendAck();
				jumpToCode();
			}
			else {
				sendNack();
			}
		}
		else if (data == 2)	{
			uint32_t address = 0;
			address = getByte();
			address |= (getByte() << 8);
			address |= (getByte() << 16);
			address |= (getByte() << 24);

			int i;
			for (i = 0; i < PAGE_SIZE; ++i) {
				rxBuffer[i] = getByte();
			}
			FlashDriver_ErasePage((uint32_t*)address);
			FlashDriver_WriteBuffer((uint32_t*)rxBuffer, PAGE_SIZE, (uint32_t*) address);
			sendAck();
		}
		else if (data == 3)	{
			uint32_t address = 0;
			address = getByte();
			address |= (getByte() << 8);
			address |= (getByte() << 16);
			address |= (getByte() << 24);

			uint8_t numOfBytes = getByte();

			uint8_t *ptr = (uint8_t*)address;

			int i;
			for (i = 0; i < numOfBytes; ++i) {
				Uart_SendByte(*ptr);
				ptr++;
			}


		}
		else if (data == 4)	{
			sendAck();
		}
		else if (data == 5)	{
			uint32_t address = 0;
			address = getByte();
			address |= (getByte() << 8);
			address |= (getByte() << 16);
			address |= (getByte() << 24);

			uint8_t numOfBytes = getByte();

			int i;
			for (i = 0; i < numOfBytes; ++i) {
				rxBuffer[i] = getByte();
			}

			//TODO запись в память
			sendAck();

		}

	}
}

static uint8_t getByte()
{
	while(1)
	{
		uint8_t data = 0;

		if (Uart_GetByte(&data) == true)	{
			Crc8_Step(data);
			return data;
		}
	}
}

static void sendAck()
{
	Uart_SendByte(55);
}

static void sendNack()
{
	Uart_SendByte(56);
}

typedef  void (*pFunction)(void);

static void jumpToCode()
{
	Uart_Deinit();

	uint32_t JumpAddress = *(__IO uint32_t*) (USER_APP_ADDRESS + 4);

	/* Jump to user application */
	pFunction Jump_To_Application = (pFunction) JumpAddress;
	/* Initialize user application's Stack Pointer */
	__set_MSP( *(__IO uint32_t*) USER_APP_ADDRESS );
	Jump_To_Application();
}
