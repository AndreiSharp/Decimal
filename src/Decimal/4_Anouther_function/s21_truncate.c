#include "./../../Headers/s21_another_function.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0;  //// добавить ошибки при вычислении (если переменные не по
                 /// формату и тп)
  s21_DecData val = s21_decimal_get_data(value);
  if (val.high_bit - 3 * val.scale >= 0) {
    for (int i = val.scale; i > 0; i--) {
      s21_div_10(&val);
    }
    *result = s21_decimal_set_data(val);
  } else {
    *result = s21_decimal_null();
  }
  return flag;
}