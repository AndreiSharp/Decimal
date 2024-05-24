#include "s21_test_decimal.h"

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

  // ARITHMETIC_FUNCTIONS
  count_failed_tests +=
      run_suite(test_s21_sub_suite(), "logs/test_s21_sub.log");
  count_failed_tests +=
      run_suite(test_s21_mul_suite(), "logs/test_s21_mul.log");
  count_failed_tests +=
      run_suite(test_s21_add_suite(), "logs/s21_add.log");
  count_failed_tests +=
      run_suite(test_s21_div_suite(), "logs/s21_div.log");

  // COMPARE_FUNCTIONS
  count_failed_tests +=
      run_suite(test_s21_is_equal_suite(), "logs/test_s21_is_equal.log");
  count_failed_tests += run_suite(test_s21_is_not_equal_suite(),
                                  "logs/test_s21_is_not_equal.log");
  count_failed_tests +=
      run_suite(test_s21_is_less_suite(), "logs/test_s21_is_less.log");
  count_failed_tests += run_suite(test_s21_is_less_or_equal_suite(),
                                  "logs/test_s21_is_less_or_equal.log");
  count_failed_tests += run_suite(test_s21_is_greater_suite(),
                                  "logs/test_s21_is_greater.log");
  count_failed_tests +=
      run_suite(test_s21_is_greater_or_equal_suite(),
                "logs/test_s21_is_greater_or_equal.log");

  // CONVERTATION_FUNCTIONS
  count_failed_tests +=
      run_suite(test_s21_from_int_to_decimal_suite(),
                "logs/test_s21_from_int_to_decimal.log");
  count_failed_tests +=
      run_suite(test_s21_from_float_to_decimal_suite(),
                "logs/test_s21_from_float_to_decimal.log");
  count_failed_tests +=
      run_suite(test_s21_from_decimal_to_int_suite(),
                "logs/test_s21_from_decimal_to_int.log");
  count_failed_tests +=
      run_suite(test_s21_from_decimal_to_float_suite(),
                "logs/test_s21_from_decimal_to_float.log");

  // ANOTHER_FUNCTIONS
  count_failed_tests +=
      run_suite(test_s21_round_suite(), "logs/test_s21_round.log");

  count_failed_tests +=
      run_suite(test_s21_floor_suite(), "logs/test_s21_floor.log");
  count_failed_tests +=
      run_suite(test_s21_negate_suite(), "logs/test_s21_negate.log");
  count_failed_tests +=
      run_suite(test_s21_truncate_suite(), "logs/test_s21_truncate.log");
  return count_failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}