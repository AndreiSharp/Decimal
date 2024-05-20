#ifndef S21_ARITH_FUNC
#define S21_ARITH_FUNC

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_comprasion_function.h"
#include "./s21_decimal_function.h"
#include "./s21_decimal_types.h"

/*---------------------------Arithmetic_function-------------------------*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*------------------------Arithmetic_help_function-----------------------*/

bit32_t s21_basic_add(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result);

bit32_t s21_basic_sub(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result);

bit32_t s21_basic_div(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result);

bit32_t s21_basic_mul(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result);

bit32_t s21_decimal_norm(s21_DecData *result);

void s21_normalize(s21_DecData *val_data_1, s21_DecData *val_data_2);

void s21_normalize_base(s21_DecData *val_data_1, s21_DecData *val_data_2);

bit32_t s21_max(bit32_t val_1, bit32_t val_2);

bit32_t s21_count_mul_10(s21_DecData *value, bit32_t count);

bit32_t s21_count_div_10(s21_DecData *value, bit32_t count);

bit32_t s21_mul_10(s21_DecData *value);

s21_DecData s21_div_10(s21_DecData *value);

bit32_t s21_bank_round_data(s21_DecData *num, s21_DecData devider,
                            s21_DecData residue);

bit_t s21_mul_mantis(s21_DecData value_1, s21_DecData value_2,
                     s21_DecData *result);

s21_DecData s21_div_mantis(s21_DecData value_1, s21_DecData value_2,
                           s21_DecData *result);

bit32_t s21_sub_mantis(s21_DecData value_1, s21_DecData value_2,
                       s21_DecData *result);

bit32_t s21_add_mantis(s21_DecData value_1, s21_DecData value_2,
                       s21_DecData *result);

#endif