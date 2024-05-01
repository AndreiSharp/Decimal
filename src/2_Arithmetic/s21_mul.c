#include "./../6_Headers/s21_arithmetic.h"

// Multiplication
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int flag = S21_SUCCES;
  flag = s21_decimal_is_correct(value_1);
  flag = (!flag) ? s21_decimal_is_correct(value_2) : S21_ERROR;
  if (result || !flag) {
    flag = s21_normalization(&value_1, &value_2);
    if (!flag) {
        }
  } else {
    flag = S21_ERROR;
  }
  return flag;
}