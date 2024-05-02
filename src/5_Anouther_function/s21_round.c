#include "../include/s21_decimal.h"

/*
 @brief Rounds a decimal value to the nearest integer
 @author yrelcary
 @param value
 @param result
 @return int ошибки
 */

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  // нужно добавить проверку на корректность числа!!!!!

  s21_decimal_init(&result);
  // считывем знак
  int sign = s21_decimal_sign(value);
  // создаем децимал без знака
  s21_decimal value_without_sign;
  value_without_sign = s21_decimal_abs(value);
  // создаем децимал без знака с отбрасыванием дробной части
  s21_decimal value_without_sign_truncated;
  s21_truncate(value_without_sign, &value_without_sign_truncated);
  // создаем дцемал для записи дробной части
  s21_decimal drobnay_chast;
  flag =
      s21_sub(value_without_sign, value_without_sign_truncated, &drobnay_chast)
      // делаем округление с учетом дробной части
      value_without_sign_truncated =
          s21_round_banking(value_without_sign_truncated, drobnay_chast);
  // возращаем знак и записываем децимал в результат
  *result = s21_decimal_set_bit(value_without_sign_truncated, 127, sign);
  return flag;
}