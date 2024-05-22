#ifndef S21_DECIMAL_TYPES
#define S21_DECIMAL_TYPES

/*--------------------------------SYS_HEADERS---------------------------*/

#include <stdio.h>
#include <stdlib.h>
/*--------------------------------CONST---------------------------------*/

enum sizes {
  COUNT_BLOCKS = 4,                                // count of decimal blocks
  COUNT_BLOCKS_MANTIS = 3,                         // count of mantis blocks
  SIZE_BLOCK = 32,                                 // size of one block
  SIZE_MANTIS = COUNT_BLOCKS_MANTIS * SIZE_BLOCK,  // size of mantis
  SIZE_DECIMAL = SIZE_BLOCK * COUNT_BLOCKS         // size of decimal
};

enum position {
  MAX_NUM_MANTIS = SIZE_MANTIS - 1,  // index of high bit
  SIGN_POS =
      SIZE_BLOCK - 1,  // position of s21_decimal sign in bits[DATA_INDEX]
  DATA_INDEX =
      COUNT_BLOCKS - 1,  // index of bits where exponent and sign of s21_decimal
  SCALE_POS_L = 16,      // start positon of exponent in bits[DATA_INDEX]
  SCALE_POS_R = 23,      // end position of exponent in bits[DATA_INDEX]
  MAX_SCALE = 28,
  MIN_SCALE = 0
};

/*--------------------------------STRUCT--------------------------------*/

typedef unsigned char bit_t;  // 1 or 0

typedef unsigned int
    bit32_t;  // 32 bit in bits[i], bits[i] - one block in s21_decimal

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
  bit32_t bits[SIZE_BLOCK];
} s21_decimal;

typedef struct s21_decimal_data {
  s21_decimal value;
  bit_t sign;
  int scale;
  bit32_t high_bit;
} s21_DecData;

/*-------------------------Arithmetic function---------------------------*/

/*---------------------------------CONST---------------------------------*/
enum s21_arithm_result {
  S21_SUCCES = 0,       // OK
  S21_TOO_LARGE = 1,    // The number is too large or equal to infinity
  S21_TOO_SMALL = 2,    // The number is too small or equal to negative infinity
  S21_DEV_BY_ZERO = 3,  // Division by 0
};

/*-------------------------Comprasion operators--------------------------*/

/*---------------------------------CONST---------------------------------*/

enum s21_comp_result { S21_TRUE = 1, S21_FALSE = 0 };

/*-----------------------CONVERTATION AND PARSERS------------------------*/

/*---------------------------------CONST---------------------------------*/

#define FLOAT_LEN 7

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