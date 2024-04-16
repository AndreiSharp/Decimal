#include "./../6_Headers/s21_convertation_and_parsers.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = S21_SUCCES;
  if (dst) {
    int index_low_bit = s21_take_exp(src);
    int index_high_bit = s21_is_set_bit(src, MAX_BIT_BLOCKS);
    int size_int_mantis = index_high_bit - index_low_bit;
    if (size_int_mantis > sizeof(int)) {
      while (size_int_mantis >= 0) {
        (*dst) << size_int_mantis;
        (*dst) &= s21_decimal_is_set_bit(src, size_int_mantis);
        (*dst) >> size_int_mantis;
        size_int_mantis--;
      }
      if (s21_take_sign(src)) {
        (*dst) *= -1;
      }
    } else {
      flag = S21_CONV_ERROR;
    }
  } else {
    flag = S21_CONV_ERROR;
  }
}