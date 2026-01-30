#include "uart.h"

uint32_t uart_recv_arr_g[4] = {0};
uint8_t  uart_recv_cnt_g    =  0;

void UART_Init(uint32_t baud) {
    printf("[uart] init...\n");
    GPIO_0_REG_IOFCFG = (uint32_t)0x3;
    GPIO_0_REG_PINMUX = (uint32_t)0;

    // printf("REG_DIV: %x REG_LCR: %x\n", UART1_REG_DIV, UART1_REG_LCR);
    UART_1_REG_DIV = (uint32_t)(100000000 / baud);        // 100x10^6 / 115200
    UART_1_REG_FCR = (uint32_t)0b1111;     // clear tx and rx fifo
    UART_1_REG_FCR = (uint32_t)0b1100;
    UART_1_REG_LCR = (uint32_t)0b00011111; // 8N1, en all irq
    printf("[uart] init done!\n");
}

uint8_t UART_RecvData(uint32_t uart_data, uint8_t *servo_action_p) {
    uint8_t uart_recv_arr_t = 0;

    uart_recv_arr_g[uart_recv_cnt_g] = uart_data;
    uart_recv_cnt_g++;

    printf("[uart] recv data is 0x%x\n", uart_data);

    if (uart_recv_cnt_g == 2) {
        if (uart_recv_arr_g[0] != 0xFF || uart_recv_arr_g[1] != 0xFF) {
            uart_recv_cnt_g = 0;
            printf("[uart] package header is invalid!\n");
        }
        else {
        }
    }
    else if (uart_recv_cnt_g == 4) {
        if ((uint8_t)(uart_recv_arr_g[0] + uart_recv_arr_g[1] + uart_recv_arr_g[2]) == uart_recv_arr_g[3]) {
            uart_recv_arr_t = (uint8_t)uart_recv_arr_g[2];
            servo_action_p = &uart_recv_arr_t;
            printf("[uart] recv [");
            PRINT_ARR(uart_recv_arr_g, "uart");
            printf("[uart] checksum is ok!\n");
            uart_recv_cnt_g = 0;
            return 1;
        }
        else {
            printf("[uart] checksum is invalid!\n");
            return 2;
        }
    }
    else {
    }

    return 0;
}

void UART_SendData(uint8_t uart_flag) {
    printf("[uart] send response...\n");
    uint32_t uart_data = (uart_flag == 1) ? 0x00 :
                         (uart_flag == 2) ? 0xFF : 0xFF;
    while (((UART_1_REG_LSR & 0x100) >> 8) == 1);
    UART_1_REG_TRX = uart_data;
    printf("[uart] send response 0x%x done!\n", uart_data);
}
