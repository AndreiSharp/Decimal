#include "../include/s21_decimal.h"

int s21_sub_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res) {
  int flag = 0;
  int res_div = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    res_div =
        s21_decimal_is_set_bit(value_1, i) - s21_decimal_is_set_bit(value_2, i);
    if (res_div - flag >= 0) {
      *res = s21_decimal_set_bit(*res, i, res_div + flag);
      flag = 0;
    } else {
      flag = 1;
      *res = s21_decimal_set_bit(*res, i, 1);
    }
  }
  return flag;
}