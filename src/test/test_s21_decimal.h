#include "../include/s21_decimal.h"
#include <check.h>
#include <stdlib.h>

// добавляем все тесты для s21_is_equal в один набор

// ARITHMETIC_FUNCTIONS
Suite *test_s21_sub_suite();
Suite *test_s21_mul_suite();
Suite *test_s21_add_suite();

// COMPARE_FUNCTIONS
Suite *test_s21_is_equal_suite();
Suite *test_s21_is_not_equal_suite();
Suite *test_s21_is_less_suite();
Suite *test_s21_is_less_or_equal_suite();
Suite *test_s21_is_greater_suite();
Suite *test_s21_is_greater_or_equal_suite();

// CONVERTATION_FUNCTIONS
Suite *test_s21_from_int_to_decimal_suite();
Suite *test_s21_from_float_to_decimal_suite();
Suite *test_s21_from_decimal_to_int_suite();
Suite *test_s21_from_decimal_to_float_suite();

// ANOTHER_FUNCTIONS
Suite *test_s21_round_suite();
Suite *test_s21_round_banking_suite();
Suite *test_s21_floor_suite();
Suite *test_s21_negate_suite();
Suite *test_s21_truncate_suite();

// функция для прогона набора тестов
unsigned int run_suite(Suite *suite, char *file_logs);
