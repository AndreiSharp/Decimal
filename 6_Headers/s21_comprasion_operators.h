#ifndef S21_COMPRASION_OPERATORS
#define S21_COMPRASION_OPERATORS

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_types.h"

/*-------------------------Comprasion operators--------------------------*/

/*---------------------------------CONST---------------------------------*/

#define S21_TRUE 1
#define S21_FALSE 1

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

/*-----------------------------------------------------------------------*/

#endif