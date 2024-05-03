#include "../include/s21_decimal.h"

/**
 * @brief multiply a decimal and 10
 * @author anon
 * @param decimal source of value
 * @return results of multiplying 10 and decimal
 */

s21_decimal s21_decimal_mul_10(s21_decimal value) {
  s21_decimal res;
  s21_decimal_init(&res);
  res.bits[3] = value.bits[3];
  int flag = 0;
  for (int i = 1; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_get_bit(value, i - 1);
    res = s21_decimal_set_bit(res, i, flag);
  }
  for (int i = 3; i < SIZE_MANTIS; i++) {
    flag =
        s21_decimal_get_bit(res, i) + s21_decimal_get_bit(value, i - 3) + flag;
    res = s21_decimal_set_bit(res, i, flag % 2);
    flag = flag / 2;
  }
  return res;
}