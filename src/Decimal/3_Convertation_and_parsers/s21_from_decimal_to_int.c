#include "./../../Headers/s21_convertation_and_parsers.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = S21_CONV_SUCCESS;
  s21_DecData src_DecData = s21_decimal_get_data(src);
  s21_count_div_10(&src_DecData, src_DecData.scale);
  if (src_DecData.sign) {
    if ((size_t)src_DecData.high_bit > sizeof(int) &&
        src_DecData.value.bits[0] > (bit32_t)(INT32_MAX + (bit32_t)1)) {
      error_code = S21_CONV_ERROR;
    } else {
      *dst = src_DecData.value.bits[0] - 1;
    }
  } else {
    if ((size_t)src_DecData.high_bit > sizeof(int) &&
        src_DecData.value.bits[0] > INT32_MAX) {
      error_code = S21_CONV_ERROR;
    } else {
      *dst = src_DecData.value.bits[0];
    }
  }
  return error_code;
}