#pragma once
#include <stddef.h>
#include <stdint.h>

/*--------------------------------CONST---------------------------------*/
enum sizes {
  MAX_BLOCKS = 4,   // count of bits
  SIZE_BLOCK = 32,  // count of bits in one block
  SIZE_MANTIS = (MAX_BLOCKS - 1) * SIZE_BLOCK,
};

enum position {
  EXP_POS_L = 16,  // left positon of exponent in bits[DATA_INDEX]
  EXP_POS_R = 23,  // right positon of exponent in bits[DATA_INDEX]
  DECIMAL_EXP_POS_L = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_L - 1,
  DECIMAL_EXP_POS_R = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_R - 1,
  SIGN_POS =
      SIZE_BLOCK - 1,  // position of s21_decimal sign in bits[DATA_INDEX]
  DATA_INDEX =
      MAX_BLOCKS - 1  // index of bits where exponent and sign of s21_decimal
};

#define MAX_MANTIS ((MAX_BLOCKS - 1) * SIZE_BLOCK)  // maximum value of mantis
#define MAX_EXP 28
#define NO_BIT_VALUE 2  // not 1 or 2

/*--------------------------------STRUCT--------------------------------*/

typedef uint8_t bit_t;  // 1 or 0
typedef uint32_t
    bit32_t;  // 32 bit in bits[i], bits[i] - one block in s21_decimal

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
