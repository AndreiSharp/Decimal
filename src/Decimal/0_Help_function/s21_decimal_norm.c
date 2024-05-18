#include "./../../Headers/s21_decimal.h"

bit32_t s21_decimal_norm(s21_DecData value) {
  if (value.value.bits[DATA_INDEX] != 0 && value.scale == 0) {
    if (value.sign == NEGATIVE) {
      return S21_TOO_SMALL;
    } else {
      return S21_TOO_LARGE;
    }
  }
}