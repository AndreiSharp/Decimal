#ifndef S21_DECIMAL_ARITHMETC
#define S21_DECIMAL_ARITHMETC

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_types.h"

/*-------------------------Arithmetic function---------------------------*/

/*---------------------------------CONST---------------------------------*/

#define S21_TOO_LARGE 1  // The number is too large or equal to infinity
#define S21_TOO_SMALL \
  2  // The number is too small or equal to negative infinity
#define S21_DEV_BY_ZERO 3  // Division by 0
#define S21_ERROR 4
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