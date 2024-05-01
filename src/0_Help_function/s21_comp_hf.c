#include "./../6_Headers/s21_help_function.h"

void s21_compare_mantis(s21_decimal value_1, s21_decimal value_2,
                        int *first_number, int *second_number) {
  int flag_stop = 0;
  for (int i = SIZE_MANTIS; i >= 0 && flag_stop != 1; i--) {
    int high_bit1 = s21_decimal_get_bit(value_1, i);
    int high_bit2 = s21_decimal_get_bit(value_2, i);
    if (high_bit1 != high_bit2) {
      *first_number = high_bit1;
      *second_number = high_bit2;
      flag_stop = 1;
    }
  }
}

void s21_compare_decimal(s21_decimal value_1, s21_decimal value_2,
                         int *first_number, int *second_number) {
  s21_normalization(&value_1, &value_2);
  s21_compare_mantis(value_1, value_2, first_number, second_number);
}

void s21_function_compare(s21_decimal value_1, s21_decimal value_2,
                          int *first_number, int *second_number) {
  int sign1 = s21_decimal_sign(value_1);
  int sign2 = s21_decimal_sign(value_2);
  int exp1 = s21_decimal_exp(value_1);
  int exp2 = s21_decimal_exp(value_2);
  if (sign1 != sign2) {
    if (sign1 == 1) {
      *second_number = 1;
    } else {
      *first_number = 1;
    }
  } else if (exp1 == exp2) {
    s21_compare_mantis(value_1, value_2, first_number, second_number);

  } else {
    s21_compare_decimal(value_1, value_2, first_number, second_number);
  }
}