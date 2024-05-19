#include "./../../Headers/s21_arithmetic_function.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bit32_t code_error = S21_SUCCES;
  // проверка на не пустой указатель
  s21_DecData val_data_1 = s21_decimal_get_data(value_1);
  s21_DecData val_data_2 = s21_decimal_get_data(value_2);
  s21_DecData result_data = s21_decimal_null_data();
  // нормализация (приведение двух децимал числе к общему знаменателю)
  code_error = s21_basic_add(val_data_1, val_data_2, &result_data);
  *result = s21_decimal_set_data(result_data);
  return code_error;
}