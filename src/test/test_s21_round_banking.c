#include "test_s21_decimal.h"

START_TEST(test_s21_round_banking_1) {
  s21_decimal decimal = {{48, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal decimal_required = {{4, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_round_banking(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_banking_2) {
  s21_decimal decimal = {{56, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal decimal_required = {{6, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_round_banking(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

Suite *test_s21_round_banking_suite() {
  Suite *suite = suite_create("s21_round_banking");
  TCase *tc_core = tcase_create("core_of_s21_round_banking");

  tcase_add_test(tc_core, test_s21_round_banking_1);
  tcase_add_test(tc_core, test_s21_round_banking_2);

  suite_add_tcase(suite, tc_core);

  return suite;
}
