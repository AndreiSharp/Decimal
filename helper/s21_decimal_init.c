#include "../include/s21_decimal.h"

/**
 * @brief initialization s21_decimal
 * @author "boilbrit"
 * @param decimal source of value
 * @return initialized s21_decimal
 */
s21_decimal s21_decimal_init(s21_decimal *decimal) {
  for (int i = 0; i < MAX_BLOCKS; ++i) {
    decimal->bits[i] = BIN_ZERO;
  }

  return *decimal;
}
