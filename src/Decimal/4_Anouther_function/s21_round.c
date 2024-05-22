#include "./../../Headers/s21_another_function.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  bit32_t error_code = S21_ANFUNC_SUCCESS;
  error_code = s21_truncate(value, result);
  if (error_code) {
    s21_DecData val = s21_decimal_get_data(value);
    s21_DecData res = s21_decimal_get_data(*result);
    s21_sub_mantis(val, res, &val);
    if (s21_compare_residue_10(res) != 2) {
      s21_DecData new = s21_decimal_null_data();
      new.value.bits[0] = 1;
      new.high_bit = 1;
      error_code = s21_add_mantis(new, res, &res);
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