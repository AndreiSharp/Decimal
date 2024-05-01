#include "./../6_Headers/s21_help_function.h"

unsigned int s21_get_sign(s21_decimal decimal) {
  return s21_get_bit(decimal.bits[DATA_INDEX], SIGN_POS);
}

s21_decimal s21_decimal_abs(s21_decimal value) {
  value.bits[DATA_INDEX] = s21_reset_bit(value.bits[DATA_INDEX], SIGN_POS);
  return value;
}

unsigned int s21_get_exp(s21_decimal value) {
  int exp = value.bits[DATA_INDEX];
  if (s21_get_sign(value)) {
    value = s21_decimal_abs(value);
  }
  value.bits[DATA_INDEX] >>= EXP_POS_L - 1;
  return value.bits[DATA_INDEX];
}

unsigned int s21_decimal_add_exp(s21_decimal *value, int count) {
  int flag = S21_SUCCES;
  int sign = s21_get_sign(*value);
  *value = s21_decimal_abs(*value);
  int exp = s21_get_exp(*value);
  if (exp + count <= 28 && flag) {
    value->bits[DATA_INDEX] >>= EXP_POS_L;
    value->bits[DATA_INDEX] += count;
    value->bits[DATA_INDEX] <<= EXP_POS_L;
  } else {
    flag = S21_ERROR;
  }
  return flag;
}

unsigned int s21_decimal_sub_exp(s21_decimal *value, int count) {
  int flag = S21_SUCCES;
  int sign = s21_get_sign(*value);
  (*value) = s21_decimal_abs(*value);
  int exp = s21_get_exp(*value);
  if (exp - count >= 0 && flag) {
    value->bits[DATA_INDEX] >>= EXP_POS_L;
    value->bits[DATA_INDEX] -= count;
    value->bits[DATA_INDEX] <<= EXP_POS_L;
  } else {
    flag = S21_ERROR;
  }
  return flag;
}

unsigned int s21_add_two_mantis(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result) {
  s21_decimal *new;
  s21_decimal_init(new);
  unsigned int flag = S21_SUCCES;
  unsigned int res = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    res = s21_decimal_is_set_bit(value_1, i) +
          s21_decimal_is_set_bit(value_2, i) + res;
    *new = s21_decimal_set_bit(*new, i, res % 2);
    res = res / 2;
  }
  if (res) {
    flag = S21_TOO_LARGE;
  } else {
    result = new;
  }
  return flag;
}

unsigned int s21_sub_two_mantis(s21_decimal value_1, s21_decimal value_2,
                                s21_decimal *result) {
  s21_decimal *new;
  s21_decimal_init(new);
  unsigned int flag = S21_SUCCES;
  unsigned int res_div = 0;
  unsigned int duty = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    res_div =
        s21_decimal_is_set_bit(value_1, i) - s21_decimal_is_set_bit(value_2, i);
    if (res_div - duty >= 0) {
      *new = s21_decimal_set_bit(*new, i, res_div + flag);
      duty = 0;
    } else {
      *new = s21_decimal_set_bit(*new, i, 1);
      duty = 1;
    }
  }
  if (duty) {
    flag = S21_TOO_SMALL;
  } else {
    result = new;
  }
  return flag;
}
