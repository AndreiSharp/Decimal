#include "../include/s21_decimal.h"
#include "../include/s21_decimal_binary.h"
#include "../include/s21_decimal_help.h"
#include <stdio.h>

typedef unsigned int bit;

s21_decimal s21_decimal_shift_left(s21_decimal decimal, int count) {
  while (--count) {
    bit last_first_bit_value = -1;
    for (int i = DATA_INDEX - 1; i >= 0; --i) {
      // берем значенипе первого бита из текущего блок
      bit first_bit_value = s21_get_bit(decimal.bits[i], 0);
      if (last_first_bit_value != -1) {
        // перебрасываем бит из первой ячейки предыдущего блока в последнюю яйчеку текущего блока
        s21_decimal_set_bit(decimal, (i + 1) * SIZE_BLOCK - 1, last_first_bit_value);
      }
      decimal.bits[i] <<= 1;
      last_first_bit_value = first_bit_value;
    }
  }
  return decimal;
}

s21_decimal s21_decimal_set_exp(s21_decimal decimal, int new_exp) {
    for (int i = EXP_POS_L; i <= EXP_POS_R; ++i) {
        
    }
}

s21_decimal s21_decimal_mul_10(s21_decimal decimal) {
  int exp = s21_decimal_exp(decimal);
  ++exp;
  
  s21_decimal result;
  s21_add(s21_decimal_shift_left(decimal, 1),
          s21_decimal_shift_left(decimal, 3), &result);
  s21_decimal_set_exp(decimal, exp);
  
  return decimal;
}

int main() {}
