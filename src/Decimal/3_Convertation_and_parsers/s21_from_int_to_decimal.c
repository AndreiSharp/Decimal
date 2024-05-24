#include "./../../Headers/s21_convertation_and_parsers.h"
// переполнение инта
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_DecData dst_DecData = s21_decimal_null_data();
  int error_code = S21_CONV_SUCCESS;
  if (dst) {
    if (src < 0) {
      bit32_t src_abs = abs(src + 1);
      dst_DecData.value.bits[0] = src_abs + 1;
      dst_DecData.sign = 1;
    } else {
      dst_DecData.value.bits[0] = src;
    }
    *dst = s21_decimal_set_data(dst_DecData);
  } else {
    error_code = S21_CONV_ERROR;
  }
  return error_code;
}