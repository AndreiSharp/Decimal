#include "s21_decimal_types.h"

/*---------------------------------CONST---------------------------------*/

enum s21_arithmetic_result {
  S21_SUCCES = 0,       // OK
  S21_TOO_LARGE = 1,    // The number is too large or equal to infinity
  S21_TOO_SMALL = 2,    // The number is too small or equal to negative infinity
  S21_DEV_BY_ZERO = 3,  // Division by 0
  S21_ERROR = 4         // Another Error
};

/*-------------------------------Function--------------------------------*/

// Addition
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Subraction
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Multiplication
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // boilbrit

// Division
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

