#include "./../../Headers/s21_another_function.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  bit32_t error_code = S21_ANFUNC_SUCCESS;  // для возврата
  // добавить проверку на корректность децимала
  s21_DecData val = s21_decimal_get_data(value);
  s21_DecData res = s21_decimal_null_data();
  s21_DecData residue = s21_decimal_null_data();
  bit32_t count = val.scale;
  while (count > 0) {
    residue = s21_div_10(&val);
    if (val.sign == 1) {
      s21_DecData ten = s21_decimal_null_data();
      ten.value.bits[0] = 10;
      ten.high_bit = s21_decimal_get_high_bit(ten.value);
      residue.value = s21_decimal_lshift(residue.value);
      residue.high_bit++;
      if (s21_decimal_compare_mantis(residue, ten) == 2) {
        s21_DecData new = s21_decimal_null_data();
        new.value.bits[0] = 1;
        new.high_bit = 0;
        error_code = s21_add_mantis(new, res, &res);
      }
    }
    count--;
  }
  *result = s21_decimal_set_data(res);
  return error_code;
}