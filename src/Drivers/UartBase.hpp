#pragma once

#include <stdint.h>
#include <stm32f103xb.h>
#include "stm32f1xx_hal_conf.h"

#include "../Common/error.hpp"

#define ERR_EGUART_NOT_INITIALIZED ERR_DEF(ERR_EGUART_GROUP, 0x01u)

typedef enum
{
    EG_UART1,
    EG_UART2,
    EG_UART3,
    EG_UART4,
    EG_UART5,
    EG_UART6,
    EG_UART7,
    EG_UART_MAX
} e_egUartHandler;

typedef enum
{
    EG_UART_WORDLEN_8,
    EG_UART_WORDLEN_9,
    EG_UART_WORDLEN_MAX
} e_egUartWordLen;

typedef enum
{
    EG_UART_PARITY_NONE,
    EG_UART_PARITY_EVEN,
    EG_UART_PARITY_ODD,
    EG_UART_PARITY_MAX
} e_egUartParity;

typedef enum
{
    EG_UART_STOPBITS_1,
    EG_UART_STOPBITS_2,
    EG_UART_STOPBITS_MAX
} e_egUartStopBits;

typedef enum
{
    EG_UART_MODE_TX,
    EG_UART_MODE_RX,
    EG_UART_MODE_TXRX,
    EG_UART_MODE_MAX
} e_egUartMode;

typedef enum
{
    EG_UART_HWCTRL_NONE,
    EG_UART_HWCTRL_RTS,
    EG_UART_HWCTRL_CTS,
    EG_UART_HWCTRL_RTSCTS,
    EG_UART_HWCTRL_MAX
} e_egUartHwCtrl;

class EgUartBase
{
public:
    virtual err_code Init(const uint32_t baudrate,
                          const e_egUartWordLen wordLength = EG_UART_WORDLEN_8,
                          const e_egUartParity parity = EG_UART_PARITY_NONE,
                          const e_egUartStopBits stopBits = EG_UART_STOPBITS_1,
                          const e_egUartMode mode = EG_UART_MODE_TXRX,
                          const uint32_t hwCtrl = EG_UART_HWCTRL_NONE)
    {
        return ERR_GENERAL;
    }

    virtual err_code Transmit(const char *const data,
                              const int len)
    {
        return ERR_GENERAL;
    }

protected:
    e_egUartHandler handler;
    volatile bool initialized = false;
    uint32_t baudrate;
    e_egUartWordLen wordLength;
    e_egUartParity parity;
    e_egUartStopBits stopBits;
    e_egUartMode mode;
    uint32_t hwCtrl;

private:
    void *operator new(size_t);
    void *operator new[](size_t);
    void operator delete(void *);
    void operator delete[](void *);
};
