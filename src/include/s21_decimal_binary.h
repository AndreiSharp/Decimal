#pragma once

#include "s21_decimal_types.h"

#define BIN_ZERO 0b00000000000000000000000000000000

/*-------------------------Binary function------------------------------*/

// get bit from index in int
bit_t s21_get_bit(int number, int index);

// set bit on index
int s21_set_bit(int number, int index);

// reset bit on index
int s21_reset_bit(int number, int index);

// get bit from index in s21_decimal
bit_t s21_decimal_is_set_bit(s21_decimal decimal, int index);

// set bit on index in s21_decimal
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index, bit_t bit);

// find first no zero bit in s21_decimal
int s21_no_zero_bit(s21_decimal decimal);

/*----------------------------------------------------------------------*/
