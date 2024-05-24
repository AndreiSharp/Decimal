#ifndef S21_ARITH_FUNC
#define S21_ARITH_FUNC

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_function.h"
#include "./s21_decimal_types.h"
#include "./s21_help_function.h"

/*---------------------------Arithmetic_function-------------------------*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif