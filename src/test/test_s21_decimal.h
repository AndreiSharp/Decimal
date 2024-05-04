#include "../include/s21_decimal.h"
#include <check.h>
#include <stdlib.h>

#define COUNT_FUNCTIONS 3 

// добавляем все тесты в один набор
Suite *test_s21_is_equal_suite();
Suite *test_s21_from_decimal_to_int_suite();
Suite *test_s21_from_decimal_to_float_suite();

// функция для прогона набора тестов
unsigned int run_suite(Suite *suite, char *file_logs);
