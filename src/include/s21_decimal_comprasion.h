#include "s21_decimal_types.h"

/*---------------------------------CONST---------------------------------*/

enum s21_comprasion_result { S21_TRUE = 1, S21_FALSE = 0 };

/*-------------------------------Function--------------------------------*/

// Less than
int s21_is_less(s21_decimal, s21_decimal);

// Less than or equal
int s21_is_less_or_equal(s21_decimal, s21_decimal);

// Greater than
int s21_is_greater(s21_decimal, s21_decimal);

// Greater than or equal to
int s21_is_greater_or_equal(s21_decimal, s21_decimal);

// Equal to
int s21_is_equal(s21_decimal, s21_decimal);

// Not equal to
int s21_is_not_equal(s21_decimal, s21_decimal);

