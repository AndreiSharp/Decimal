#include "../s21_test_decimal.h"

START_TEST(test_s21_div_1) {
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_DEV_BY_ZERO);
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal decimal1 = {{100, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0b10000000000000000}};
  s21_decimal decimal3 = {{200, 0, 0, 0}};
  s21_negate(decimal1, &decimal1);
  s21_negate(decimal3, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0b10000000000000000}};
  s21_decimal decimal3 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal decimal1 = {{0b101110001111110, 0, 0, 0}};
  decimal1 = s21_decimal_set_sign(decimal1, 1);
  decimal1 = s21_decimal_set_scale(decimal1, 3);
  s21_decimal decimal2 = {{47356, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 4);
  s21_decimal decimal3 = {{5, 0, 0, 0}};
  s21_negate(decimal3, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal decimal1 = {{23678, 0, 0, 0}};
  decimal1 = s21_decimal_set_scale(decimal1, 3);
  s21_decimal decimal2 = {{47356, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 4);
  s21_decimal decimal3 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_6) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_div_7) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 1);
  decimal2 = s21_decimal_set_sign(decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_div_8) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{7, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 1);
  decimal2 = s21_decimal_set_sign(decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_div_9) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{99, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 2);
  decimal2 = s21_decimal_set_sign(decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_div_10) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{3, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_div_11) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{9, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_div_12) {
  s21_decimal decimal1 = {{167688, 0, 0, 0}};
  decimal1 = s21_decimal_set_scale(decimal1, 4);
  s21_decimal decimal2 = {{4658, 0, 0, 0}};
  decimal2 = s21_decimal_set_scale(decimal2, 3);
  s21_decimal decimal3 = {{36, 0, 0, 0}};
  decimal3 = s21_decimal_set_scale(decimal3, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_13) {
  s21_decimal decimal1 = {{167688, 0, 0, 0}};
  decimal1 = s21_decimal_set_scale(decimal1, 4);
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(4.658, &decimal2);
  s21_decimal decimal3 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(3.6, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_14) {
  int max = 0b11111111111111111111111111111111;
  int max1 = 0b11111111111111111111111111111110;
  int max2 = 0b01111111111111111111111111111111;
  s21_decimal decimal1 = {{max1, max, max, 0}};
  s21_decimal decimal2 = {{2, 0, 0, 0}};
  s21_decimal decimal3 = {{max, max, max2, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_15) {
  int max = 0b11111111111111111111111111111111;
  int max1 = 0b11111111111111111111111111111110;
  int max2 = 0b01111111111111111111111111111111;
  s21_decimal decimal1 = {{max1, max, max, 0}};
  s21_decimal decimal2 = {{2, 0, 0, 0}};
  s21_decimal decimal3 = {{max, max, max2, 0}};
  s21_negate(decimal1, &decimal1);
  s21_negate(decimal3, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_get_sign(decimal3);
  int sign2 = s21_decimal_get_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

// new tests

START_TEST(test_s21_div_16) {
  s21_decimal decimal_1 = {{35, 0, 0, 0}};
  s21_decimal decimal_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  decimal_1 = s21_decimal_set_scale(decimal_1, 1);
  decimal_2 = s21_decimal_set_scale(decimal_2, 2);
  int return_value = s21_div(decimal_1, decimal_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_div_17) {
  s21_decimal decimal_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal decimal_2 = {{0x2, 0, 0, 0}};
  decimal_2 = s21_decimal_set_sign(decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  check = s21_decimal_set_sign(check, 1);
  int return_value = s21_div(decimal_1, decimal_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_div_18) {
  s21_decimal decimal_1 = {{10, 0, 0, 0}};
  decimal_1 = s21_decimal_set_sign(decimal_1, 1);
  s21_decimal decimal_2 = {{8, 0, 0, 0}};
  decimal_2 = s21_decimal_set_sign(decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{125, 0, 0, 0}};
  check = s21_decimal_set_scale(check, 2);
  int return_value = s21_div(decimal_1, decimal_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_div_19) {
  s21_decimal decimal_1 = {{15, 0, 0, 0}};
  decimal_1 = s21_decimal_set_sign(decimal_1, 1);
  s21_decimal decimal_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(decimal_1, decimal_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, S21_DEV_BY_ZERO);
}
END_TEST

START_TEST(test_s21_div_20) {
  s21_decimal decimal_1 = {{10, 0, 0, 0}};
  s21_decimal decimal_2 = {{1, 0, 0, 0}};
  decimal_2 = s21_decimal_set_scale(decimal_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(decimal_1, decimal_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, S21_SUCCES);
}
END_TEST

Suite *test_s21_div_suite() {
  Suite *suite = suite_create("s21_div");
  TCase *tc_core = tcase_create("core_of_s21_div");

  tcase_add_test(tc_core, test_s21_div_1);
  tcase_add_test(tc_core, test_s21_div_2);
  tcase_add_test(tc_core, test_s21_div_3);
  tcase_add_test(tc_core, test_s21_div_4);
  tcase_add_test(tc_core, test_s21_div_5);
  tcase_add_test(tc_core, test_s21_div_6);
  tcase_add_test(tc_core, test_s21_div_7);
  tcase_add_test(tc_core, test_s21_div_8);
  tcase_add_test(tc_core, test_s21_div_8);
  tcase_add_test(tc_core, test_s21_div_9);
  tcase_add_test(tc_core, test_s21_div_10);
  tcase_add_test(tc_core, test_s21_div_11);
  tcase_add_test(tc_core, test_s21_div_12);
  tcase_add_test(tc_core, test_s21_div_13);
  tcase_add_test(tc_core, test_s21_div_14);
  tcase_add_test(tc_core, test_s21_div_15);

  // new

  tcase_add_test(tc_core, test_s21_div_16);
  tcase_add_test(tc_core, test_s21_div_17);
  tcase_add_test(tc_core, test_s21_div_18);
  tcase_add_test(tc_core, test_s21_div_19);
  tcase_add_test(tc_core, test_s21_div_20);

  suite_add_tcase(suite, tc_core);

  return suite;
}
