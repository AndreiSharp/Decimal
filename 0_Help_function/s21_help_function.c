#include "./../6_Headers/s21_help_function.h"

s21_decimal s21_decimal_abs(s21_decimal decimal) {
  decimal.bits[DATA_INDEX] = s21_reset_bit(decimal.bits[DATA_INDEX], SIGN_POS);
  return decimal;
}

int s21_take_exp(s21_decimal value) {
  int exp = 0b1;
  exp = value.bits[DATA_INDEX];
  if (s21_get_bit(exp, SIGN_POS)) {
    s21_reset_bit(exp, SIGN_POS);
  }
  exp >> 16;
  return exp;
}

int s21_take_sign(s21_decimal decimal) {
  return s21_get_bit(decimal.bits[DATA_INDEX], SIGN_POS);
}

s21_decimal s21_decimal_copy(s21_decimal src, s21_decimal *dest) {
  for (int i = 0; i < MAX_BLOCKS; ++i) {
    (*dest).bits[i] = src.bits[i];
  }
  return *dest;
}

s21_decimal s21_decimal_abs(s21_decimal decimal) {
  decimal.bits[DATA_INDEX] = s21_reset_bit(decimal.bits[DATA_INDEX], SIGN_POS);
  return decimal;
}