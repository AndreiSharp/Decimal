#include "../include/s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = S21_CONV_SUCCESS;
  if (dst) {
    if (src < 0) {
      src *= -1;
      *dst = s21_decimal_set_bit(*dst, DECIMAL_SIGN_POS, 1);
    }
    dst->bits[0] = src;
  } else {
    flag = S21_CONV_ERROR;
  }
  return flag;
}
