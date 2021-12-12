#include "UartSTM32HAL.hpp"

UART_HandleTypeDef *EgUartSTM32HAL::handlers[EG_UART_MAX] = {0};
USART_TypeDef *EgUartSTM32HAL::usartMapper[EG_UART_MAX] = {
#ifdef USART1
    USART1,
#endif
#ifdef USART2
    USART2,
#endif
#ifdef USART3
    USART3,
#endif
#ifdef USART4
    USART4,
#endif
#ifdef USART5
    USART5,
#endif
#ifdef USART6
    USART6,
#endif
#ifdef USART7
    USART7,
#endif
};
EgUartSTM32HAL *EgUartSTM32HAL::uartObjects[7] = {0};

EgUartSTM32HAL::EgUartSTM32HAL(e_egUartHandler handler)
{
    if (handler >= EG_UART_MAX)
    {
        while (true)
            ;
    }
    this->handler = handler;
    this->huart.Instance = usartMapper[handler];
    this->handlers[handler] = &this->huart;
    this->uartObjects[handler] = this;
}

err_code EgUartSTM32HAL::Init(const uint32_t baudrate,
                              const char *messageTerminator,
                              const int messageTerminatorLen,
                              const e_egUartWordLen wordLength,
                              const e_egUartParity parity,
                              const e_egUartStopBits stopBits,
                              const e_egUartMode mode,
                              const uint32_t hwCtrl)
{
    huart.Init.BaudRate = baudrate;

    if (wordLength >= EG_UART_WORDLEN_MAX)
    {
        return ERR_EGUART_WORDLEN;
    }
    const uint32_t wordLengthMapper[] = {
        UART_WORDLENGTH_8B,
        UART_WORDLENGTH_9B,
    };
    huart.Init.WordLength = wordLengthMapper[wordLength];
    this->baudrate = baudrate;

    if (parity >= EG_UART_PARITY_MAX)
    {
        return ERR_EGUART_PARITY;
    }
    const uint32_t parityMapper[] = {
        UART_PARITY_NONE,
        UART_PARITY_EVEN,
        UART_PARITY_ODD,
    };
    huart.Init.Parity = parityMapper[parity];
    this->wordLength = wordLength;

    if (stopBits >= EG_UART_STOPBITS_MAX)
    {
        return ERR_EGUART_STOPBITS;
    }
    const uint32_t stopBitsMapper[] = {
        UART_STOPBITS_1,
        UART_STOPBITS_2,
    };
    huart.Init.StopBits = stopBitsMapper[stopBits];
    this->stopBits = stopBits;

    if (mode >= EG_UART_MODE_MAX)
    {
        return ERR_EGUART_MODE;
    }
    const uint32_t modeMapper[] = {
        UART_MODE_TX,
        UART_MODE_RX,
        UART_MODE_TX_RX,
    };
    huart.Init.Mode = modeMapper[mode];
    this->mode = mode;

    if (hwCtrl >= EG_UART_HWCTRL_MAX)
    {
        return ERR_EGUART_HWCTRL;
    }
    const uint32_t hwCtrlMapper[] = {
        UART_HWCONTROL_NONE,
        UART_HWCONTROL_RTS,
        UART_HWCONTROL_CTS,
        UART_HWCONTROL_RTS_CTS,
    };
    huart.Init.HwFlowCtl = hwCtrlMapper[hwCtrl];
    this->hwCtrl = hwCtrl;

    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_OK != HAL_UART_Init(&this->huart))
    {
        return ERR_EGUART_HAL;
    }

    huart.RxCpltCallback = this->RxCplCallback;
    huart.RxEventCallback = this->RxEventCallback;

    if (HAL_OK != HAL_UARTEx_ReceiveToIdle_IT(&this->huart, (uint8_t *)this->rx_buffer, UART_RX_BUF_SIZE))
    {
        return ERR_EGUART_HAL;
    }

    this->initialized = true;
    return ERR_OK;
}

err_code EgUartSTM32HAL::Transmit(const char *const data,
                                  const int len)
{
    if (!this->initialized)
    {
        return ERR_EGUART_NOT_INITIALIZED;
    }
    if (HAL_OK != HAL_UART_Transmit(&this->huart, (uint8_t *)data, len, 1000))
    {
        return ERR_EGUART_HAL;
    }
    return ERR_OK;
}

EgUartSTM32HAL *EgUartSTM32HAL::HuartToObject(UART_HandleTypeDef *huart)
{
    EgUartSTM32HAL *object = nullptr;
    for (unsigned int i = 0; i < EG_UART_MAX; i++)
    {
        if (huart->Instance == EgUartSTM32HAL::usartMapper[i])
        {
            object = uartObjects[i];
        }
    }
    return object;
}

void EgUartSTM32HAL::RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    EgUartSTM32HAL *object = EgUartSTM32HAL::HuartToObject(huart);
    if (nullptr == object)
    {
        return;
    }
    if (0u == Size)
    {
        Size = UART_RX_BUF_SIZE;
    }
    object->Receive(object->rx_buffer, Size);
    HAL_UARTEx_ReceiveToIdle_IT(&object->huart, (uint8_t *)object->rx_buffer, UART_RX_BUF_SIZE);
}

void EgUartSTM32HAL::RxCplCallback(UART_HandleTypeDef *huart)
{
    EgUartSTM32HAL::RxEventCallback(huart, 0u);
}

void EgUartSTM32HAL::IRQ_Handler(e_egUartHandler handler)
{
    HAL_UART_IRQHandler(EgUartSTM32HAL::handlers[handler]);
}
