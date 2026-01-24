#include "uart.h"

uint32_t uart_recv_arr_g[4] = {0};
uint8_t  uart_recv_cnt      = 0;

void UART_Init() {
    GPIO_0_REG_IOFCFG = (uint32_t)0x3;
    GPIO_0_REG_PINMUX = (uint32_t)0;

    // printf("REG_DIV: %x REG_LCR: %x\n", UART1_REG_DIV, UART1_REG_LCR);
    UART1_REG_DIV = (uint32_t)868;        // 100x10^6 / 115200
    UART1_REG_FCR = (uint32_t)0b1111;     // clear tx and rx fifo
    UART1_REG_FCR = (uint32_t)0b1100;
    UART1_REG_LCR = (uint32_t)0b00011111; // 8N1, en all irq
    printf("REG_DIV: %x REG_LCR: %x\n", UART1_REG_DIV, UART1_REG_LCR);
}

uint8_t UART_RecvData(uint32_t uart_data, uint8_t *servo_action_p) {
    uart_recv_arr_g[uart_recv_cnt] = uart_data;
    uart_recv_cnt++;

    if (uart_recv_cnt == 2) {
        if (uart_recv_arr_g[0] != 0xFF || uart_recv_arr_g[1] != 0xFF) {
            uart_recv_cnt = 0;
            printf("[uart] package header is invalid!\n");
        }
        else {
        }
    }
    else if (uart_recv_cnt == 4) {
        if ((uint8_t)(uart_recv_arr_g[0] + uart_recv_arr_g[1] + uart_recv_arr_g[2]) == uart_recv_arr_g[3]) {
            servo_action_p = &uart_recv_arr_g[2];
            printf("[uart] recv [");
            PRINT_ARR(uart_recv_arr_g);
            printf("[uart] checksum is ok!\n");
            uart_recv_cnt = 0;
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

void UART_SendData(uint8_t servo_flag) {
    printf("[uart] send response...\n");
    uint32_t data = (flag == 1) ? 0x00 :
                    (flag == 2) ? 0xFF : 0xFF;
    while (((UART1_REG_LSR & 0x100) >> 8) == 1);
    UART1_REG_TRX = data;
    printf("[uart] send response 0x%x done!\n", data);
}
