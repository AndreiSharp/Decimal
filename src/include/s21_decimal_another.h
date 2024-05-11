#include "s21_decimal_types.h"
#include "s21_decimal_help.h"

/*---------------------------------CONST---------------------------------*/

#define S21_CALC_ERROR  // Calculation error

/*-------------------------------Function--------------------------------*/

// Rounds a specified Decimal number to the closest integer toward negative
// infinity
int s21_floor(s21_decimal value, s21_decimal *result);

// Rounds a decimal value to the nearest integer
int s21_round(s21_decimal value, s21_decimal *result);

// Returns the integral digits of the specified Decimal; any fractional digits
// are discarded, including trailing zeroes
int s21_truncate(s21_decimal value, s21_decimal *result);  // boilbrit

// Returns the result of multiplying the specified Decimal value by negative one
int s21_negate(s21_decimal value, s21_decimal *result);