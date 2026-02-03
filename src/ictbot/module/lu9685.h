#ifndef LU9685_H
#define LU9685_H

#include <klib-macros.h>
#include <ecos.h>
#include "../driver/i2c_soft.h"
#include "../driver/timer.h"
#include "../util/debug.h"

typedef struct {
    uint8_t num;
    uint8_t val;
} LU9685Struct;

void LU9685_Init(LU9685Struct *servo_arr_p, uint8_t *servo_arr_len_p);
void LU9685_Reset();
void LU9685_SetAngleSingle(uint8_t servo_idx, uint8_t servo_val);
void LU9685_SetAngleMulti(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction(LU9685Struct *servo_arr_p, uint8_t servo_arr_len,
                                                 uint8_t servo_action);
void LU9685_SetAction0X01(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X02(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X03(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X04(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X05(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X06(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X07(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X08(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X09(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);
void LU9685_SetAction0X0A(LU9685Struct *servo_arr_p, uint8_t servo_arr_len);

#endif
