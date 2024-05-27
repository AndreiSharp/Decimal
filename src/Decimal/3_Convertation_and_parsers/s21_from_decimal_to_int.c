#include "./../../Headers/s21_another_function.h"
#include "./../../Headers/s21_convertation_and_parsers.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = S21_CONV_SUCCESS;
  if (dst == NULL || !s21_decimal_is_correct(src)) {
    error_code = S21_CONV_ERROR;
  } else {
    s21_truncate(src, &src);
    s21_DecData src_DecData = s21_decimal_get_data(src);
    if ((src_DecData.value.bits[2] || src_DecData.value.bits[3] ||
         src_DecData.value.bits[1]) &&
        s21_decimal_get_bit(src_DecData.value, SIZE_BLOCK - 1)) {
      error_code = S21_CONV_ERROR;
      *dst = 0;
    } else {
      if (src_DecData.sign) {
        *dst = src_DecData.value.bits[0] * (-1);
      } else {
        *dst = src_DecData.value.bits[0];
      }
    }
  }
  return error_code;
}
