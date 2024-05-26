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
#if TEST_ADD
  count_failed_tests +=
      run_suite(test_s21_add_suite(), "logs/1_Arithmetic/test_s21_add.log");
#endif

#if TEST_SUB
  count_failed_tests +=
      run_suite(test_s21_sub_suite(), "logs/1_Arithmetic/test_s21_sub.log");
#endif

#if TEST_MUL
  count_failed_tests +=
      run_suite(test_s21_mul_suite(), "logs/1_Arithmetic/test_s21_mul.log");
#endif

#if TEST_DIV
  count_failed_tests +=
      run_suite(test_s21_div_suite(), "logs/1_Arithmetic/test_s21_div.log");
#endif

  // COMPARE_FUNCTIONS
#if TEST_IS_EQUAL
  count_failed_tests += run_suite(test_s21_is_equal_suite(),
                                  "logs/2_Compare/test_s21_is_equal.log");
#endif

#if TEST_IS_NOT_EQUAL
  count_failed_tests += run_suite(test_s21_is_not_equal_suite(),
                                  "logs/2_Compare/test_s21_is_not_equal.log");
#endif

#if TEST_IS_LESS
  count_failed_tests += run_suite(test_s21_is_less_suite(),
                                  "logs/2_Compare/test_s21_is_less.log");
#endif

#if TEST_IS_LESS_OR_EQUAL
  count_failed_tests +=
      run_suite(test_s21_is_less_or_equal_suite(),
                "logs/2_Compare/test_s21_is_less_or_equal.log");
#endif

#if TEST_IS_GREATER
  count_failed_tests += run_suite(test_s21_is_greater_suite(),
                                  "logs/2_Compare/test_s21_is_greater.log");
#endif

#if TEST_IS_GREATER_OR_EQUAL
  count_failed_tests +=
      run_suite(test_s21_is_greater_or_equal_suite(),
                "logs/2_Compare/test_s21_is_greater_or_equal.log");
#endif

  // CONVERTATION_FUNCTIONS
#if TEST_FROM_INT_TO_DECIMAL
  count_failed_tests +=
      run_suite(test_s21_from_int_to_decimal_suite(),
                "logs/3_Convertation/test_s21_from_int_to_decimal.log");
#endif

#if TEST_FROM_FLOAT_TO_DECIMAL
  count_failed_tests +=
      run_suite(test_s21_from_float_to_decimal_suite(),
                "logs/3_Convertation/test_s21_from_float_to_decimal.log");
#endif

#if TEST_FROM_DECIMAL_TO_INT
  count_failed_tests +=
      run_suite(test_s21_from_decimal_to_int_suite(),
                "logs/3_Convertation/test_s21_from_decimal_to_int.log");
#endif

#if TEST_FROM_DECIMAL_TO_FLOAT
  count_failed_tests +=
      run_suite(test_s21_from_decimal_to_float_suite(),
                "logs/3_Convertation/test_s21_from_decimal_to_float.log");
#endif

  // ANOTHER_FUNCTIONS
#if TEST_ROUND
  count_failed_tests +=
      run_suite(test_s21_round_suite(), "logs/4_Anouther/test_s21_round.log");
#endif

#if TEST_FLOOR
  count_failed_tests +=
      run_suite(test_s21_floor_suite(), "logs/4_Anouther/test_s21_floor.log");
#endif

#if TEST_NEGATE
  count_failed_tests +=
      run_suite(test_s21_negate_suite(), "logs/4_Anouther/test_s21_negate.log");
#endif

#if TEST_TRUNCATE
  count_failed_tests += run_suite(test_s21_truncate_suite(),
                                  "logs/4_Anouther/test_s21_truncate.log");
#endif

  return count_failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}