#include "uart.h"
#include "loader.h"

int main(void)
{
	Uart_Init();

	Loader_Process();

    while(1)
    {

    }
}


//#define USE_FULL_ASSERT
#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
  }
}
#endif

void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}
