#include "../include/s21_decimal.h"

static void s21_decimal_shift_mantis(s21_decimal *decimal) {
  bit_t buff = 0;
  for (unsigned int i = 0; i < DATA_INDEX; ++i) {
    bit_t new_buff = s21_decimal_get_bit(*decimal, (i + 1) * SIZE_BLOCK - 1);
    decimal->bits[i] <<= 1;

    if (i != 0) {
      *decimal = s21_decimal_set_bit(*decimal, i * SIZE_BLOCK, buff);
    }
    buff = new_buff;
  }
}

int s21_decimal_mul_two_mantis(s21_decimal value_1, s21_decimal value_2,
                               s21_decimal *res) {
  s21_decimal_init(res);

  unsigned int error_code = S21_SUCCES;

  for (unsigned int i = 0; i < MAX_MANTIS; ++i) {
    bit_t cur_bit = s21_decimal_get_bit(value_2, i);

    if (cur_bit == 1) {
      s21_add_two_mantis(value_1, value_2, res);
    }

    s21_decimal_shift_mantis(&value_1);
  }

  return error_code;
}