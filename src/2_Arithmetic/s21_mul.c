#include "../include/s21_decimal.h"

// Multiplication
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (s21_get_bit(value_1.bits[3], 31) == s21_get_bit(value_2.bits[3], 31)) {
        s21_decimal_set_bit(*result, 127, 0);
    } else {
        s21_decimal_set_bit(*result, 127, 1);
    }



    
}