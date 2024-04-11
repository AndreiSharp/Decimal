#pragma once

#include "s21_decimal.h"

typedef unsigned int bit;

/*-------------------------Binary function------------------------------*/

// get bit from index in int
bit s21_get_bit(int number, int index);

// set bit on index
int s21_set_bit(int number, int index);

// reset bit on index
int s21_reset_bit(int number, int index);

// get bit from index in s21_decimal
int s21_decimal_is_set_bit(s21_decimal decimal, int index);

// set bit on index in s21_decimal
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index, bit bit);

// find first no zero bit in s21_decimal
int s21_no_zero_bit(s21_decimal decimal);

/*----------------------------------------------------------------------*/