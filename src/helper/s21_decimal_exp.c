#include "../include/s21_decimal_help.h"

/**
 * @brief Get exponent of s21_decimal
 * @author boilbrit
 * @param decimal source of value
 * @return int s21_decimal exponent
 */

unsigned int s21_decimal_exp(s21_decimal decimal) {
  if (s21_decimal_sign(decimal)) {
    decimal = s21_decimal_abs(decimal);
  }
  decimal.bits[DATA_INDEX] >>= (EXP_POS_L - 1);

  return decimal.bits[DATA_INDEX];
}
