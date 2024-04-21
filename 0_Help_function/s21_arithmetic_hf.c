#include "./../6_Headers/s21_help_function.h"

int s21_get_sign(s21_decimal decimal) {
  return s21_get_bit(decimal.bits[DATA_INDEX], SIGN_POS);
}

s21_decimal s21_decimal_abs(s21_decimal value) {
  value.bits[DATA_INDEX] = s21_reset_bit(value.bits[DATA_INDEX], SIGN_POS);
  return value;
}

int s21_get_exp(s21_decimal value) {
  int exp = 0b1;
  exp = value.bits[DATA_INDEX];
  if (s21_get_bit(exp, SIGN_POS)) {
    s21_reset_bit(exp, SIGN_POS);
  }
  exp >> 16;
  return exp;
}

int s21_decimal_add_exp(s21_decimal *value, int count) {
  int flag = S21_SUCCES;
  int sign = s21_get_sign(*value);
  s21_decimal_abs(value);
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

int s21_decimal_sub_exp(s21_decimal *value, int count) {
  int flag = S21_SUCCES;
  int sign = s21_get_sign(*value);
  s21_decimal_abs(value);
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

int s21_add_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res) {
  int flag = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_is_set_bit(value_1, i) +
           s21_decimal_is_set_bit(value_2, i) + flag;
    *res = s21_decimal_set_bit(*res, i, flag % 2);
    flag = flag / 2;
  }
  return flag;
}

int s21_sub_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res) {
  int flag = 0;
  int res_div = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    res_div =
        s21_decimal_is_set_bit(value_1, i) - s21_decimal_is_set_bit(value_2, i);
    if (res_div - flag >= 0) {
      *res = s21_decimal_set_bit(*res, i, res_div + flag);
      flag = 0;
    } else {
      flag = 1;
      *res = s21_decimal_set_bit(*res, i, 1);
    }
  }
  return flag;
}