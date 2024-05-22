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

bit32_t s21_function_compare(s21_decimal value_1, s21_decimal value_2) {
  bit32_t result = 0;
  if (!s21_decimal_is_null(value_1) && !s21_decimal_is_null(value_2)) {
    s21_DecData val_1 = s21_decimal_get_data(value_1);
    s21_DecData val_2 = s21_decimal_get_data(value_2);

    int high_bit_pos_norm_1 = val_1.high_bit - 3 * val_1.scale;
    int high_bit_pos_norm_2 = val_2.high_bit - 3 * val_2.scale;

    if (high_bit_pos_norm_1 > high_bit_pos_norm_2) {
      result = 1;
    } else if (high_bit_pos_norm_1 < high_bit_pos_norm_2) {
      result = 2;
    } else {
      s21_normalize(&val_1, &val_2);
      result = s21_decimal_compare_mantis(val_1, val_2);
    }
  }
  return result;
}