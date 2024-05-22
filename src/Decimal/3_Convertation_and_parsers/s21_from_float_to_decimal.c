#include "./../../Headers/s21_convertation_and_parsers.h"
// переполнение инта
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_DecData dst_DecData = s21_decimal_null_data();
  unsigned int error_code = S21_CONV_SUCCESS;
  if (dst) {
    if (src < 0) {
      dst_DecData.sign = 1;
      src *= -1;
    }
    for (int i = 0; i < FLOAT_LEN; ++i) {
      src *= 10;
    }
    s21_from_int_to_decimal((int)src, &dst_DecData.value);
  } else {
    error_code = S21_CONV_ERROR;
  }
  return error_code;
}