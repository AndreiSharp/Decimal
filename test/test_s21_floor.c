#include "../include/s21_decimal.h"

START_TEST(test_s21_floor_1) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_floor_2) {
  s21_decimal decimal = {{424, 0, 0, 0}};
  s21_decimal decimal_required = {{424, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_floor_3) {
  s21_decimal decimal = {{3, 0, 0, 0b00000000000101100000000000000000}};
  s21_decimal decimal_required = {
      {0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_floor_4) {
  s21_decimal decimal = {{3, 0, 0, 0b10000000000000010000000000000000}};
  s21_decimal decimal_required = {
      {1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_floor_5) {
  s21_decimal decimal = {{95689, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal decimal_required = {
      {95, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_floor_6) {
  s21_decimal decimal = {{95689, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal decimal_required = {
      {96, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

START_TEST(test_s21_floor_7) {
  s21_decimal decimal = {{58490938, 0b11111111111111111111111111111111, 0,
                          0b00000000000001110000000000000000}};
  s21_decimal decimal_required = {{5, 0b11111111111111111111111111111111, 0,
                                   0b00000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}

Suite *test_s21_floor_suite() {
  Suite *suite = suite_create("s21_floor");
  TCase *tc_core = tcase_create("core_of_s21_floor");

  tcase_add_test(tc_core, test_s21_floor_1);
  tcase_add_test(tc_core, test_s21_floor_2);
  tcase_add_test(tc_core, test_s21_floor_3);
  tcase_add_test(tc_core, test_s21_floor_4);
  tcase_add_test(tc_core, test_s21_floor_5);
  tcase_add_test(tc_core, test_s21_floor_6);
  tcase_add_test(tc_core, test_s21_floor_7);

  suite_add_tcase(suite, tc_core);

  return suite;
}
