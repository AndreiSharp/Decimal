#include "test_s21_decimal.h"

START_TEST(test_s21_truncate_1) {
  s21_decimal decimal = {{0, 0, 0, 95689.73}};
  s21_decimal decimal_required = {{0, 0, 0, 95689}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

Suite *test_s21_truncate_suite() {
  Suite *suite = suite_create("s21_truncate");
  TCase *tc_core = tcase_create("core_of_s21_truncate");

  tcase_add_test(tc_core, test_s21_truncate_1);

  suite_add_tcase(suite, tc_core);

  return suite;
}
