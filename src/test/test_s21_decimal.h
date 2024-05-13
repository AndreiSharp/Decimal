#include "../include/s21_decimal.h"
#include <check.h>
#include <stdlib.h>
 
// добавляем все тесты в один набор
Suite *test_s21_is_equal_suite();
Suite *test_s21_from_decimal_to_int_suite();
Suite *test_s21_truncate_suite();
Suite *test_s21_negate_suite();
Suite *test_s21_floor_suite();
Suite *test_s21_round_suite();
Suite *test_s21_round_banking_suite();

// функция для прогона набора тестов
unsigned int run_suite(Suite *suite, char *file_logs);
