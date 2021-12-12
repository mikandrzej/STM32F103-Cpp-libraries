#include <stdlib.h>
#include <stdint.h>

#include "Drivers/UartSTM32HAL.hpp"
#include "stm32f1xx_hal.h"

#include "Libraries/ProducerConsumer.hpp"

void SystemClock_Config(void);
void Error_Handler(void);

// EgUartSTM32 uart(EG_UART1);
EgUartSTM32HAL uart2(EG_UART2);


void RecvCallbackUart2a(ReceiveCallbackArgs_s arg)
{
    uart2.Transmit(arg.buf, arg.len);
}
void RecvCallbackUart2b(ReceiveCallbackArgs_s arg)
{
    uart2.Transmit(arg.buf, arg.len);
}
void RecvCallbackUart2c(ReceiveCallbackArgs_s arg)
{
    uart2.Transmit(arg.buf, arg.len);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    EgUartBase *eguart2 = &uart2;
    eguart2->Init(115200);

    eguart2->RegisterReceiveCallback(RecvCallbackUart2a);
    eguart2->RegisterReceiveCallback(RecvCallbackUart2b);
    eguart2->RegisterReceiveCallback(RecvCallbackUart2c);

    while (true)
    {

        // eguart1->Transmit("abc\r\n", 5);
        // eguart2->Transmit("def\r\n", 5);
    }

    return 0;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}