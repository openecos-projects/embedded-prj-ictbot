#ifndef UART_H
#define UART_H

#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <ysyx.h>

#define UART1_BASE_ADDR    0x10001000
#define UART1_REG_LCR      *((volatile uint32_t *)(UART1_BASE_ADDR + 0))
#define UART1_REG_DIV      *((volatile uint32_t *)(UART1_BASE_ADDR + 4))
#define UART1_REG_TRX      *((volatile uint32_t *)(UART1_BASE_ADDR + 8))
#define UART1_REG_FCR      *((volatile uint32_t *)(UART1_BASE_ADDR + 12))
#define UART1_REG_LSR      *((volatile uint32_t *)(UART1_BASE_ADDR + 16))

#define PRINT_ARR(arr) \
    for (uint8_t i = 0; i < LENGTH(arr); i++) { \
        printf("0x%x", arr[i]);                 \
        if (i < LENGTH(arr) - 1) { \
            printf(", "); \
        }\
        else { \
            printf("]"); \
        } \
    }                                           \
    printf("\n");                               \


#endif
