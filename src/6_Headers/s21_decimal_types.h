#ifndef S21_DECIMAL_TYPES
#define S21_DECIMAL_TYPES

/*--------------------------------SYS_HEADERS---------------------------*/

#include <stdint.h>
#include <stdio.h>

/*--------------------------------CONST---------------------------------*/

enum sizes {
  COUNT_BLOCKS = 4,                        // count of decimal blocks
  SIZE_BLOCK = 32,                         // size of one block
  SIZE_MANTIS = 96,                        // size of mantis
  SIZE_DECIMAL = SIZE_BLOCK * SIZE_MANTIS  // size of decimal
};

enum position {
  MAX_NUM_MANTIS = 95,  // index of high bit
  SIGN_POS = 31,        // position of s21_decimal sign in bits[DATA_INDEX]
  DATA_INDEX = 3,       // index of bits where exponent and sign of s21_decimal
  EXP_POS_L = 16,       // start positon of exponent in bits[DATA_INDEX]
  EXP_POS_R = 23,       // end position of exponent in bits[DATA_INDEX]
  MAX_EXP = 28
};

/*--------------------------------STRUCT--------------------------------*/
/* main struct of decimal:
  in 0 bit [0..31] contain low bits of 96-bit integer
  in 1 bit [32..63] contain middle bits of 96-bit integer
  in 2 bit [64..95] contain high bits of 96-bit integer
  in 3 bit :
    [0..15] - the lower word, are unused and must be zero.
    [16..23] - contain an exponent between 0 and 28, which indicates the
  power of 10 to divide the integer number [24..30] - unused and must be
  zero [31] - contains the sign
*/
typedef struct {
  unsigned int bits[SIZE_BLOCK];
} s21_decimal;

typedef uint8_t bit_t;  // 1 or 0

typedef uint32_t
    bit32_t;  // 32 bit in bits[i], bits[i] - one block in s21_decimal

/*-------------------------Arithmetic function---------------------------*/

/*---------------------------------CONST---------------------------------*/
enum s21_arithm_result {
  S21_SUCCES = 0,       // OK
  S21_TOO_LARGE = 1,    // The number is too large or equal to infinity
  S21_TOO_SMALL = 2,    // The number is too small or equal to negative infinity
  S21_DEV_BY_ZERO = 3,  // Division by 0
  S21_ERROR = 4         // Another Error
};

/*-------------------------Comprasion operators--------------------------*/

/*---------------------------------CONST---------------------------------*/

enum s21_comp_result { S21_TRUE = 1, S21_FALSE = 0 };

/*-----------------------CONVERTATION AND PARSERS------------------------*/

/*---------------------------------CONST---------------------------------*/

enum s21_conv_result {
  S21_CONV_ERROR = 1,   // Convertation error
  S21_CONV_SUCCESS = 0  // Convertation success
};

/*---------------------------ANOUTHER FUNCTION---------------------------*/

/*---------------------------------CONST---------------------------------*/

enum s21_anoutherfunc_result {
  S21_ANFUNC_ERROR = 1,   // Calculation error
  S21_ANFUNC_SUCCESS = 0  // Calculation success
};

/*----------------------------------------------------------------------*/
#endif