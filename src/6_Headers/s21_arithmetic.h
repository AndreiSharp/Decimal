#ifndef S21_DECIMAL_ARITHMETC
#define S21_DECIMAL_ARITHMETC

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_types.h"
#include "./s21_help_function.h"

/*-------------------------Arithmetic function---------------------------*/

/*-------------------------------Function--------------------------------*/

// Addition
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Subraction
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Multiplication
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Division
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*-----------------------------------------------------------------------*/

#endif