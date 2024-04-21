#include "./../6_Headers/s21_decimal.h"

// Returns the result of multiplying the specified Decimal value by negative one
// int s21_get_sign(s21_decimal value) {
//   return (value.bits[3] & 0x80000000) >> 31;
// }
// int s21_get_exp(s21_decimal value) {
//   return (value.bits[3] & 0x00FF0000) >> 16;
// }
int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  result->bits[3] =
      ((s21_get_sign(*result) ^ 1) << 31) |  (s21_get_exp(*result) << 16);
  return 0;
}