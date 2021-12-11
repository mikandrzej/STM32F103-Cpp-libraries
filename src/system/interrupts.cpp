extern "C"
{
#include "stm32f1xx_hal.h"
    /**
 * @brief Systick periodic 1ms interrupt handler
 * 
 */
    void SysTick_Handler(void)
    {
        HAL_IncTick();
    }
}