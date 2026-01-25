#ifndef LU9685_H
#define LU9685_H

#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <ysyx.h>

typedef struct {
    uint8_t num;
    uint8_t val;
} LU9685Struct;

LU9685Struct *LU9685_Init(uint8_t *servo_arr_len_p);
void LU9685_Reset();
void LU9685_SetAngleSingle(uint8_t servo_idx, uint8_t servo_val);
void LU9685_SetAngleMulti(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X01(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction(LU9685Struct *servo_arr_p, uint8_t servo_arr_len,
                                                 uint8_t servo_act);

#endif
