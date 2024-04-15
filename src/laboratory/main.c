#include <stdio.h>
#include <stdint.h>

/*--------------------------------CONST---------------------------------*/

#define MAX_BLOCKS 4       // count of bits
#define MAX_BIT_BLOCKS 96  // count of bits in one block
#define SIZE_BLOCK 32      // size of one block
#define DATA_INDEX 3    // index of bits where exponent and sign of s21_decimal
#define EXP_POS_L 16    // left positon of exponent in bits[DATA_INDEX]
#define EXP_POS_R 23    // right positon of exponent in bits[DATA_INDEX]
#define SIGN_POS 31     // position of s21_decimal sign in bits[DATA_INDEX]
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

int s21_set_bit(int number, int index) { return number | (0b1 << index); }

int s21_get_bit(int number, int index) {
  return ((0b1 << index) & number) >> index;
}

int s21_reset_bit(int number, int index) { return number & ~(0b1 << index); }

s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index, int bit) {
  if (bit == 0) {
    decimal.bits[index / MAX_BLOCKS] =
        s21_reset_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  } else {
    decimal.bits[index / MAX_BLOCKS] =
        s21_set_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  }
  return decimal;
}

s21_decimal s21_decimal_copy(s21_decimal src, s21_decimal *dest) {
  for (int i = 0; i < MAX_BLOCKS; ++i) {
    (*dest).bits[i] = src.bits[i];
  }
  return *dest;
}

bit_t s21_decimal_get_bit(s21_decimal decimal, int index) {
  return s21_get_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
}

s21_decimal s21_decimal_mul_10(s21_decimal decimal) {
  s21_decimal result;
  s21_decimal_copy(decimal, &result);

  unsigned int rem = 0;
  for (unsigned int i = 0; i < MAX_BIT_BLOCKS * (MAX_BLOCKS - 1); ++i) {
    unsigned int right1 = 0, right3 = 0;
    puts("OK\n");
    if (i > 0) {
      right1 = s21_decimal_get_bit(decimal, i - 1);
    }
    
    if (i > 2) {
      //printf("i - 3 = %u\n", i - 3);
      right3 = s21_decimal_get_bit(decimal, i - 3);
    }

    printf("i = %u r1 = %u r3 = %u rem = %u\n", i, right1, right3, rem);


    s21_decimal_set_bit(decimal, i, (right1 + right3 + rem) % 2);

    rem = (right1 + right3 + rem) / 2;
  }

  return result;
}

s21_decimal s21_decimal_mantis_sub(s21_decimal value_1, s21_decimal value_2) {
  return value_1;;;;;
}

int main() {
  s21_decimal decimal;
  decimal.bits[0] = 0b00000000000000000000000000001010; // 1100100
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[3] = 0b00000000000000000000000100000000;

  decimal = s21_decimal_mul_10(decimal);

  printf("%u", decimal.bits[0]);

}
