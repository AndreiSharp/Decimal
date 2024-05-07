#include "test_s21_decimal.h"

START_TEST(test_s21_truncate_1) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_truncate_2) {
  s21_decimal decimal = {{27, 0, 0, 0}};
  s21_decimal decimal_required = {{27, 0, 0, 0}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_truncate_3) {
  s21_decimal decimal = {{27, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_required = {{27, 0, 0, 0b10000000000000000000000000000000}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_truncate_4) {
  s21_decimal decimal = {{9568973, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal decimal_required = {{95689, 0, 0, 0}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_truncate_5) {
  s21_decimal decimal = {{9568973, 0, 0, 0b10000000000000100000000000000000}};
  s21_decimal decimal_required = {{95689, 0, 0, 0b10000000000000000000000000000000}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_truncate_6) {
  s21_decimal decimal = {{3, 0, 0, 0b00000000000101100000000000000000}};
  s21_decimal decimal_required = {{0, 0, 0, 0b00000000000000000000000000000000}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_truncate_7) {
  s21_decimal decimal = {{3, 0, 0, 0b10000000000101100000000000000000}};
  s21_decimal decimal_required = {{0, 0, 0, 0b00000000000000000000000000000000}};  
  s21_decimal *result;
  int status = s21_truncate(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

Suite *test_s21_truncate_suite() {
  Suite *suite = suite_create("s21_truncate");
  TCase *tc_core = tcase_create("core_of_s21_truncate");

  tcase_add_test(tc_core, test_s21_truncate_1);
  tcase_add_test(tc_core, test_s21_truncate_2);
  tcase_add_test(tc_core, test_s21_truncate_3);
  tcase_add_test(tc_core, test_s21_truncate_4);
  tcase_add_test(tc_core, test_s21_truncate_5);
  tcase_add_test(tc_core, test_s21_truncate_6);
  tcase_add_test(tc_core, test_s21_truncate_7);

  suite_add_tcase(suite, tc_core);

  return suite;
}
