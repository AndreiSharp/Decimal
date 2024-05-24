#ifndef S21_BINARY
#define S21_BINARY

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_decimal_types.h"

/*----------------------------Binary function---------------------------*/

/*----------------------------Number function---------------------------*/

bit32_t s21_get_bit(bit32_t number, int index);

bit32_t s21_set_bit(bit32_t number, int index);

bit32_t s21_reset_bit(bit32_t number, int index);

bit32_t s21_get_high_bit(bit32_t value);

/*----------------------------Decimal function---------------------------*/

bit32_t s21_decimal_get_bit(s21_decimal value, int index);

s21_decimal s21_decimal_set_bit(s21_decimal value, int index, bit_t bit);

bit32_t s21_decimal_get_high_bit(s21_decimal value);

bit32_t s21_decimal_get_sign(s21_decimal value);

s21_decimal s21_decimal_set_sign(s21_decimal value, bit32_t bit);

s21_decimal s21_decimal_abs(s21_decimal value);

bit32_t s21_decimal_get_scale(s21_decimal value);

s21_decimal s21_decimal_set_scale(s21_decimal value, bit32_t scale);

#endif