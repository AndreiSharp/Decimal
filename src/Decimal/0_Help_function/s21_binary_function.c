#include "./../../Headers/s21_binary_function.h"

// работает
bit_t s21_get_bit(bit32_t number, int index) {
  return ((0b1 << index) & number) >> index;
}

// работает
bit32_t s21_set_bit(bit32_t number, int index) {
  return number | (0b1 << index);
}

// работает
bit32_t s21_reset_bit(bit32_t number, int index) {
  return number & ~(0b1 << index);
}

// работает
bit32_t s21_get_high_bit(bit32_t value) {
  bit32_t index = SIZE_BLOCK;
  while (index >= 0 && !s21_get_bit(value, index)) {
    index--;
  }
  return (bit32_t)(index + 1);
}

// работает
bit_t s21_decimal_get_bit(s21_decimal value, int index) {
  return s21_get_bit(value.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
}

// работает
s21_decimal s21_decimal_set_bit(s21_decimal value, int index, bit_t bit) {
  if (bit == 0) {
    value.bits[index / SIZE_BLOCK] =
        s21_reset_bit(value.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  } else {
    value.bits[index / SIZE_BLOCK] =
        s21_set_bit(value.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  }
  return value;
}

// работает
bit32_t s21_decimal_get_high_bit(s21_decimal value) {
  int index = SIZE_DECIMAL;
  for (int i = DATA_INDEX; i > 0 && !value.bits[i]; i--) {
    if (!value.bits[i]) {
      index -= SIZE_BLOCK;
    }
  }
  while (index != -1 && !s21_decimal_get_bit(value, index)) {
    index--;
  }
  return (bit32_t)(index + 1);
}

// работает
bit32_t s21_decimal_get_sign(s21_decimal value) {
  return s21_decimal_get_bit(value, SIGN_POS + SIZE_MANTIS);
}

// работает
s21_decimal s21_decimal_set_sign(s21_decimal value, bit32_t bit) {
  return s21_decimal_set_bit(value, SIGN_POS + SIZE_MANTIS, bit);
}

// работает
s21_decimal s21_decimal_abs(s21_decimal value) {
  return s21_decimal_set_sign(value, 0);
}

// работает
bit32_t s21_decimal_get_scale(s21_decimal value) {
  bit32_t scale;
  value = s21_decimal_abs(value);
  scale = value.bits[DATA_INDEX] >> SCALE_POS_L;
  return scale;
}

// работает
s21_decimal s21_decimal_set_scale(s21_decimal value, bit32_t scale) {
  bit32_t sign = s21_decimal_get_sign(value);
  value.bits[DATA_INDEX] = scale << SCALE_POS_L;
  return s21_decimal_set_sign(value, sign);
}