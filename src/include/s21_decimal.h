#pragma once
#include <stddef.h>
#include <stdint.h>

/*--------------------------------CONST---------------------------------*/
enum sizes {
  MAX_BLOCKS = 4,  // count of bits
  SIZE_BLOCK = 32, // count of bits in one block
  SIZE_MANTIS = (MAX_BLOCKS - 1) * SIZE_BLOCK,
};

enum position {
  EXP_POS_L = 16, // left positon of exponent in bits[DATA_INDEX]
  EXP_POS_R = 23, // right positon of exponent in bits[DATA_INDEX]
  DECIMAL_EXP_POS_L = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_L - 1,
  DECIMAL_EXP_POS_R = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_R - 1,
  SIGN_POS = SIZE_BLOCK - 1, // position of s21_decimal sign in bits[DATA_INDEX]
  DATA_INDEX =
      MAX_BLOCKS - 1 // index of bits where exponent and sign of s21_decimal
};

#define NO_BIT_VALUE 2 // not 1 or 2

/*--------------------------------STRUCT--------------------------------*/

typedef uint8_t bit_t; // 1 or 0
typedef uint32_t
    bit32_t; // 32 bit in bits[i], bits[i] - one block in s21_decimal

/* main struct of decimal:
  in 0 bit [0..31] contain low bits of 96-bit integer
  in 1 bit [32..63] contain middle bits of 96-bit integer
  in 2 bit [64..95] contain high bits of 96-bit integer
  in 3 bit :
    [0..15] - the lower word, are unused and must be zero.
    [16..23] - contain an exponent between 0 and 28, which indicates the power
               of 10 to divide the integer number
    [24..30] - unused and must be zero
    [31] - contains the sign
*/

typedef struct {
  bit32_t bits[MAX_BLOCKS];
} s21_decimal;

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