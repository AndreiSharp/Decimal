#include "./../../Headers/s21_comprasion_function.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_function_compare(value_2, value_2) != 0;
}