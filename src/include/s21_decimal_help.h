#pragma once

#include "s21_decimal_binary.h"

#define BIN_ZERO 0b00000000000000000000000000000000

/*-------------------------Helper function------------------------------*/

// get sign of s21_decimal
int s21_decimal_sign(s21_decimal decimal);

// get absolutely value of s21_decimal
s21_decimal s21_decimal_abs(s21_decimal decimal);

// get exponent value of s21_decimal
int s21_decimal_exp(s21_decimal decimal);

// multiplicate s21_decimal by 10
s21_decimal s21_decimal_mul_10(s21_decimal decimal);

// divides s21_decimal by 10
s21_decimal s21_decimal_div_10(s21_decimal decimal);

// copy decimal from src to dest
s21_decimal s21_decimal_copy(s21_decimal src, s21_decimal *dest);

bit_t s21_decimal_get_bit(s21_decimal decimal, int index);

s21_decimal s21_decimal_init(s21_decimal *decimal);

/*----------------------------------------------------------------------*/