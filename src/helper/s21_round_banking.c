#include "../include/s21_decimal_help.h"

/*
 @brief банковское округление
 @author yrelcary
 @param value
 @param drobnay_chast
 @return decimal result
 */

s21_decimal s21_round_banking(s21_decimal value, s21_decimal drobnay_chast) {
  // создаем децимал, который будем возращать
  s21_decimal result;
  s21_decimal_init(&result);
  // создаем децимал 0.5 для сравнения с другими децималами
  s21_decimal zero_dot_five = {{5, 0, 0, 0b00000000000000001000000000000000}};
  // создаем децимал = 1 для сравнения с другими децималами
  s21_decimal decimal_one = {{1, 0, 0, 0}};
  // проверка на равенство 0.5
  if (s21_is_equal(drobnay_chast, zero_dot_five)) {
    // проверка на нечетное и четное число
    if (s21_decimal_get_bit(value, 0)) {
      // если функция возращает 1, то оно нечетное и мы прибавляем 1
      s21_add_two_mantis(value, decimal_one, &result);
    } else {
      // в ином случае оставляем число без изменений
      result = value;
    }
    // Если дробная часть больше 0.5, то прибавляем 1
  } else if (s21_is_greater(drobnay_chast, zero_dot_five)) {
    s21_add_two_mantis(value, decimal_one, &result);
  } else {
    // в ином случае оставляем число без изменений
    result = value;
  }
  return result;
}
