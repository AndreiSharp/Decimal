#include "./../../Headers/s21_another_function.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  bit32_t error_code = S21_ANFUNC_SUCCESS;
  error_code = s21_truncate(value, result);
  if (error_code) {
    s21_DecData val = s21_decimal_get_data(value);
    s21_DecData res = s21_decimal_get_data(*result);
    if (val.sign) {
      error_code = s21_decimal_add_one(res, &res);
    }
    if (!error_code) {
      *result = s21_decimal_set_data(res);
    } else {
      *result = s21_decimal_null();
    }
  } else {
    *result = s21_decimal_null();
  }
  return error_code;
}