#include "../include/s21_decimal.h"

/*
  @brief Returns the result of multiplying the specified Decimal value by negative one
  @rosalori
  @param value decimal
  @param result decimal
  @return flag mistake
 */

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_decimal negative_one = {{1, 0, 0, 0b10000000000000000000000000000000}};
  int error_status = s21_mul(value, negative_one, result);

  return error_status;
}
