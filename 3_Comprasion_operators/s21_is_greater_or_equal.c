#include "./../6_Headers/s21_decimal.h"

// Greater than or equal to
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag;
  int exp_1 = s21_take_exp(value_1);
  int exp_2 = s21_take_exp(value_2);
  if (exp_1 == exp_2) {
  } else {
  }
  return flag;
}

int s21_is_equal_mantis(s21_decimal value_1, s21_decimal value_2) {
  int flag = S21_TRUE;
  int index_1 = s21_get_index_high_bit(value_1);
  int index_2 = s21_get_index_high_bit(value_2);
  if (index_1 == index_2 && index_1 != -1) {
    int result = s21_decimal_is_set_bit(value_1, index_1) -
                 s21_decimal_is_set_bit(value_2, index_1);
  } else {
    flag = S21_FALSE;
  }
}

int s21_get_index_high_bit(s21_decimal value) {
  int index = MAX_BIT_BLOCKS;
  while (s21_decimal_is_set_bit(value, index) && index != -1) {
    index--;
  }
  return index;
}