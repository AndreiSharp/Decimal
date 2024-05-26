#include "../s21_test_decimal.h"

START_TEST(test_s21_negate_1) {
  s21_decimal decimal = {{5, 0, 0, 0}};
  s21_decimal decimal_required = {
      {5, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;
  int status = s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal decimal = {{9898989, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_required = {{9898989, 0, 0, 0}};
  s21_decimal result;
  int status = s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal decimal = {{3, 0, 0, 0b00000000000101100000000000000000}};
  s21_decimal decimal_required = {
      {3, 0, 0, 0b10000000000101100000000000000000}};
  s21_decimal result;
  int status = s21_negate(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

Suite *test_s21_negate_suite() {
  Suite *suite = suite_create("s21_negate");
  TCase *tc_core = tcase_create("core_of_s21_negate");

  tcase_add_test(tc_core, test_s21_negate_1);
  tcase_add_test(tc_core, test_s21_negate_2);
  tcase_add_test(tc_core, test_s21_negate_3);

  suite_add_tcase(suite, tc_core);

  return suite;
}