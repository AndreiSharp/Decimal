#include "./../../Headers/s21_another_function.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  bit32_t error_code = S21_ANFUNC_SUCCESS;
  error_code = s21_truncate(value, result);
  if (error_code == S21_ANFUNC_SUCCESS) {
    s21_DecData val = s21_decimal_get_data(value);
    if (val.scale) {
      s21_DecData res = s21_decimal_get_data(*result);
      res.sign = val.sign;
      s21_count_mul_10(&res, val.scale);
      s21_sub_mantis(val, res, &val);
      s21_count_div_10(&res, val.scale);
      s21_count_div_10(&val, val.scale - 1);
      if (s21_compare_residue_10(val) != 2) {
        error_code = s21_decimal_add_one(res, &res);
      }
      *result = s21_decimal_set_data(res);
    }
  }
  return error_code;
}