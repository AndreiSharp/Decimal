#include "../include/s21_decimal.h"
#include "../include/s21_decimal_binary.h"
#include "../include/s21_decimal_help.h"
#include <stdio.h>

s21_decimal s21_decimal_shift_left(s21_decimal decimal, int count) {
  while (--count) {
    bit_t last_first_bit_value = NO_BIT_VALUE;
    for (int i = DATA_INDEX - 1; i >= 0; --i) {
      // берем значенипе первого бита из текущего блок
      bit_t first_bit_value = s21_get_bit(decimal.bits[i], 0);
      if (last_first_bit_value != NO_BIT_VALUE) {
        // перебрасываем бит из первой ячейки предыдущего блока в последнюю
        // яйчеку текущего блока
        decimal = s21_decimal_set_bit(decimal, (i + 1) * SIZE_BLOCK - 1,
                                      last_first_bit_value);
      }
      decimal.bits[i] <<= 1;
      last_first_bit_value = first_bit_value;
    }
  }

  return decimal;
}

s21_decimal s21_decimal_set_exp(s21_decimal decimal, bit32_t new_exp) {
  for (int i = EXP_POS_L; i <= EXP_POS_R; ++i) {
    decimal = s21_decimal_set_bit(decimal, (MAX_BLOCKS - 1) * SIZE_BLOCK + i,
                                  s21_get_bit(new_exp, i - EXP_POS_L));
  }

  return decimal;
}

s21_decimal s21_decimal_mul_10(s21_decimal decimal) {
  int exp = s21_decimal_exp(decimal);

  s21_decimal result;
  s21_add(s21_decimal_shift_left(decimal, 1),
          s21_decimal_shift_left(decimal, 3), &result);
  s21_decimal_set_exp(decimal, exp + 1);

  return decimal;
}



int main() {}
