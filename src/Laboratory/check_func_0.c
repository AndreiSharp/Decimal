#include "./../Headers/s21_decimal.h"

int main() {
  s21_decimal value_1 = {{3, 0, 0, 0}};
  s21_decimal value_2 = {{4, 0, 0, 0}};
  int key = 0;
  s21_from_decimal_to_int(value_2, &key);
  printf("key = %d\n", key);
  // value_1 = s21_decimal_set_sign(value_1, 1);
  // value_2 = s21_decimal_set_sign(value_2, 1);
  // value_1 = s21_decimal_invert(value_1, COUNT_BLOCKS_MANTIS);
  // value_2 = s21_decimal_set_scale(value_2, 4);
  // value_1 = s21_decimal_set_scale(value_1, 4);
  print_decimal(value_1, "start value_1");
  print_decimal(value_2, "start value_2");
  s21_decimal result;
  bit32_t code_func = s21_mul(value_1, value_2, &result);
  printf("code_func = %u\n", code_func);
  printf("correct = %d\n", s21_decimal_is_correct(result));
  print_decimal(result, "start result");
  return code_func;
}