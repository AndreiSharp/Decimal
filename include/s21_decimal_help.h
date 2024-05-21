
// здесь какая-то помойка, это надо исправить

#pragma once

#include "s21_decimal_types.h"


// get sign of s21_decimal
unsigned int s21_decimal_sign(s21_decimal decimal);

// get absolutely value of s21_decimal
s21_decimal s21_decimal_abs(s21_decimal decimal);

// get exponent value of s21_decimal
unsigned int s21_decimal_exp(s21_decimal decimal);

// copy decimal from src to dest
s21_decimal s21_decimal_copy(s21_decimal src, s21_decimal *dest);

s21_decimal s21_decimal_init(s21_decimal *decimal);

int s21_mantis_is_equal_null(s21_decimal decimal);

void change_sign_if_zero(s21_decimal *value);

void compare_mantis(s21_decimal value_1, s21_decimal value_2, int *first_number, int *second_number);

void compare_decimal(s21_decimal value_1, s21_decimal value_2,
                     int *first_number, int *second_number);

void change_sign_if_zero(s21_decimal *value);

void function_compare(s21_decimal value_1, s21_decimal value_2,
                      int *first_number, int *second_number);

int s21_add_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res);

int s21_sub_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res);

s21_decimal s21_decimal_mul_10(s21_decimal decimal);
s21_decimal s21_decimal_div_10(s21_decimal decimal);

// unsigned int s21_normalization(s21_decimal *value_1, s21_decimal *value_2);

int s21_decimal_mul_two_mantis(s21_decimal value_1, s21_decimal value_2,
                               s21_decimal *res);

s21_decimal s21_decimal_set_exp(s21_decimal decimal, unsigned int exp);

s21_decimal s21_decimal_invert(s21_decimal decimal);

s21_decimal s21_round_banking(s21_decimal value, s21_decimal drobnay_chast);

void change_sign_if_zero(s21_decimal *value);

int exp_plus(s21_decimal *value_1, int count);
/*----------------------------------------------------------------------*/
