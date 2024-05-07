#include "../include/s21_decimal.h"

// From float
/*
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag_error = S21_SUCCES;
  if (dst) {
    if (src < 0) {
      src *= -1;
      *dst = s21_decimal_set_bit(*dst, DECIMAL_SIGN_POS, 1);
    }
    int quotient = (int)src;
    int fraction_part = src - quotient;
    int exp = 0;
  } else {
    flag_error = S21_CONV_ERROR;
  }
  return flag_error;
}
*/
