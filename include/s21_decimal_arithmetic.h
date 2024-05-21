#include "s21_decimal_types.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------CONST---------------------------------*/

#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0
#define BADINT (unsigned int)0x80000000
#define START_INFO 96

enum s21_arithmetic_result {
  S21_SUCCES = 0,       // OK
  S21_TOO_LARGE = 1,    // The number is too large or equal to infinity
  S21_TOO_SMALL = 2,    // The number is too small or equal to negative infinity
  S21_DEV_BY_ZERO = 3,  // Division by 0
  S21_ERROR = 4         // Another Error
};

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

/*-------------------------------Function--------------------------------*/

// // Addition
// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// // Subraction
// int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// // Multiplication
// int s21_mul(s21_decimal value_1, s21_decimal value_2,
//             s21_decimal *result);  // boilbrit

// // Division
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void s21_add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);

void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);

int s21_mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);

int s21_get_scale(s21_decimal dst);
void s21_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2,
                       int diff);
void s21_set_scale(s21_decimal *dst, int scale);
void s21_increase_scale_big_decimal(s21_big_decimal *dst, int n);
void s21_decreace_scale_big_decimal(s21_big_decimal *dst, int n);
void s21_find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                      int *bit_1, int *bit_2);
int s21_is_big_decimal_not_empty(s21_big_decimal dst);
int s21_equation_bits_big_decimal(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2);
int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2);
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2);
int s21_get_integer_part(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);

void s21_normalize(s21_decimal *d1, s21_decimal *d2);
void s21_normalize_scale_upper(s21_decimal *d, int norm);
void s21_copy_decimal(s21_decimal *d1, s21_decimal d2);
int s21_post_normalization(s21_big_decimal *result, int scale);