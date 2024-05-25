#ifndef S21_CONV_FUNC
#define S21_CONV_FUNC

#include <math.h>

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_function.h"
#include "./s21_decimal_types.h"
#include "./s21_help_function.h"

/*-------------------Convertation_and_parsers_function------------------*/

// From int
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// From float
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// To int
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// To float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif
