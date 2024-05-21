#include "../include/s21_decimal.h"

int exp_plus(s21_decimal *value_1, int count) {
  int flag = S21_SUCCES;
  //Узнаем знак числа
  int sign = s21_decimal_sign(*value_1);
  //Берем модуль числа
  *value_1 = s21_decimal_abs(*value_1);
  //Сдвигаем третий блок на 15 позиций
  (*value_1).bits[DATA_INDEX] >>= EXP_POS_L - 1;
  //Увеличиваем экспонент до нужной суммы
  (*value_1).bits[DATA_INDEX] += count;
  //Проверяем на допустимые пределы
  if ((*value_1).bits[DATA_INDEX] > 28) {
    flag = S21_TOO_SMALL;
  }
  //Сдвигаем третий блок на 15 позиций обратно
  (*value_1).bits[DATA_INDEX] <<= EXP_POS_L - 1;
  //Возращаем знак числа
  *value_1 = s21_decimal_set_bit(*value_1, DECIMAL_SIGN_POS, sign);
  return flag;
}

unsigned int s21_count_mul10(s21_decimal *value, int count) {
  for (int i = 0; i < count; i++) {
    // Умножение мантисы на 10
    *value = s21_decimal_mul_10(*value);
  }
  return 0;
}

unsigned int s21_check_normalization(s21_decimal value_1, s21_decimal value_2) {
  unsigned int flag = 0;
  int exp_1 = s21_decimal_exp(value_1);
  int exp_2 = s21_decimal_exp(value_2);
  if (exp_1 < exp_2) {
    flag = 1;
  } else if (exp_1 > exp_2) {
    flag = 2;
  } else {
    flag = 0;
  }
  return flag;
}

// unsigned int s21_normalization(s21_decimal *value_1, s21_decimal *value_2) {
//   unsigned int flag = S21_SUCCES;
//   if (value_1 && value_2) {
//     int exp_1 = s21_decimal_exp(*value_1);
//     int exp_2 = s21_decimal_exp(*value_2);
//     if (exp_1 > exp_2) {
//       flag = s21_count_mul10(value_2, exp_1 - exp_2);
//       flag = exp_plus(value_2, exp_1 - exp_2);
//     } else if (exp_2 > exp_1) {
//       flag = s21_count_mul10(value_1, exp_2 - exp_1);
//       flag = exp_plus(value_1, exp_2 - exp_1);
//     }
//   } else {
//     flag = S21_ERROR;
//   }
//   return flag;
// }
