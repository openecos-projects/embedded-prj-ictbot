#include "lu9685.h"

void LU9685_SetAngleSingle(uint8_t servo_idx, uint8_t servo_val) {
    printf("[lu9685] move servo %d to %d degree...\n", servo_idx, servo_val);
    I2C_Soft_WriteByteN(0x00, servo_idx, I2C_DEV_ADDR_8BIT, 1, &servo_val);
    printf("[lu9685] move servo done!\n");
}

void LU9685_SetAngleMulti(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {
    char servo_num_str[100] = {0};
    char servo_val_str[100] = {0};
    uint8_t servo_arr[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    for (uint8_t i = 0; i < servo_arr_len; i++) {
        for (uint8_t j = 0; j < LENGTH(servo_arr); j++) {
            if (servo_arr_p->num == j) {
                if (servo_num_str[0] == 0) {
                    sprintf(servo_num_str, "%d", j);
                    sprintf(servo_val_str, "%d", servo_arr_p->val);
                }
                else {
                    sprintf(servo_num_str, "%s, %d", servo_num_str, j);
                    sprintf(servo_val_str, "%s, %d", servo_val_str, servo_arr_p->val);
                }

                servo_arr[j] = servo_arr_p->val;
            }
            else {
            }
        }
        servo_arr_p++;
    }

    PRINT_ARR(servo_arr, "lu9685");
    printf("[lu9685] move servo [%s] to [%s] degrees...\n", servo_num_str,
                                                            servo_val_str);
    I2C_Soft_WriteByteN(0x00, 0xFD, I2C_DEV_ADDR_8BIT, LENGTH(servo_arr), servo_arr);
    printf("[lu9685] move servo done!\n");
}

void LU9685_SetAction(LU9685Struct *servo_arr_p, uint8_t servo_arr_len,
                                                 uint8_t servo_action) {
    printf("[lu9685] move servo action 0x%x...\n", servo_action);
    switch (servo_action) {
        case 0x01:
            LU9685_SetAction0X01(servo_arr_p, servo_arr_len);
            break;
        case 0x02:
            LU9685_SetAction0X02(servo_arr_p, servo_arr_len);
            break;
        case 0x03:
            LU9685_SetAction0X03(servo_arr_p, servo_arr_len);
            break;
        case 0x04:
            LU9685_SetAction0X04(servo_arr_p, servo_arr_len);
            break;
        case 0x05:
            LU9685_SetAction0X05(servo_arr_p, servo_arr_len);
            break;
        case 0x06:
            LU9685_SetAction0X06(servo_arr_p, servo_arr_len);
            break;
        case 0x07:
            LU9685_SetAction0X07(servo_arr_p, servo_arr_len);
            break;
        case 0x08:
            LU9685_SetAction0X08(servo_arr_p, servo_arr_len);
            break;
        case 0x09:
            LU9685_SetAction0X09(servo_arr_p, servo_arr_len);
            break;
        case 0x0A:
            LU9685_SetAction0X0A(servo_arr_p, servo_arr_len);
            break;
        default:
            printf("[lu9685] move servo action 0x%x is not supported!\n",
                   servo_action);
            break;
    }
    printf("[lu9685] move servo action done!\n\n");
}

void LU9685_SetAction0X01(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {
    for (uint8_t i = 0; i < 10; i++) {
        servo_arr_p[0].val = 80;
        servo_arr_p[1].val = 80;
        servo_arr_p[2].val = 80;
        servo_arr_p[3].val = 80;
        servo_arr_p[4].val = 80;
        for (uint8_t i = 0; i < 5; i++) {
            LU9685_SetAngleSingle(servo_arr_p[i].num, servo_arr_p[i].val);
        }
        Timer_DelayMs(300);

        servo_arr_p[0].val = 110;
        servo_arr_p[1].val = 110;
        servo_arr_p[2].val = 110;
        servo_arr_p[3].val = 110;
        servo_arr_p[4].val = 110;
        for (uint8_t i = 0; i < 5; i++) {
            LU9685_SetAngleSingle(servo_arr_p[i].num, servo_arr_p[i].val);
        }
        Timer_DelayMs(300);
    }
}

void LU9685_SetAction0X02(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X03(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X04(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X05(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X06(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X07(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X08(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X09(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}

void LU9685_SetAction0X0A(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {}