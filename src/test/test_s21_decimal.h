#include "../include/s21_decimal.h"
#include <check.h>
#include <stdlib.h>

// добавляем все тесты для s21_is_equal в один набор
// COMPARE_FUNCTIONS
Suite *test_s21_is_equal_suite();
Suite *test_s21_is_not_equal_suite();
Suite *test_s21_is_less_suite();
Suite *test_s21_is_less_or_equal_suite();
Suite *test_s21_is_greater_suite();
Suite *test_s21_is_greater_or_equal_suite();
// ANOUTHER_FUNCTION
Suite *test_s21_from_int_to_decimal_suite();

// функция для прогона набора тестов
unsigned int run_suite(Suite *suite, char *file_logs);