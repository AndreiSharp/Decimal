#include "s21_decimal_types.h"

/*---------------------------------CONST---------------------------------*/

enum s21_conv_result {
  S21_CONV_ERROR = 1,  // Convertation error
  S21_CONV_SUCCESS = 0
};

/*-------------------------------Function--------------------------------*/

// From int
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// From float
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// To int
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// To float
int s21_from_decimal_to_float(s21_decimal src, float *dst);


