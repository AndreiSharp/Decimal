#include <stdint.h>
#include <stdio.h>

#include "debug.h"

/*--------------------------------CONST---------------------------------*/

enum SIZES {
  MAX_BLOCKS = 4,
  SIZE_BLOCK = 32,
  SIZE_MANTIS = (MAX_BLOCKS - 1) * SIZE_BLOCK,
};

enum POSITIONS {
  EXP_POS_L = 16,
  EXP_POS_R = 23,
  DECIMAL_EXP_POS_L = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_L - 1,
  DECIMAL_EXP_POS_R = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_R - 1,
  SIGN_POS = SIZE_BLOCK - 1,
  DATA_INDEX = MAX_BLOCKS - 1
};

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
    decimal.bits[index / SIZE_BLOCK] =
        s21_reset_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  } else {
    decimal.bits[index / SIZE_BLOCK] =
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

int s21_decimal_sign(s21_decimal decimal) {
  return s21_get_bit(decimal.bits[DATA_INDEX], SIGN_POS);
}

s21_decimal s21_decimal_abs(s21_decimal decimal) {
  decimal.bits[DATA_INDEX] = s21_reset_bit(decimal.bits[DATA_INDEX], SIGN_POS);
  return decimal;
}

void print_binary(unsigned int number) {
  if (number >> 1) {
    print_binary(number >> 1);
  }
  putc((number & 1) ? '1' : '0', stdout);
}

void s21_decimal_print_bit(s21_decimal decimal) {
  for (int i = 0; i < MAX_BLOCKS; ++i) {
    for (int j = 0; j < SIZE_BLOCK; ++j) {
      printf("%d", s21_decimal_get_bit(decimal, i * SIZE_BLOCK + j));
    }
    puts("");
  }
}

int s21_decimal_exp(s21_decimal decimal) {
  if (s21_decimal_sign(decimal)) {
    decimal = s21_decimal_abs(decimal);
  }
  decimal.bits[DATA_INDEX] >>= EXP_POS_L - 1;

  return decimal.bits[DATA_INDEX];
}

s21_decimal s21_decimal_init(s21_decimal *decimal) {
  // s21_from_int_to_decimal(decimal, 0);

  for (int i = 0; i < MAX_BLOCKS; ++i) {
    (*decimal).bits[i] = 0b00000000000000000000000000000000;
  }

  *decimal = s21_decimal_set_bit(*decimal, DECIMAL_EXP_POS_L, 1);

  return *decimal;
}

int s21_decimal_first_set_bit(s21_decimal decimal) {
  int result = -1;
  for (int i = SIZE_MANTIS - 1; i >= 0 && result == -1; --i) {
    if (s21_decimal_get_bit(decimal, i) == 1) {
      result = i;
    }
  }
  return result;
}

int *s21_sub_to_bin(int prefix[], int n, int sub) {
  for (int i = 0, x = 1 << (n - 1); i < n; ++i, x >>= 1) {
    printf("%d %d\n", x, prefix[i]);

    prefix[i] = sub / x;
    sub %= x;

    printf("%d\n", prefix[i]);

    puts("");
  }
  return prefix;
}

s21_decimal s21_decimal_div_10(s21_decimal decimal) {
  s21_decimal result;
  s21_decimal_init(&result);
  int start = s21_decimal_first_set_bit(decimal);

  for (int i = start; i >= 3; --i) {
    if (i == start) {
      int prefix[4] = {
          s21_decimal_get_bit(decimal, i),
          s21_decimal_get_bit(decimal, i - 1),
          s21_decimal_get_bit(decimal, i - 2),
          s21_decimal_get_bit(decimal, i - 3),
      };

      int prefix10 =
          prefix[0] * 8 + prefix[1] * 4 + prefix[2] * 2 + prefix[3] * 1;
      int sub = prefix10 - 10;

      if (sub >= 0) {
        int *new_prefix = s21_sub_to_bin(prefix, 4, sub);

        for (int j = 0; j < 4; ++j) {
          decimal = s21_decimal_set_bit(decimal, i - j, new_prefix[j]);
        }

        result = s21_decimal_set_bit(result, i - 3, 1);
      }
    } else {
      int prefix[5] = {
          s21_decimal_get_bit(decimal, i + 1),
          s21_decimal_get_bit(decimal, i),
          s21_decimal_get_bit(decimal, i - 1),
          s21_decimal_get_bit(decimal, i - 2),
          s21_decimal_get_bit(decimal, i - 3),
      };

      int prefix10 = prefix[0] * 16 + prefix[1] * 8 + prefix[2] * 4 +
                     prefix[3] * 2 + prefix[4] * 1;
      int sub = prefix10 - 10;

      if (sub >= 0) {
        int *new_prefix = s21_sub_to_bin(prefix, 5, sub);

        for (int j = 0; j < 5; ++j) {
          decimal = s21_decimal_set_bit(decimal, i - j + 1, new_prefix[j]);
        }

        result = s21_decimal_set_bit(result, i - 3, 1);
      }
    }
  }

  printf("remander = %d\n", decimal.bits[0]);
  printf("result = %d\n", result.bits[0]);
  printf("exp = %d\n", s21_decimal_exp(decimal));

  return result;
}

int main() {
  s21_decimal decimal;
  decimal.bits[0] = 0b00000000000000000000000011100111;  // 231
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[3] = 0b00000000000000000000000000000000;

  decimal = s21_decimal_set_bit(decimal, DECIMAL_EXP_POS_L, 1);

  decimal = s21_decimal_div_10(decimal);
}
