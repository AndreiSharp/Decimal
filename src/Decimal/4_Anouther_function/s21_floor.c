#include "./../../Headers/s21_another_function.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  bit32_t error_code = S21_ANFUNC_SUCCESS;
  error_code = s21_truncate(value, result);
  if (!error_code) {
    s21_DecData val = s21_decimal_get_data(value);
    if (val.scale) {
      s21_DecData res = s21_decimal_get_data(*result);
      res.sign = val.sign;
      s21_count_mul_10(&res, val.scale);
      s21_sub_mantis(val, res, &val);
      if (!s21_decimal_is_null(val.value)) {
        s21_count_div_10(&res, val.scale);
        s21_count_div_10(&val, val.scale - 1);
      }
      if (val.sign) {
        error_code = s21_decimal_add_one(res, &res);
      }
      if (!error_code) {
        *result = s21_decimal_set_data(res);
      } else {
        *result = s21_decimal_null();
      }
    }
  } else {
    *result = s21_decimal_null();
  }
  return error_code;
}