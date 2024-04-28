#include "../include/s21_decimal.h"

// Subraction
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int flag = S21_SUCCES;
  int sign_value1 = s21_decimal_sign(value_1);
  int sign_value2 = s21_decimal_sign(value_2);
  if (sign_value1 == sign_value2) {
    if (s21_is_less(value_1, value_2)) {
      flag = s21_sub_two_mantis(value_1, value_2, result);
    } else {
      flag = s21_sub_two_mantis(value_2, value_1, result);
    }
  } else {
    flag = s21_normalization(&value_1, &value_2);
    if (flag) {
      flag = s21_add_two_mantis(value_1, value_2, result);
    }
  }
  return flag;
}