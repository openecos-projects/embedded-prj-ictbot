#include "lu9685.h"

void LU9685_Init(LU9685Struct *servo_arr_p, uint8_t *servo_arr_len_p) {
    LU9685Struct servo_arr[] = {
        {3, 0},
        {4, 0},
        {5, 0},
        {6, 0},
        {7, 0}
    };
    uint8_t servo_arr_len = LENGTH(servo_arr);

    servo_arr_p     = &servo_arr;
    servo_arr_len_p = &servo_arr_len;
}

void LU9685_Reset() {
    printf("[lu9685] reset servo...\n");
    i2c_wr_nbyte(0x00, 0xFB, I2C_DEV_ADDR_8BIT, 1, (uint8_t *)0xFB);
    printf("[lu9685] reset servo done!\n");
}

void LU9685_SetAngleSingle(uint8_t servo_idx, uint8_t servo_val) {
    printf("[lu9685] move servo %d to %d degree...\n", servo_idx, servo_val);
    i2c_wr_nbyte(0x00, servo_idx, I2C_DEV_ADDR_8BIT, 1, &servo_val);
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

    printf("[lu9685] move servos [%s] to [%s] degrees...\n", servo_num_str,
                                                             servo_val_str);
    i2c_wr_nbyte(0x00, 0xFD, I2C_DEV_ADDR_8BIT, LENGTH(servo_arr), servo_arr);
    printf("[lu9685] move servos done!\n");
}

void LU9685_SetAction(LU9685Struct *servo_arr_p, uint8_t servo_arr_len,
                                                 uint8_t servo_action) {
    printf("[lu9685] move servos to action 0x%x...\n", servo_action);
    switch (servo_action) {
        case 0x01:
            LU9685_SetAction0X01(servo_arr_p, servo_arr_len);
            break;
        case 0x02:
            break;
        default:
            break;
    }
    printf("[lu9685] move servos servo_act done!\n\n");
}

void LU9685_SetAction0X01(LU9685Struct *servo_arr_p, uint8_t servo_arr_len) {
    LU9685Struct *servo_arr_p_t;
    servo_arr_p_t = servo_arr_p;

    servo_arr_p_t->val = 90;
    servo_arr_p_t++;
    servo_arr_p_t->val = 180;
    servo_arr_p_t++;
    servo_arr_p_t->val = 45;
    servo_arr_p_t++;
    servo_arr_p_t->val = 30;
    servo_arr_p_t++;
    servo_arr_p_t->val = 70;
    LU9685_SetAngleMulti(servo_arr_p, servo_arr_len);
}
