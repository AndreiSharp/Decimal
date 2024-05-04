#include "test_s21_decimal.h"

unsigned int run_suite(Suite *suite, char *file_logs) {
  // создаем раней
  SRunner *srunner = srunner_create(suite);

  // результаты записываем в файл
  srunner_set_log(srunner, file_logs);
  srunner_run_all(srunner, CK_ENV);
  // кол-во зафейленых тестов
  int count_failed_tests = srunner_ntests_failed(srunner);

  // освобождаем память которая была определена для ранера
  srunner_free(srunner);

  return count_failed_tests;
}

int main() {
  int count_failed_tests = 0;
// COMPARE_FUNCTIONS
  count_failed_tests +=
      run_suite(test_s21_is_equal_suite(), "test/logs/test_s21_is_equal.log");
  count_failed_tests +=
      run_suite(test_s21_is_not_equal_suite(), "test/logs/test_s21_is_not_equal.log");
  count_failed_tests +=
      run_suite(test_s21_is_less_suite(), "test/logs/test_s21_is_less.log");
  count_failed_tests +=
      run_suite(test_s21_is_less_or_equal_suite(), "test/logs/test_s21_is_less_or_equal.log");
  count_failed_tests +=
      run_suite(test_s21_is_greater_suite(), "test/logs/test_s21_is_greater.log");
  count_failed_tests +=
      run_suite(test_s21_is_greater_or_equal_suite(), "test/logs/test_s21_is_greater_or_equal.log");
// ANOUTHER_FUNCTION
  count_failed_tests +=
      run_suite(test_s21_from_int_to_decimal_suite(), "test/logs/test_s21_from_int_to_decimal.log");
  return count_failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}