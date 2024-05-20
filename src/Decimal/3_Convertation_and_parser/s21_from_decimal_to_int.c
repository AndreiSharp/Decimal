#include "./../../Headers/s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_DecData src_DecData = s21_decimal_get_data(src);

  int error_code = S21_CONV_SUCCESS;
  if (dst && s21_decimal_is_correct(src)) {
    bit32_t size_int_mantis = src_DecData.high_bit;
    if ((size_t) size_int_mantis > sizeof(int)) {
      while (size_int_mantis >= 0) {
        (*dst) <<= size_int_mantis;
        (*dst) &= s21_decimal_get_bit(src_DecData.value, size_int_mantis);
        (*dst) >>= size_int_mantis;
        size_int_mantis--;
      }
      if (src_DecData.sign == 1) {
        (*dst) *= -1;
      }
    } else {
      error_code = S21_CONV_ERROR;
    }
  } else {
    error_code = S21_CONV_ERROR;
  }

  return error_code;
}

int funch0za_s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_DecData src_DecData = s21_decimal_get_data(src);

  int error_code = S21_CONV_SUCCESS;
  if (dst && s21_decimal_is_correct(src)) {
    s21_count_div_10(&src_DecData, src_DecData.scale);

    if ((size_t) src_DecData.high_bit > sizeof(int)) {
      
    }
  } else {
    error_code = S21_CONV_ERROR;
  }
}