#include "../include/s21_decimal.h"

// unsigned int run_suite(Suite *suite, char *file_logs) {
//   // создаем раней
//   SRunner *srunner = srunner_create(suite);

//   // результаты записываем в файл
//   srunner_set_log(srunner, file_logs);
//   srunner_run_all(srunner, CK_ENV);
//   // кол-во зафейленых тестов
//   int count_failed_tests = srunner_ntests_failed(srunner);

//   // освобождаем память которая была определена для ранера
//   srunner_free(srunner);

//   return count_failed_tests;
// }

// int main() {
//   int count_failed_tests = 0;

//   // ARITHMETIC_FUNCTIONS
//   count_failed_tests +=
//       run_suite(test_s21_sub_suite(), "test/logs/test_s21_sub.log");
//   count_failed_tests +=
//       run_suite(test_s21_mul_suite(), "test/logs/test_s21_mul.log");
//   count_failed_tests +=
//       run_suite(test_s21_add_suite(), "test/logs/s21_add.log");
//   count_failed_tests +=
//       run_suite(test_s21_div_suite(), "test/logs/s21_div.log");

//   // COMPARE_FUNCTIONS
//   count_failed_tests +=
//       run_suite(test_s21_is_equal_suite(), "test/logs/test_s21_is_equal.log");
//   count_failed_tests += run_suite(test_s21_is_not_equal_suite(),
//                                   "test/logs/test_s21_is_not_equal.log");
//   count_failed_tests +=
//       run_suite(test_s21_is_less_suite(), "test/logs/test_s21_is_less.log");
//   count_failed_tests += run_suite(test_s21_is_less_or_equal_suite(),
//                                   "test/logs/test_s21_is_less_or_equal.log");
//   count_failed_tests += run_suite(test_s21_is_greater_suite(),
//                                   "test/logs/test_s21_is_greater.log");
//   count_failed_tests += run_suite(test_s21_is_greater_or_equal_suite(),
//                                   "test/logs/test_s21_is_greater_or_equal.log");

//   // CONVERTATION_FUNCTIONS
//   count_failed_tests += run_suite(test_s21_from_int_to_decimal_suite(),
//                                   "test/logs/test_s21_from_int_to_decimal.log");
//   count_failed_tests +=
//       run_suite(test_s21_from_float_to_decimal_suite(),
//                 "test/logs/test_s21_from_float_to_decimal.log");
//   count_failed_tests +=
//       run_suite(test_s21_from_decimal_to_int_suite(),
//                 "./test/logs/test_s21_from_decimal_to_int.log");
//   count_failed_tests +=
//       run_suite(test_s21_from_decimal_to_float_suite(),
//                 "./test/logs/test_s21_from_decimal_to_float.log");

//   // ANOTHER_FUNCTIONS
//   count_failed_tests +=
//       run_suite(test_s21_round_suite(), "test/logs/test_s21_round.log");
//   count_failed_tests +=
//       run_suite(test_s21_floor_suite(), "test/logs/test_s21_floor.log");
//   count_failed_tests +=
//       run_suite(test_s21_negate_suite(), "test/logs/test_s21_negate.log");
//   count_failed_tests +=
//       run_suite(test_s21_truncate_suite(), "test/logs/test_s21_truncate.log");
//   return count_failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
// }

void run_tests(void) {
  Suite *list_cases[] = {test_s21_sub_suite(),
// test_s21_mul_suite(),
test_s21_add_suite(),
test_s21_div_suite(),

// COMPARE_FUNCTIONS
test_s21_is_equal_suite(),
test_s21_is_not_equal_suite(),
test_s21_is_less_suite(),
test_s21_is_less_or_equal_suite(),
test_s21_is_greater_suite(),
test_s21_is_greater_or_equal_suite(),

// CONVERTATION_FUNCTIONS
test_s21_from_int_to_decimal_suite(),
// test_s21_from_float_to_decimal_suite(),
test_s21_from_decimal_to_int_suite(),
test_s21_from_decimal_to_float_suite(),

// ANOTHER_FUNCTIONS
test_s21_round_suite(),
test_s21_floor_suite(),
test_s21_negate_suite(),
test_s21_truncate_suite(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
  // sleep(1);
}

int main(void) {
  run_tests();
  return 0;
}