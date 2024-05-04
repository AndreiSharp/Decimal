#include "./../6_Headers/s21_convertation_and_parsers.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = S21_CONV_SUCCESS;
  *dst = 0;
  if (dst == NULL) {
    result = S21_CONV_ERROR;
  } else {
    int minus = 1;
    long double result = 0, two = 1;
    int exp = s21_take_exp(src);
    if (s21_take_sign(src) == 1) minus = -1;
    for (int i = 0; i < 96; i++) {
      if (s21_decimal_is_set_bit(src, i)) {
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
