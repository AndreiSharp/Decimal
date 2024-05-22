#include "./../../Headers/s21_another_function.h"

// Returns the result of multiplying the specified Decimal value by negative one
int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  result->bits[3] = ((s21_decimal_get_sign(*result) ^ 1) << 31) |
                    (s21_decimal_get_scale(*result) << 16);
  return 0;
}