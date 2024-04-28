#include "./../s21_decimal.h"


/**
 * @brief больше или равно
 * @author yrelcary
 * @param value_1 - децимал
 * @param value_2 - децимал
 * @return true or false
 */

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int first = 0; 
  int second = 0;
  function_compare(value_1, value_2, &first, &second);
  int flag = FALSE;
  if (first == 1 || first == second) {
    flag = TRUE;
  }
  return flag;
}