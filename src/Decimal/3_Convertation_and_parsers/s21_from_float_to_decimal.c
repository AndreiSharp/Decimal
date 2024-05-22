#include "./../../Headers/s21_convertation_and_parsers.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_DecData dst_DecData = s21_decimal_null_data();
  unsigned int error_code = S21_CONV_SUCCESS;
  if (dst) {
    if (src < 0) {
      dst_DecData.sign = 1;
      src *= -1;
    }
    for (dst_DecData.scale; dst_DecData.scale < FLOAT_LEN;
         ++dst_DecData.scale) {
      src *= 10;
    }
    error_code = s21_from_int_to_decimal((int)src, &dst_DecData.value);
    if (!error_code) {
      dst_DecData.high_bit = s21_decimal_get_high_bit(dst_DecData.value);
      *dst = s21_decimal_set_data(dst_DecData);
    } else {
      *dst = s21_decimal_null();
    }
  } else {
    error_code = S21_CONV_ERROR;
    *dst = s21_decimal_null();
  }
  return error_code;
}