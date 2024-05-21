#include "../test_s21_decimal.h"

START_TEST(test_s21_round_1) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_2) {
  s21_decimal decimal = {{7778654, 0, 0, 0}};
  s21_decimal decimal_required = {{7778654, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_3) {
  s21_decimal decimal = {{4, 0, 0, 0b00000000000101100000000000000000}};
  s21_decimal decimal_required = {
      {0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_4) {
  s21_decimal decimal = {{2, 0, 0, 0b10000000000000010000000000000000}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_5) {
  s21_decimal decimal = {{74189, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal decimal_required = {
      {74, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_6) {
  s21_decimal decimal = {{61490752, 0b11111111111111111111111111111111, 0,
                          0b00000000000001110000000000000000}};
  s21_decimal decimal_required = {{6, 0b11111111111111111111111111111111, 0,
                                   0b00000000000000000000000000000000}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_7) {
  s21_decimal decimal = {{80000000, 0b11111111111111111111111111111111,
                          0b00000000000000000000000000000011,
                          0b00000000000001110000000000000000}};
  s21_decimal decimal_required = {{8, 0b11111111111111111111111111111111,
                                   0b00000000000000000000000000000011,
                                   0b00000000000000000000000000000000}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_8) {
  s21_decimal decimal = {{27, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal decimal_required = {{2, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_round_9) {
  s21_decimal decimal = {{36, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal decimal_required = {{4, 0, 0, 0}};
  s21_decimal *result;
  int status = s21_round(decimal, result);
  ck_assert_int_eq(s21_is_equal(*result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

Suite *test_s21_round_suite() {
  Suite *suite = suite_create("s21_round");
  TCase *tc_core = tcase_create("core_of_s21_round");

  tcase_add_test(tc_core, test_s21_round_1);
  tcase_add_test(tc_core, test_s21_round_2);
  tcase_add_test(tc_core, test_s21_round_3);
  tcase_add_test(tc_core, test_s21_round_4);
  tcase_add_test(tc_core, test_s21_round_5);
  tcase_add_test(tc_core, test_s21_round_6);
  tcase_add_test(tc_core, test_s21_round_7);
  tcase_add_test(tc_core, test_s21_round_8);
  tcase_add_test(tc_core, test_s21_round_9);

  suite_add_tcase(suite, tc_core);

  return suite;
}
