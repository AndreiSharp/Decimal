#include "test_s21_decimal.h"

unsigned int run_suite(Suite *suite, char *file_logs) {
  // создаем ранер
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

  count_failed_tests +=
      run_suite(test_s21_is_equal_suite(), "test/logs/test_s21_is_equal.log");
  count_failed_tests += run_suite(test_s21_from_decimal_to_int_suite(),
                                  "test/logs/test_s21_from_decimal_to_int.log");

  return count_failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
