#include <check.h>
#include <stdlib.h>

#include "./../Headers/s21_decimal.h"

// добавляем все тесты для s21_is_equal в один набор

// ARITHMETIC_FUNCTIONS
Suite *test_s21_sub_suite();
Suite *test_s21_mul_suite();
Suite *test_s21_add_suite();
Suite *test_s21_div_suite();

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
Suite *test_s21_floor_suite();
Suite *test_s21_negate_suite();
Suite *test_s21_truncate_suite();

// функция для прогона набора тестов
unsigned int run_suite(Suite *suite, char *file_logs);

#define TEST_SUB 1                    // so ok +/-
#define TEST_MUL 1                    // so ok +/-
#define TEST_ADD 1                    // ok
#define TEST_DIV 1                    // ok
#define TEST_IS_EQUAL 1               // ok
#define TEST_IS_NOT_EQUAL 1           // ok
#define TEST_IS_LESS 1                // ok
#define TEST_IS_LESS_OR_EQUAL 1       // ok
#define TEST_IS_GREATER 1             // ok
#define TEST_IS_GREATER_OR_EQUAL 1    // ok
#define TEST_FROM_INT_TO_DECIMAL 1    // ok
#define TEST_FROM_FLOAT_TO_DECIMAL 1  // ok
#define TEST_FROM_DECIMAL_TO_INT 1    // ok
#define TEST_FROM_DECIMAL_TO_FLOAT 1  // ok
#define TEST_ROUND 1                  // ok
#define TEST_FLOOR 1                  // ok
#define TEST_NEGATE 1                 // ok
#define TEST_TRUNCATE 1               // ok