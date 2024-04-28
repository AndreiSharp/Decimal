#include "../include/s21_decimal.h"

// Multiplication
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int error_code = S21_SUCCES;

 
  bit_t sign_result = 1;

  if (s21_decimal_sign(value_1) == s21_decimal_sign(value_2)) {
    sign_result = 0;
  }

  unsigned int exp_result = s21_decimal_exp(value_1) + s21_decimal_exp(value_2);

#ifdef FINAL
  while (1) { // пока exp не будет норм и пока мантисы не могут норм перемножиться
    // округление
    exp_result = s21_decimal_exp(value_1) + s21_decimal_exp(value_2);
    error_code = s21_decimal_mul_two_mantis(value_1, value_2, result);
  }
#endif
    
  exp_result = s21_decimal_exp(value_1) + s21_decimal_exp(value_2);
  error_code = s21_decimal_mul_two_mantis(value_1, value_2, result);

  *result = s21_decimal_set_exp(*result, exp_result);

  return error_code;
}