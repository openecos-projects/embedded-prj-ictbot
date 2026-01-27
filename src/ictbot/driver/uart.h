#ifndef UART_H
#define UART_H

#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <ecos.h>

#define UART1_BASE_ADDR    0x10001000
#define UART1_REG_LCR      *((volatile uint32_t *)(UART1_BASE_ADDR + 0))
#define UART1_REG_DIV      *((volatile uint32_t *)(UART1_BASE_ADDR + 4))
#define UART1_REG_TRX      *((volatile uint32_t *)(UART1_BASE_ADDR + 8))
#define UART1_REG_FCR      *((volatile uint32_t *)(UART1_BASE_ADDR + 12))
#define UART1_REG_LSR      *((volatile uint32_t *)(UART1_BASE_ADDR + 16))

#define UART_STATUS_PASS    0
#define UART_STATUS_SUCCESS 1
#define UART_STATUS_ERROR   2

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

void UART_Init();
uint8_t UART_RecvData(uint32_t uart_data, uint8_t *servo_action_p);
void UART_SendData(uint8_t uart_flag);

#endif
