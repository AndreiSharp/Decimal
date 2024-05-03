#include "../include/s21_decimal_help.h"

/**
 * @brief Get absolute value of s21_decimal
 * @author boilbrit
 * @param decimal source of value
 * @return s21_decimal absolute value
 */

s21_decimal s21_decimal_abs(s21_decimal decimal) {
  decimal.bits[DATA_INDEX] = s21_reset_bit(decimal.bits[DATA_INDEX], SIGN_POS);
  return decimal;
}