#include "../include/s21_decimal_help.h"

/**
 * @brief initialization s21_decimal
 * @author "boilbrit"
 * @param decimal source of value
 * @return initialized s21_decimal 
 */
s21_decimal s21_decimal_init(s21_decimal *decimal) {
  for (int i = 0; i < MAX_BLOCKS; ++i) {
    (*decimal).bits[i] = BIN_ZERO;
  }

  *decimal = s21_decimal_set_bit(*decimal, DECIMAL_EXP_POS_L, 1);

  return *decimal;
}
