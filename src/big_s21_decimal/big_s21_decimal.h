#include "../include/s21_decimal.h"

enum {
	BD_MAX_BLOCKS = MAX_BLOCKS * 2,
	BD_SIZE_MANITS = SIZE_BLOCK * BD_MAX_BLOCKS
};

struct big_s21_decimal {
	unsigned int manits[BD_MAX_BLOCKS];
	unsigned int exp, sign;
};
