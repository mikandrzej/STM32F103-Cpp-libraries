#include "Drivers/UartSTM32HAL.hpp"

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

    void USART1_IRQHandler(void)
    {
        EgUartSTM32HAL::IRQ_Handler(EG_UART1);
    }
    void USART2_IRQHandler(void)
    {
        EgUartSTM32HAL::IRQ_Handler(EG_UART2);
    }
    void USART3_IRQHandler(void)
    {
        EgUartSTM32HAL::IRQ_Handler(EG_UART3);
    }
    void USART4_IRQHandler(void)
    {
        EgUartSTM32HAL::IRQ_Handler(EG_UART4);
    }
    void USART5_IRQHandler(void)
    {
        EgUartSTM32HAL::IRQ_Handler(EG_UART5);
    }
    void USART6_IRQHandler(void)
    {
        EgUartSTM32HAL::IRQ_Handler(EG_UART6);
    }
    void USART7_IRQHandler(void)
    {
        EgUartSTM32HAL::IRQ_Handler(EG_UART7);
    }
}