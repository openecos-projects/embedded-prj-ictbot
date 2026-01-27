#include "driver/uart.h"
#include "module/lu9685.h"

void Timer_Init() {
    timer_init(1, 100000);
}

void Timer_DelayMs(uint32_t val) {
    TIMER_0_REG_CTRL = (uint32_t)0xD;
    for (int i = 0; i < val; ++i) {
        while (TIMER_0_REG_STAT == 0);
    }
    TIMER_0_REG_CTRL = (uint32_t)0xD;
}

void I2C_Init() {
    i2c_config();
}

void main() {
    Timer_Init();
    I2C_Init();
    UART_Init();

    LU9685Struct servo_arr;
    uint8_t      servo_arr_len = 0;
    uint8_t      servo_action  = 0;
    LU9685_Init(&servo_arr, &servo_arr_len);

    while (1) {
        while (((UART1_REG_LSR & 0x080) >> 7) == 1);
        uint8_t uart_flag = UART_RecvData(UART1_REG_TRX, &servo_action);
        if (uart_flag == UART_STATUS_SUCCESS) {
            UART_SendData(uart_flag);
            LU9685_SetAction(&servo_arr, servo_arr_len, servo_action);
        }
        else if (uart_flag == UART_STATUS_ERROR) {
            UART_SendData(uart_flag);
        }
        else {
        }
    }
}