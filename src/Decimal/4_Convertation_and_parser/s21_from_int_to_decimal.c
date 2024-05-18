#include "./../../Headers/s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
s21_DecData src_DecData = s21_from_decimal_to_DecData(src); // Андрей, где функция??

  int flag = S21_SUCCES;
  if (dst) {
    int index_low_bit = src_DecData.scale;
    int index_high_bit = src_DecData.high_bit;
    int size_int_mantis = index_high_bit - index_low_bit;
    if ((size_t) size_int_mantis > sizeof(int)) {
      while (size_int_mantis >= 0) {
        (*dst) <<= size_int_mantis;
        (*dst) &= s21_decimal_get_bit(src_DecData.value, size_int_mantis);
        (*dst) >>= size_int_mantis;
        size_int_mantis--;
      }
      if (src_DecData.sign) {
        (*dst) *= -1;
      }
    } else {
      flag = S21_CONV_ERROR;
    }
  } else {
    flag = S21_CONV_ERROR;
  }

  return flag;
}