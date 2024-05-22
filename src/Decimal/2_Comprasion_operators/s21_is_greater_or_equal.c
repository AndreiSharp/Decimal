#include "./../../Headers/s21_comprasion_function.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  unsigned int comp_result = s21_function_compare(value_1, value_2);
  return comp_result == 1 || comp_result == 0;
}