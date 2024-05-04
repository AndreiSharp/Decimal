#include "./../6_Headers/s21_decimal.h"

int s21_add_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res) {
  int flag = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_get_bit(value_1, i) + s21_decimal_get_bit(value_2, i) +
           flag;
    *res = s21_decimal_set_bit(*res, i, flag % 2);
    flag = flag / 2;
  }
  return flag; // изменить
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_result_t flag = S21_ARITHMETIC_OK;

  int sign_value1 = s21_decimal_sign(value_1);
  int sign_value2 = s21_decimal_sign(value_2);

  if (sign_value1 == 0 && sign_value2 == 0) {
    // Нормализация Экспонента
    flag = s21_normalization(&value_1, &value_2);
    // Сложение мантис
    flag = s21_add_two_mantis(value_1, value_2, result);
  } else if (sign_value1 == 1 && sign_value2 == 1) {
    // Нормализация Экспонента
    flag = s21_normalization(&value_1, &value_2);
    // Сложение мантис
    flag = s21_add_two_mantis(value_1, value_2, result);
  }

  return flag;
}