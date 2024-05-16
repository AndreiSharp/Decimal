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
  s21_decimal_init(result);
  // считывем знак
  int sign = s21_decimal_sign(value);
  // создаем децимал без знака
  s21_decimal value_without_sign;
  value_without_sign = s21_decimal_abs(value);
  // создаем децимал без знака с отбрасыванием дробной части
  s21_decimal value_without_sign_truncated;
  s21_truncate(value_without_sign, &value_without_sign_truncated);
  // создаем децемал для записи дробной части
  s21_decimal drobnay_chast;
  s21_decimal_init(&drobnay_chast);
  flag =
      s21_sub(value_without_sign, value_without_sign_truncated, &drobnay_chast);
  // создаем децимал 0.5 для сравнения с другими децималами
  s21_decimal zero_dot_five = {{5, 0, 0, 0b00000000000000001000000000000000}};
  // создаем децимал = 1 для сравнения с другим децималом
  s21_decimal decimal_one = {{1, 0, 0, 0}};
  // проверка на равенство 0.5
  if (s21_is_greater_or_equal(drobnay_chast, zero_dot_five)) {
    // если функция возращает 1, то оно больше или равно ,5 и мы прибавляем 1
    s21_add_two_mantis(value_without_sign_truncated, decimal_one, result);
  } else {
    // в ином случае оставляем число без изменений
    *result = value_without_sign_truncated;
  }
  // возращаем знак и записываем децимал в результат
  *result = s21_decimal_set_bit(value_without_sign_truncated, 127, sign);
  return flag;
}
