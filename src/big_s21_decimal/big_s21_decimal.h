#include "../include/s21_decimal.h"

enum {
  BD_MAX_BLOCKS = MAX_BLOCKS * 2,
  BD_SIZE_MANTIS = SIZE_BLOCK * BD_MAX_BLOCKS
};

typedef struct {
  unsigned int mantis[BD_MAX_BLOCKS];
  unsigned int exp, sign;
} big_s21_decimal;
