#ifndef S21_DECIMAL_TYPES
#define S21_DECIMAL_TYPES

/*--------------------------------CONST---------------------------------*/

#define MAX_BLOCKS 4       // count of bits
#define MAX_BIT_BLOCKS 95  // count of bits in one block
#define SIZE_BLOCK 32      // size of one block
#define SIZE_MANTIS 96     // size of mantis
#define DATA_INDEX 3  // index of bits where exponent and sign of s21_decimal
#define EXP_POS_L 16  // left positon of exponent in bits[DATA_INDEX]
#define EXP_POS_R 23  // right positon of exponent in bits[DATA_INDEX]
#define SIGN_POS 31   // position of s21_decimal sign in bits[DATA_INDEX]
#define S21_SUCCES 0  // OK

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
  unsigned int bits[MAX_BLOCKS];
} s21_decimal;

/*----------------------------------------------------------------------*/
#endif