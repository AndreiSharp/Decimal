#include "../include/s21_decimal.h"
#include <check.h>
#include <stdlib.h>
 
// добавляем все тесты для s21_is_equal в один набор
Suite *test_s21_is_equal_suite();

// функция для прогона набора тестов
unsigned int run_suite(Suite *suite, char *file_logs);