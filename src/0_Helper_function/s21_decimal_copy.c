#include "../include/s21_decimal_help.h"

/**
 * @brief copy decimal from src to dest
 * @author boilbrit
 * @param decimal source of value (from)
 * @param decimal source of value (to)
 * @return decimal copy from src
 */

s21_decimal s21_decimal_copy(s21_decimal src, s21_decimal *dest) {
  for (int i = 0; i < MAX_BLOCKS; ++i) {
    (*dest).bits[i] = src.bits[i];
  }
  return *dest;
}