#include "test_s21_decimal.h"

START_TEST(test_s21_div_1) {
  s21_decimal decimal_first = {{10, 0, 0, 0}};
  s21_decimal decimal_second = {{2, 0, 0, 0}};
  s21_decimal decimal_required = {{5, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_div(decimal_first, decimal_second, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_div_2) {
  s21_decimal decimal_first = {{1, 0, 0, 0}};
  s21_decimal decimal_second = {{10, 0, 0, 0}};
  s21_decimal decimal_required = {{1, 0, 0, 0b10000000000000010000000000000000}};
  s21_decimal *result;
  int status = s21_div(decimal_first, decimal_second, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

Suite *test_s21_div() {
  Suite *suite = suite_create("s21_div");
  TCase *tc_core = tcase_create("core_of_s21_div");

  tcase_add_test(tc_core, test_s21_div_1);
  tcase_add_test(tc_core, test_s21_div_2);

  suite_add_tcase(suite, tc_core);

  return suite;
}
