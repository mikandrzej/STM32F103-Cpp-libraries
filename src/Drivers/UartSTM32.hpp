#pragma once

#include "UartBase.hpp"

#define ERR_EGUART_WORDLEN ERR_DEF(ERR_EGUART_GROUP, 0x1u)
#define ERR_EGUART_PARITY ERR_DEF(ERR_EGUART_GROUP, 0x2u)
#define ERR_EGUART_STOPBITS ERR_DEF(ERR_EGUART_GROUP, 0x3u)
#define ERR_EGUART_MODE ERR_DEF(ERR_EGUART_GROUP, 0x4u)
#define ERR_EGUART_HWCTRL ERR_DEF(ERR_EGUART_GROUP, 0x5u)
#define ERR_EGUART_HAL ERR_DEF(ERR_EGUART_GROUP, 0x6u)

class EgUartSTM32 : public EgUartBase
{
public:
    EgUartSTM32(e_egUartHandler handler);
    err_code Init(const uint32_t baudrate,
                  const e_egUartWordLen wordLength = EG_UART_WORDLEN_8,
                  const e_egUartParity parity = EG_UART_PARITY_NONE,
                  const e_egUartStopBits stopBits = EG_UART_STOPBITS_1,
                  const e_egUartMode mode = EG_UART_MODE_TXRX,
                  const uint32_t hwCtrl = EG_UART_HWCTRL_NONE);

    err_code Transmit(const char *const data,
                      const int len);

private:
    UART_HandleTypeDef huart = {0};
};

EgUartSTM32::EgUartSTM32(e_egUartHandler handler)
{
    USART_TypeDef *usartMapper[] = {
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
    if (handler >= (sizeof(usartMapper) / sizeof(usartMapper[0])))
    {
        while (true)
            ;
    }
    this->handler = handler;
    this->huart.Instance = usartMapper[handler];
}

err_code EgUartSTM32::Init(const uint32_t baudrate,
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
    uint32_t wordLengthMapper[] = {
        UART_WORDLENGTH_8B,
        UART_WORDLENGTH_9B,
    };
    huart.Init.WordLength = wordLengthMapper[wordLength];

    if (parity >= EG_UART_PARITY_MAX)
    {
        return ERR_EGUART_PARITY;
    }
    uint32_t parityMapper[] = {
        UART_PARITY_NONE,
        UART_PARITY_EVEN,
        UART_PARITY_ODD,
    };
    huart.Init.Parity = parityMapper[parity];

    if (stopBits >= EG_UART_STOPBITS_MAX)
    {
        return ERR_EGUART_STOPBITS;
    }
    uint32_t stopBitsMapper[] = {
        UART_STOPBITS_1,
        UART_STOPBITS_2,
    };
    huart.Init.StopBits = stopBitsMapper[stopBits];

    if (mode >= EG_UART_MODE_MAX)
    {
        return ERR_EGUART_MODE;
    }
    uint32_t modeMapper[] = {
        UART_MODE_TX,
        UART_MODE_RX,
        UART_MODE_TX_RX,
    };
    huart.Init.Mode = modeMapper[mode];

    if (hwCtrl >= EG_UART_HWCTRL_MAX)
    {
        return ERR_EGUART_HWCTRL;
    }
    uint32_t hwCtrlMapper[] = {
        UART_HWCONTROL_NONE,
        UART_HWCONTROL_RTS,
        UART_HWCONTROL_CTS,
        UART_HWCONTROL_RTS_CTS,
    };
    huart.Init.HwFlowCtl = hwCtrlMapper[hwCtrl];

    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_OK != HAL_UART_Init(&this->huart))
    {
        return ERR_EGUART_HAL;
    }

    this->initialized = true;
    return ERR_OK;
}

err_code EgUartSTM32::Transmit(const char *const data,
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
