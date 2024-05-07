#include "../include/s21_decimal_help.h"

/**
 * @brief Get sign of s21_decimal
 * @author boilbrit
 * @param decimal source of value
 * @return int s21_decimal sign
 */

unsigned int s21_decimal_sign(s21_decimal decimal) {
  return s21_get_bit(decimal.bits[DATA_INDEX], SIGN_POS);
}
