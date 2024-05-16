#include "test_s21_decimal.h"
s21_from_float_to_decimal(src, &dst);
s21_from_int_to_decimal(src, &dst);

enum s21_arithmetic_result {
  S21_SUCCES = 0,      // OK
  S21_TOO_LARGE = 1,   // The number is too large or equal to infinity
  S21_TOO_SMALL = 2,   // The number is too small or equal to negative infinity
  S21_DEV_BY_ZERO = 3, // Division by 0
  S21_ERROR = 4        // Another Error
};

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
  int check = s21_sub(decimal1, decimal2, &result);
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
  s21_negate(decimal1, &decimal1);
  s21_negate(decimal3, &decimal3);
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_div_4) {}
END_TEST

START_TEST(test_s21_div_5) {}
END_TEST

START_TEST(test_s21_div_6) {}
END_TEST

START_TEST(test_s21_div_7) {}
END_TEST

START_TEST(test_s21_div_8) {}
END_TEST

START_TEST(test_s21_div_9) {}
END_TEST

START_TEST(test_s21_div_10) {}
END_TEST

START_TEST(test_s21_div_11) {}
END_TEST

START_TEST(test_s21_div_12) {}
END_TEST

START_TEST(test_s21_div_13) {}
END_TEST

START_TEST(test_s21_div_14) {}
END_TEST

START_TEST(test_s21_div_15) {}
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
