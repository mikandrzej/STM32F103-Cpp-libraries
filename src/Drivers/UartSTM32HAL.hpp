#pragma once

#include "UartBase.hpp"

#define ERR_EGUART_WORDLEN ERR_DEF(ERR_EGUART_GROUP, 0x1u)
#define ERR_EGUART_PARITY ERR_DEF(ERR_EGUART_GROUP, 0x2u)
#define ERR_EGUART_STOPBITS ERR_DEF(ERR_EGUART_GROUP, 0x3u)
#define ERR_EGUART_MODE ERR_DEF(ERR_EGUART_GROUP, 0x4u)
#define ERR_EGUART_HWCTRL ERR_DEF(ERR_EGUART_GROUP, 0x5u)
#define ERR_EGUART_HAL ERR_DEF(ERR_EGUART_GROUP, 0x6u)

#if defined(USART7)
#define EG_UART_MAX 7u
#elif defined(USART6)
#define EG_UART_MAX 6u
#elif defined(USART5)
#define EG_UART_MAX 5u
#elif defined(USART4)
#define EG_UART_MAX 4u
#elif defined(USART3)
#define EG_UART_MAX 3u
#elif defined(USART2)
#define EG_UART_MAX 2u
#elif defined(USART1)
#define EG_UART_MAX 1u
#endif

#define UART_RX_BUF_SIZE 128u
#define UART_TX_BUF_SIZE 128u

class EgUartSTM32HAL : public EgUartBase
{
public:
    EgUartSTM32HAL(e_egUartHandler handler);
    err_code Init(const uint32_t baudrate,
                  const char *messageTerminator = "\r\n",
                  const int messageTerminatorLen = sizeof("\r\n"),
                  const e_egUartWordLen wordLength = EG_UART_WORDLEN_8,
                  const e_egUartParity parity = EG_UART_PARITY_NONE,
                  const e_egUartStopBits stopBits = EG_UART_STOPBITS_1,
                  const e_egUartMode mode = EG_UART_MODE_TXRX,
                  const uint32_t hwCtrl = EG_UART_HWCTRL_NONE);

    err_code Transmit(const char *const data,
                      const int len);
    static void IRQ_Handler(e_egUartHandler handler);

private:
    static EgUartSTM32HAL *HuartToObject(UART_HandleTypeDef *huart);
    UART_HandleTypeDef huart = {0};
    static void RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
    static void RxCplCallback(UART_HandleTypeDef *huart);
    char rx_buffer[UART_RX_BUF_SIZE];
    char tx_buffer[UART_TX_BUF_SIZE];
    static UART_HandleTypeDef *handlers[];
    static EgUartSTM32HAL *uartObjects[];
    static USART_TypeDef *usartMapper[];
};