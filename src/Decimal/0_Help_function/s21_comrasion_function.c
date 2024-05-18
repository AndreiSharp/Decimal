#include "./../../Headers/s21_comprasion_function.h"

bit32_t s21_decimal_compare_mantis(s21_DecData value_1, s21_DecData value_2) {
  bit32_t flag = 0;
  if (value_1.high_bit == value_2.high_bit) {
    for (int i = value_1.high_bit - 1; i >= 0 && flag == 0; i--) {
      if (s21_decimal_get_bit(value_1.value, i) >
          s21_decimal_get_bit(value_2.value, i)) {
        flag = 1;
      } else if (s21_decimal_get_bit(value_1.value, i) <
                 s21_decimal_get_bit(value_2.value, i)) {
        flag = 2;
      }
    }
  } else if (value_1.high_bit > value_2.high_bit) {
    flag = 1;
  } else {
    flag = 2;
  }
  return flag;
}