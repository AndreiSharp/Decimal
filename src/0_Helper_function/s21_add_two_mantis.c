#include "../include/s21_decimal.h"

int s21_add_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res) {
  int flag = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_is_set_bit(value_1, i) +
           s21_decimal_is_set_bit(value_2, i) + flag;
    *res = s21_decimal_set_bit(*res, i, flag % 2);
    flag = flag / 2;
  }
  return flag;
}