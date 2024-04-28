#include "s21_decimal_binary.h"
#include "s21_decimal_help.h"
#include "s21_decimal_types.h"

/*----------------------------------------------------------------------*/

/*-------------------------Arithmetic function---------------------------*/

/*---------------------------------CONST---------------------------------*/

enum s21_arithmetic_result {
  S21_SUCCES = 0,      // OK
  S21_TOO_LARGE = 1,   // The number is too large or equal to infinity
  S21_TOO_SMALL = 2,   // The number is too small or equal to negative infinity
  S21_DEV_BY_ZERO = 3, // Division by 0
  S21_ERROR = 4        // Another Error
};

/*-------------------------------Function--------------------------------*/

// Addition
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Subraction
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Multiplication
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result); // boilbrit

// Division
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*-----------------------------------------------------------------------*/

/*-------------------------Comprasion operators--------------------------*/

/*---------------------------------CONST---------------------------------*/

enum s21_comprasion_result { S21_TRUE = 1, S21_FALSE = 0 };

/*-------------------------------Function--------------------------------*/

// Less than
int s21_is_less(s21_decimal, s21_decimal);

// Less than or equal
int s21_is_less_or_equal(s21_decimal, s21_decimal);

// Greater than
int s21_is_greater(s21_decimal, s21_decimal);

// Greater than or equal to
int s21_is_greater_or_equal(s21_decimal, s21_decimal);

// Equal to
int s21_is_equal(s21_decimal, s21_decimal);

// Not equal to
int s21_is_not_equal(s21_decimal, s21_decimal);

/*-----------------------------------------------------------------------*/

/*-----------------------CONVERTATION AND PARSERS------------------------*/

/*---------------------------------CONST---------------------------------*/

enum s21_conv_result {
  S21_CONV_ERROR = 1, // Convertation error
  S21_CONV_SUCCESS = 0
};

/*-------------------------------Function--------------------------------*/

// From int
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// From float
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// To int
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// To float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*-----------------------------------------------------------------------*/

/*---------------------------ANOUTHER FUNCTION---------------------------*/

/*---------------------------------CONST---------------------------------*/

#define S21_CALC_ERROR // Calculation error

/*-------------------------------Function--------------------------------*/

// Rounds a specified Decimal number to the closest integer toward negative
// infinity
int s21_floor(s21_decimal value, s21_decimal *result);

// Rounds a decimal value to the nearest integer
int s21_round(s21_decimal value, s21_decimal *result);

// Returns the integral digits of the specified Decimal; any fractional digits
// are discarded, including trailing zeroes
int s21_truncate(s21_decimal value, s21_decimal *result); // boilbrit

// Returns the result of multiplying the specified Decimal value by negative one
int s21_negate(s21_decimal value, s21_decimal *result);

/*-----------------------------------------------------------------------*/