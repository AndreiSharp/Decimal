#ifndef S21_CONVERTATION_AND_PARSERS
#define S21_CONVERTATION_AND_PARSERS

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_types.h"
#include "./s21_help_function.h"

/*-----------------------CONVERTATION AND PARSERS------------------------*/

/*-------------------------------Function--------------------------------*/

// From int
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// From float
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// To int
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// To float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*-----------------------------------------------------------------------*/
#endif