#include "../include/s21_decimal.h"


s21_decimal s21_decimal_set_exp(s21_decimal decimal, unsigned int exp) {
    for (int i = EXP_POS_L; i <= EXP_POS_R; ++i) {
        s21_decimal_set_bit(decimal, i, s21_get_bit(exp, i - EXP_POS_L));
    }
    return decimal;
}