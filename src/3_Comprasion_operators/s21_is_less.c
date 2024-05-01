#include "./s21_comprasion_operators.h"

// Less than
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int first = 0;
  int second = 0;
  s21_function_compare(value_1, value_2, &first, &second);
  int flag = S21_FALSE;
  if (second == 1 || first == second) {
    flag = S21_TRUE;
  }
  return flag;
}