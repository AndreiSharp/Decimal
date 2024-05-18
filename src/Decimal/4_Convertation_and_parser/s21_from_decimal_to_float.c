#include "./../../Headers/s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_DecData src_DecData = s21_from_decimal_to_DecData(src);

  int result = S21_CONV_SUCCESS;
  *dst = 0;
  if (dst == NULL) {
    result = S21_CONV_ERROR;
  } else {
    int minus = 1;
    long double result = 0, two = 1;
    int exp = src_DecData.scale;
    if (src_DecData.sign == 1)
      minus = -1;
    for (int i = 0; i < 96; i++) {
      if (s21_decimal_get_bit(src_DecData.value, i)) {
        result += two;
      }
      two *= 2;
    }
    for (int i = 0; i < exp; i++) {
      result /= 10;
    }
    *dst = minus * result;
  }

  return result;
}