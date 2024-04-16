#include "./../6_Headers/s21_decimal.h"

// Addition
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int error_code = S21_SUCCES;
  if (!result) {
    error_code = S21_ERROR;
  } else {
  }
  return 0;
}

int s21_check_normalization(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int exp_1 = s21_take_exp(value_1);
  int exp_2 = s21_take_exp(value_2);
  if (exp_1 < exp_2) {
    flag = 1;
  } else if (exp_1 > exp_2) {
    flag = 2;
  }
  return exp_1 - exp_2;
}

int s21_normalization(s21_decimal *value_1, s21_decimal *value_2) {
  int flag = s21_check_normalization(*value_1, *value_2);
  if (flag > 0) {
  } else if (flag < 0) {
    flag *= -1;
  }
  return 0;
}

int s21_count_mul10(s21_decimal *value, int count) {
  for (int i = 0; i < count; i++) {
    *value = s21_mul10(*value);
  }
}

s21_decimal s21_mul10(s21_decimal value) {
  s21_decimal res;
  res.bits[0] = value.bits[0];
  res.bits[1] = value.bits[1];
  res.bits[2] = value.bits[2];
  res.bits[3] = value.bits[3];
  int flag = 0;
  for (int i = 1; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_is_set_bit(res, i - 1) +
           s21_decimal_is_set_bit(value, i) + flag;
    res = s21_decimal_set_bit(value, i, flag % 2);
    flag = flag / 2;
  }
  for (int i = 3; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_is_set_bit(res, i - 3) +
           s21_decimal_is_set_bit(value, i) + flag;
    res = s21_decimal_set_bit(value, i, flag % 2);
    flag = flag / 2;
  }
  return res;
}

int s21_count_div10(s21_decimal valu, int count) {
  for (int i = 0; i < count; i++) {
  }
}

s21_decimal s21_div10(s21_decimal value) {
  s21_decimal res;
  res.bits[0] = value.bits[0];
  res.bits[1] = value.bits[1];
  res.bits[2] = value.bits[2];
  res.bits[3] = value.bits[3];
  int flag = 0;
  // for () return res;
}

/**
 * @brief sum two mantis
 * @author morsbard
 * @param value_1 first summand
 * @param value_2 first summand
 * @param res pointer to decimal number that result of sum two mantis
 * @return decimal number that result of sum two mantis
 */
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

/**
 * @brief subtraction of two mantis
 * @author morsbard
 * @param value_1 diminutive
 * @param value_2 deductible
 * @param res pointer to decimal number of residual
 * @return the code of the function execution:
 *      0 - SUCSESS
 *      1 - ERROR
 */
int s21_sub_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res) {
  int flag = 0;
  int res_div = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    res_div =
        s21_decimal_is_set_bit(value_1, i) - s21_decimal_is_set_bit(value_2, i);
    if (res_div + flag >= 0) {
      *res = s21_decimal_set_bit(*res, i, res_div + flag);
      flag = 0;
    } else {
      flag = -1;
      *res = s21_decimal_set_bit(*res, i, 0);
    }
  }
  return flag * (-1);
}