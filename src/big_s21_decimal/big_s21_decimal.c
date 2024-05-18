#include "big_s21_decimal.h"

#include "../include/s21_decimal.h"

void big_s21_decimal_init(big_s21_decimal *big_decimal) {
  big_decimal->exp = 0;
  big_decimal->sign = 0;
  for (int i = 0; i < BD_MAX_BLOCKS; ++i) {
    big_decimal->mantis[i] = 0;
  }
}

big_s21_decimal s21_from_decimal_to_big_decimal(s21_decimal decimal) {
  big_s21_decimal big_decimal;
  big_s21_decimal_init(&big_decimal);

  big_decimal.mantis[0] = decimal.bits[0];
  big_decimal.mantis[1] = decimal.bits[1];
  big_decimal.mantis[2] = decimal.bits[2];
  big_decimal.exp = s21_decimal_exp(decimal);
  big_decimal.sign = s21_decimal_sign(decimal);
}

unsigned int bit_s21_decimal_is_set_bit() {
  
}


big_s21_decimal big_s21_decimal_add_mantis(big_s21_decimal value_1,
                                           big_s21_decimal value_2) {
  big_s21_decimal res;
  big_s21_decimal_init(&res);

  unsigned int buf = 0;
  for (unsigned int bit = 0; bit < BD_SIZE_MANTIS; ++bit) {
    buf = s21_decimal_is_set_bit(value_1, bit) +
          s21_decimal_is_set_bit(value_2, bit) + buf;
    *res = s21_decimal_set_bit(*res, i, buf % 2);
    buf /= 2;
  }

  return buf;
}

big_s21_decimal big_s21_decimal_sub_manits(big_s21_decimal value_1,
                                           big_s21_decimal value_2) {
  big_s21_decimal res;

  for (unsigned int bit = 0; bit < BD_SIZE_MANTIS; ++bit) {
    int sub = s21_decimal_is_set_bit(value_1, bit) -
              s21_decimal_is_set_bit(value_2, bit);
    if (sub == -1) {
      value_1 = s21_decimal_set_bit(value_1, bit + 1, 1);
    } else {
    }
  }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int flag = S21_SUCCES;
  int sign_value1 = s21_decimal_sign(value_1);
  int sign_value2 = s21_decimal_sign(value_2);
  if (sign_value1 == sign_value2) {
    flag = s21_normalization(&value_1, &value_2);
    if (flag) {
      flag = s21_add_two_mantis(value_1, value_2, result);
    }
  } else {
    if (s21_is_greater(value_1, value_2)) {
      flag = s21_sub_two_mantis(value_1, value_2, result);
    } else {
      flag = s21_sub_two_mantis(value_2, value_1, result);
    }
  }
  return flag;
}

void big_s21_add(big_s21_decimal value_1, big_s21_decimal value_2,
                 big_s21_decimal *res) {
  big_s21_decimal_init(res);

  res->exp = s21_decimal_exp(value_1) + s21_decimal_exp(value_2);
  if (value_1.sign == value_2.sign) {
  } else {
  }
}
