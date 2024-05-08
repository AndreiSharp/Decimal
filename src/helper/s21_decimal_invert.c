#include "../include/s21_decimal.h"

s21_decimal s21_decimal_invert(s21_decimal decimal) {
  for (int i = 0; i < MAX_BLOCKS - 1; ++i) {
    decimal.bits[i] = ~decimal.bits[i];
  }
  return decimal;
}
