#include "./s21_anouther_function.h"

/*
  @brief Returns the integral digits of the specified Decimal any fractional
  digits are discarded, including trailing zeroes
  @author name
  @param value
  @param result
  @return int
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0;  //// добавить ошибки при вычислении (если переменные не по
                 ///формату и тп)
  int exp = s21_decimal_exp(value);
  for (int i = exp; i > 0; i--) {
    value = s21_decimal_div_10(value);
    exp_plus(&value, -1);
  }
  *result = value;
  change_sign_if_zero(result);
  return flag;
}