#include "./s21_comprasion_operators.h"

// Greater than or equal to
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  if (s21_take_sign(value_1) > s21_take_sign(value_2)) {
    if (s21_take_exp(value_1) == s21_take_exp(value_2)) {
    } else {
    }
  } else {
  }
  return flag;
}