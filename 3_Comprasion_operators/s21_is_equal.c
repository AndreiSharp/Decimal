#include "./../6_Headers/s21_decimal.h"

// Equal to
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag;
  int index = MAX_BIT_BLOCKS;
  while (s21_is_set_bit(value_1, index) == s21_is_set_bit(value_2) &&
         index >= 0) {
    index--;
  }
  return index == -1 ? S21_TRUE : S21_FALSE;
}