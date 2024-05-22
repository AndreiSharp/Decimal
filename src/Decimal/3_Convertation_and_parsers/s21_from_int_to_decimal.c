#include "./../../Headers/s21_convertation_and_parsers.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_DecData dst_DecData = s21_decimal_null_data();
  int error_code = S21_CONV_SUCCESS;
  if (dst) {
    if (src < 0) {
      bit32_t src_abs = abs(src);
      dst_DecData.sign = 1;
    }
    dst->bits[0] = src;
  } else {
    error_code = S21_CONV_ERROR;
  }
  return error_code;
}