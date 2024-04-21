#include "./../6_Headers/s21_convertation_and_parsers.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = S21_SUCCES;
  if (dst) {
    if (src < 0) {
      src *= -1;
      s21_decimal_set_bit(*dst, MAX_BIT_BLOCKS, 1);
    }
    dst->bits[0] = src;
  } else {
    flag = S21_CONV_ERROR;
  }
  return flag;
}