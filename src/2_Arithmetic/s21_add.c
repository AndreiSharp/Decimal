#include "./../6_Headers/s21_arithmetic.h"
// !Необходимо заменить функцию s21_is_greater на функцию только проверки мантис
// !Необходимо в вычитании добавить
// !Необходимо добавить

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int flag = S21_SUCCES;
  flag = s21_decimal_is_correct(value_1);
  flag = (!flag) ? s21_decimal_is_correct(value_2) : S21_ERROR;
  if (result || !flag) {
    flag = s21_normalization(&value_1, &value_2);
    if (!flag) {
      unsigned int sign_1 = s21_get_sign(value_1);
      unsigned int sign_2 = s21_get_sign(value_2);
      if (sign_1 == sign_2) {
        flag = s21_add_two_mantis(value_1, value_2, result);
      } else {
        if (s21_is_greater(value_1, value_2)) {
          flag = s21_sub_two_mantis(value_1, value_2, result);
        } else {
          flag = s21_sub_two_mantis(value_2, value_1, result);
        }
      }
      if (!flag) {
        result->bits[DATA_INDEX] = value_1.bits[DATA_INDEX];
      }
    }
  } else {
    flag = S21_ERROR;
  }
  return flag;
}