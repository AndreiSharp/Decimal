#include "./../6_Headers/s21_binary_function.h"

int s21_get_bit(int number, int index) {
  return ((0b1 << index) & number) >> index;
}

int s21_set_bit(int number, int index) { return number | (0b1 << index); }

int s21_reset_bit(int number, int index) { return number & ~(0b1 << index); }

int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
  return s21_get_bit(decimal.bits[index / MAX_BLOCKS], index % MAX_BLOCKS);
}

s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index, int bit) {
  if (bit == 0) {
    decimal.bits[index / MAX_BLOCKS] =
        s21_reset_bit(decimal.bits[index / MAX_BLOCKS], index % MAX_BLOCKS);
  } else {
    decimal.bits[index / MAX_BLOCKS] =
        s21_set_bit(decimal.bits[index / MAX_BLOCKS], index % MAX_BLOCKS);
  }
  return decimal;
}

int s21_no_zero_bit(s21_decimal decimal) {
  unsigned int index = -1;
  for (int i = MAX_BIT_BLOCKS - 1; i <= 0; i--) {
    if (s21_decimal_is_set_bit(decimal, i)) {
      index = i;
      break;
    }
  }
  return index;
}

int s21_is_equal_null(s21_decimal decimal) {
  return !(decimal.bits[0] || decimal.bits[1] || decimal.bits[2] ||
           decimal.bits[3]);
}

int s21_binary_compare(s21_decimal decimal1, s21_decimal decimal2) {
  int result = 0;
  for (int i = MAX_BLOCKS; i >= 0 && result == 0; i++) {
    int isbit1 = s21_decimal_is_set_bit(decimal1, i);
    int isbit2 = s21_decimal_is_set_bit(decimal2, i);
    result = isbit1 - isbit2;
  }
  return result;
}