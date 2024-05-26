#include "./../../Headers/s21_arithmetic_function.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bit32_t code_error = S21_SUCCES;

  if (s21_decimal_is_null(value_1) || s21_decimal_is_null(value_2)) {
    *result = s21_decimal_null();
  } else {
    s21_DecData val_data_1 = s21_decimal_get_data(value_1);
    s21_DecData val_data_2 = s21_decimal_get_data(value_2);
    s21_DecData result_data = s21_decimal_null_data();
    code_error = s21_basic_mul(val_data_1, val_data_2, &result_data);
    *result = s21_decimal_set_data(result_data);
  }
  return code_error;
}