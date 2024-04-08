#include "./../s21_decimal.h"

// Addition
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int error_code = S21_SUCCES;
  if (!result) {
    error_code = S21_ERROR;
  } else {
    // pass`
  }
  return 0;
}

int s21_take_exp(s21_decimal value) {
  int exp = 0b1;
  exp << 31;
  exp = exp + value.bits[3];
  exp >> 16;
  return exp;
}

int s21_normalization(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int exp_1 = s21_take_exp(value_1);
  int exp_2 = s21_take_exp(value_2);
  if (exp_1 != exp_2) {
    }
  return flag;
}