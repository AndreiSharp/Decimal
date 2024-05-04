#include "../include/s21_decimal.h"

// Rounds a specified Decimal number to the closest integer toward negative
// infinity

/*
  @brief Rounds a specified Decimal number to the closest integer toward
  negative infinity
  @yrelcary
  @param value децимал
  @param result децимал
  @return flag mistake
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 0; // для возврата
  // добавить проверку на корректность децимала
  s21_decimal_init(result);
  (*result).bits[3] = value.bits[3];
  change_sign_if_zero(result);
  int sign = s21_decimal_sign(value);
  flag = s21_truncate(value, result);
  if (sign == 1) {
    s21_decimal bufer;
    s21_decimal_init(&bufer);
    flag = s21_sub(value, *result, &bufer);
    if (s21_mantis_is_equal_null(bufer) != 1) {
      s21_decimal_init(&bufer);
      bufer.bits[0] = 0b0000000000000000000000000000001;
      flag = s21_add(*result, bufer, result);
    }
  }
  return flag;
}