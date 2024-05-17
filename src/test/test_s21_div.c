#include "test_s21_decimal.h"

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
  s21_decimal decimal2 = {{5, 0, 0, 0b1000000000000000}};
  s21_decimal decimal3 = {{200, 0, 0, 0}};
  s21_negate(decimal1, &decimal1);
  s21_negate(decimal3, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0b1000000000000000}};
  s21_decimal decimal3 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(-23.678, &decimal1);
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(4.7356, &decimal2);
  s21_decimal decimal3 = {{5, 0, 0, 0}};
  s21_negate(decimal3, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(23.678, &decimal1);
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(4.7356, &decimal2);
  s21_decimal decimal3 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_6) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, max}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(0.5, &decimal2);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_div_7) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, max}};
  s21_decimal decimal2 = {{max, max, max, max}};
  s21_from_float_to_decimal(-0.5, &decimal2);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_div_8) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, max}};
  s21_decimal decimal2 = {{max, max, max, max}};
  s21_from_float_to_decimal(-0.7, &decimal2);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_div_9) {
    int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, max}};
  s21_decimal decimal2 = {{max, max, max, max}};
  s21_from_float_to_decimal(-0.99, &decimal2);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_div_10) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, max}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(0.3, &decimal2);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_div_11) {
    int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, max}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(0.9, &decimal2);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_div_12) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(16.7688, &decimal1);
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(4.658, &decimal2);
  s21_decimal decimal3 = {{0, 0, 0, 0}};
    s21_from_float_to_decimal(3.6, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_13) {
    s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(16.7688, &decimal1);
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(4.658, &decimal2);
  s21_decimal decimal3 = {{0, 0, 0, 0}};
    s21_from_float_to_decimal(3.6, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
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
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
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
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
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
  v

      return suite;
}
