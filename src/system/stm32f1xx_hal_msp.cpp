extern "C"
{

#include "stm32f1xx_hal.h"

  /**
  * Initializes the Global MSP.
  */
  void HAL_MspInit(void)
  {

    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();
  }
}