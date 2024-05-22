#include "./../../Headers/s21_comprasion_function.h"

/**
 * @brief равенство
 * @author yrelcary
 * @param value_1 - децимал
 * @param value_2 - децимал
 * @return true or false
 */

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_function_compare(value_1, value_2) == 0;
}