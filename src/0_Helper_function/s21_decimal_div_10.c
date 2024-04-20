#include "../include/s21_decimal_help.h"

/**
 * @brief sub prefix of first n bin digits in decimal and 10
 * @author "boilbrit"
 * @param bit_t prefix[] first few bits in decimal
 * @param bit_t n count of bits
 * @return int sub prefix of first n bin digits in decimal and 10
 */
static int s21_get_sub_10(bit_t prefix[], size_t n) {
  unsigned int prefix10 = 0;
  for (int i = 0, pow = 1 << (n - 1); i < n; ++i, pow >>= 1) {
    prefix10 += prefix[i] * pow;
  }
  return prefix10 - 10;
}

/**
 * @brief sub to binary 
 * @author "boilbrit"
 * @param bit_t prefix[] first few bits in decimal
 * @param bit_t n count of bits
 * @param unsigned int sub prefix of sub
 * @return static bit_t[] new prefix
*/
static bit_t *s21_sub_to_bin(bit_t prefix[], size_t n, unsigned int sub) {
  for (int i = 0, pow = 1 << (n - 1); i < n; ++i, pow >>= 1) {
    prefix[i] = sub / pow;
    sub %= pow;
  }
  return prefix;
}

/**
 * @brief division decimal by 10
 * @author "boilbrit"
 * @param decimal source of value
 * @return division decimal by 10
 */
s21_decimal s21_decimal_div_10(s21_decimal decimal) {
  s21_decimal result;
  s21_decimal_init(&result);
  int start = s21_no_zero_bit(decimal);

  for (int i = start; i >= 3; --i) {
    if (i == start) {
      bit_t prefix[4];
      for (int j = 0; j < 4; ++j) {
        prefix[j] = s21_decimal_get_bit(decimal, i - j);
      }

      int sub = s21_get_sub_10(prefix, 4);
      if (sub >= 0) {
        bit_t *new_prefix = s21_sub_to_bin(prefix, 4, sub);
        for (int j = 0; j < 4; ++j) {
          decimal = s21_decimal_set_bit(decimal, i - j, new_prefix[j]);
        }

        result = s21_decimal_set_bit(result, i - 3, 1);
      }
    } else {
      bit_t prefix[5];
      for (int j = 0; j < 5; ++j) {
        prefix[j] = s21_decimal_get_bit(decimal, i - j + 1);
      }

      int sub = s21_get_sub_10(prefix, 5);
      if (sub >= 0) {
        bit_t *new_prefix = s21_sub_to_bin(prefix, 5, sub);
        for (int j = 0; j < 5; ++j) {
          decimal = s21_decimal_set_bit(decimal, i - j + 1, new_prefix[j]);
        }

        result = s21_decimal_set_bit(result, i - 3, 1);
      }
    }
  }

  return result;
}