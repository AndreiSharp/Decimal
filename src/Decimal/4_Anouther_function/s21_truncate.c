#include "./../../Headers/s21_another_function.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = S21_ANFUNC_SUCCESS;  //// добавить ошибки при вычислении (если
                                  ///переменные не по
                                  /// формату и тп)
  s21_DecData val = s21_decimal_get_data(value);
  s21_DecData res = s21_decimal_null_data();
  res.sign = val.sign;
  if ((int)val.high_bit - 3 * val.scale >= 0) {
    for (int i = val.scale; i > 0; i--) {
      s21_div_10(&val);
    }
    res.value = val.value;
    res.high_bit = val.high_bit;
    *result = s21_decimal_set_data(res);
  } else {
    *result = s21_decimal_null();
  }
  return flag;
}