#include "../s21_test_decimal.h"

START_TEST(test_s21_mul_1) {
  s21_decimal decimal_first = {{3, 0, 0, 0}};
  s21_decimal decimal_second = {{4, 0, 0, 0}};
  s21_decimal decimal_required = {{12, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

// не проходит возвращает в 2 раза больше и положительный результат
START_TEST(test_s21_mul_2) {
  s21_decimal decimal_first = {{30, 0, 0, 0}};
  decimal_first = s21_decimal_set_sign(decimal_first, 1);
  s21_decimal decimal_second = {{20, 0, 0, 0}};
  s21_decimal decimal_required = {{600, 0, 0, 0}};
  decimal_required = s21_decimal_set_sign(decimal_required, 1);
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal decimal_first = {{279, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_second = {
      {37865, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal decimal_required = {{10564335, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal decimal_first = {{0, 0, 0, 0}};
  s21_decimal decimal_second = {{6, 0, 0, 0}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal decimal_first = {{0, 0, 0b11111111111111111111111111111111, 0}};
  s21_decimal decimal_second = {{0, 0, 0b11111111111111111111111111111111, 0}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_mul_6) {
  s21_decimal decimal_first = {{1, 0, 0, 0b00000000000110010000000000000000}};
  s21_decimal decimal_second = {{1, 0, 0, 0b00000000000110010000000000000000}};
  s21_decimal decimal_required = {
      {0, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_7) {
  s21_decimal decimal_first = {
      {53785, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal decimal_second = {{1, 0, 0, 0}};
  s21_decimal decimal_required = {
      {53785, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_8) {
  s21_decimal decimal_first = {
      {8511, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal decimal_second = {
      {324, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal decimal_required = {
      {2757564, 0, 0, 0b00000000000001000000000000000000}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_9) {
  unsigned int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{max, max, max, 0}};
  s21_decimal result;
  int check = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_mul_10) {
  unsigned int max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{max, max, max, 0}};
  s21_negate(decimal2, &decimal2);
  s21_decimal result;
  int check = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_mul_11) {
  s21_decimal decimal_first = {{0, 0, 0, 0}};
  s21_decimal decimal_second = {
      {324, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_12) {
  unsigned int max = 0b11111111111111111111111111111111;
  s21_decimal decimal_first = {{max, max, max, 0}};
  s21_decimal decimal_second = {{max, max, max, 0}};
  s21_decimal decimal_required = {{0, 0, 0, 0}};

  decimal_first = s21_decimal_set_scale(decimal_first, 5);
  decimal_second = s21_decimal_set_scale(decimal_second, 18);
  s21_decimal result;
  int status = s21_mul(decimal_first, decimal_second, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal_required), 1);
  ck_assert_int_eq(status, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_mul_13) {
  s21_decimal a, b;
  a = s21_decimal_null();
  b = s21_decimal_null();
  a = s21_decimal_invert(a, SIZE_MANTIS);
  b = s21_decimal_invert(b, SIZE_MANTIS);
  a = s21_decimal_set_scale(a, 20);
  b = s21_decimal_set_scale(b, 20);

  s21_decimal result;
  int error_code = s21_mul(a, b, &result);
  for (int i = 0; i < COUNT_BLOCKS - 1; ++i) {
    ck_assert_int_eq(result.bits[i], 0);
  }
  ck_assert_int_eq(error_code, S21_SUCCES);
}
END_TEST

Suite *test_s21_mul_suite() {
  Suite *suite = suite_create("s21_mul");
  TCase *tc_core = tcase_create("core_of_s21_mul");

  tcase_add_test(tc_core, test_s21_mul_1);
  tcase_add_test(tc_core, test_s21_mul_2);
  tcase_add_test(tc_core, test_s21_mul_3);
  tcase_add_test(tc_core, test_s21_mul_4);
  tcase_add_test(tc_core, test_s21_mul_5);
  tcase_add_test(tc_core, test_s21_mul_6);
  tcase_add_test(tc_core, test_s21_mul_7);
  tcase_add_test(tc_core, test_s21_mul_8);
  tcase_add_test(tc_core, test_s21_mul_9);
  tcase_add_test(tc_core, test_s21_mul_10);
  tcase_add_test(tc_core, test_s21_mul_11);
  tcase_add_test(tc_core, test_s21_mul_12);
  tcase_add_test(tc_core, test_s21_mul_13);

  suite_add_tcase(suite, tc_core);
  return suite;
}
