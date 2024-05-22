#ifndef S21_COMPRASION
#define S21_COMPRASION

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_function.h"
#include "./s21_decimal_types.h"
#include "./s21_help_function.h"

/*----------------------------Comprasion function---------------------------*/
// Less than
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

// Less than or equal
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// Greater than
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

// Greater than or equal to
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

// Equal to
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

// Not equal to
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

#endif