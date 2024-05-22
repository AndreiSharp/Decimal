#include <stdint.h>

#include "./../../Headers/s21_convertation_and_parsers.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_DecData src_DecData = s21_decimal_get_data(src);

  int error_code = S21_CONV_SUCCESS;
  if (dst && s21_decimal_is_correct(src)) {
    s21_count_div_10(&src_DecData, src_DecData.scale);

    if ((size_t)src_DecData.high_bit > sizeof(int) ||
        src_DecData.value.bits[0] > INT32_MAX) {
      error_code = S21_CONV_ERROR;
    } else {
      *dst = src_DecData.value.bits[0];
    }
  } else {
    error_code = S21_CONV_ERROR;
  }
  return error_code;
}