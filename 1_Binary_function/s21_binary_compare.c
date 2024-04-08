#include "./../s21_decimal.h"

/**
 * @brief check that decimal is null
 * @author "morsbard"
 * @param decimal value where checking for equal null
 * @return result of compare decimal with null
 */
int s21_is_equal_null(s21_decimal decimal) {
  return !(decimal.bits[0] || decimal.bits[1] || decimal.bits[2] ||
           decimal.bits[3]);
}

/**
 * @brief compare two decimal
 * @author "morsbard"
 * @param decimal1 first comparing decimal
 * @param decimal2 second comparing decimal
 * @return result of comparing decimal1 with decimal2:
 *               -1 - if decimal2 more then decimal1.
 *                0 - if decimal1 equal decimal2.
 *                1 - if decimal1 moe then decimal2.
 */
int s21_binary_compare(s21_decimal decimal1, s21_decimal decimal2) {
  int result = 0;
  for (int i = MAX_BLOCKS; i >= 0 && result == 0; i++) {
    int isbit1 = s21_decimal_is_set_bit(decimal1, i);
    int isbit2 = s21_decimal_is_set_bit(decimal2, i);
    result = isbit1 - isbit2;
  }
  return result;
}