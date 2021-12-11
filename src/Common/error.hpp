#pragma once

#define ERROR_GROUP_SHIFT 8u
#define ERR_DEF(x, y) ((x << ERROR_GROUP_SHIFT) | y)

#define ERR_OK 0x00
#define ERR_HAL 0x01
#define ERR_GENERAL 0x02

#define ERR_EGUART_GROUP 0x01u

typedef uint32_t err_code;