#include "test_s21_decimal.h"

START_TEST(test_s21_sub_1) {
  // тест 1
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_decimal decimal3 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_2) {
  // тест 2
  s21_decimal decimal1 = {{1, 0, 0, 0}};
  s21_decimal decimal2 = {{2, 0, 0, 0}};
  s21_decimal decimal3 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal3, &decimal3);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_3) {
  // тест 3
  s21_decimal decimal1 = {{55, 0, 0, 0}};
  s21_decimal decimal2 = {{100, 0, 0, 0}};
  s21_decimal decimal3 = {{45, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal3, &decimal3);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_4) {
  // тест 4
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal2 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal3 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_5) {
  // тест 5
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal2 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal3 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal1, &decimal1);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_sub_6) {
  // тест 6
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal2 = {{2147483647, 2147483647, 2147483647, 89678}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_ERROR);
}
END_TEST

START_TEST(test_s21_sub_7) {
  // тест 7
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{2147483648, 2147483647, 2147483647, 1}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_ERROR);
}
END_TEST

START_TEST(test_s21_sub_8) {
  // тест 8
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_decimal decimal3 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_9) {
  // тест 9
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal2 = {{100, 0, 0, 0}};
  s21_decimal decimal3 = {{2147483647, 2147483647, 2147483547, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_10) {
  // тест 10
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483547, 0}};
  s21_decimal decimal2 = {{100, 0, 0, 0}};
  s21_decimal decimal3 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal1, &decimal1);
  s21_negate(decimal3, &decimal3);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_11) {
  // тест 11
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483548, 0}};
  s21_decimal decimal2 = {{100, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal1, &decimal1);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_sub_12) {
  // тест 12
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483548, 0}};
  s21_decimal decimal2 = {{100, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal2, &decimal2);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_sub_13) {
  // тест 13
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal decimal2 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal2, &decimal2);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_sub_14) {
  // тест 14
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483547, 0}};
  s21_decimal decimal2 = {{2147483647, 2147483647, 0, 0}};
  s21_decimal decimal3 = {{2147483647, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_15) {
  // тест 15
  s21_decimal decimal1 = {{2147483647, 2147483647, 2147483547, 0}};
  s21_decimal decimal2 = {{2147483647, 0, 0, 0}};
  s21_decimal decimal3 = {{2147483647, 2147483647, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_16) {
  // тест 16
  s21_decimal decimal1 = {{100, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0b1000000000000000}};
  s21_decimal decimal3 = {{995, 0, 0, 0b1000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_17) {
  // тест 17
  s21_decimal decimal1 = {{1, 0, 0, 0b11000000000000000}};
  s21_decimal decimal2 = {{5, 0, 0, 0b1000000000000000}};
  s21_decimal decimal3 = {{49, 0, 0, 0b10000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal3, &decimal3);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_18) {
  // тест 18
  s21_decimal decimal1 = {{5, 0, 0, 0b1000000000000000}};
  s21_decimal decimal2 = {{5, 0, 0, 0b1000000000000000}};
  s21_decimal decimal3 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal2, &decimal2);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_19) {
  // тест 19
  s21_decimal decimal1 = {{99, 0, 0, 0b1000000000000000}};
  s21_decimal decimal2 = {{5, 0, 0, 0b1000000000000000}};
  s21_decimal decimal3 = {{104, 0, 0, 0b1000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal2, &decimal2);
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_sub_20) {
  // тест 20
  s21_decimal decimal1 = {{153, 0, 0, 0b1000000000000000}};
  s21_decimal decimal2 = {{25, 0, 0, 0b1000000000000000}};
  s21_decimal decimal3 = {{128, 0, 0, 0b1000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
  int sign1 = s21_decimal_sign(decimal3);
  int sign2 = s21_decimal_sign(result);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

Suite *test_s21_sub_suite() {
  // создаем новый набор для тестов функции
  Suite *suite = suite_create("test_s21_sub");
  TCase *tc_core = tcase_create("core_of_s21_sub");

  // каждый тест добавляем
  tcase_add_test(tc_core, test_s21_sub_1);
  tcase_add_test(tc_core, test_s21_sub_2);
  tcase_add_test(tc_core, test_s21_sub_3);
  tcase_add_test(tc_core, test_s21_sub_4);
  tcase_add_test(tc_core, test_s21_sub_5);
  tcase_add_test(tc_core, test_s21_sub_6);
  tcase_add_test(tc_core, test_s21_sub_7);
  tcase_add_test(tc_core, test_s21_sub_8);
  tcase_add_test(tc_core, test_s21_sub_9);
  tcase_add_test(tc_core, test_s21_sub_10);
  tcase_add_test(tc_core, test_s21_sub_11);
  tcase_add_test(tc_core, test_s21_sub_12);
  tcase_add_test(tc_core, test_s21_sub_13);
  tcase_add_test(tc_core, test_s21_sub_14);
  tcase_add_test(tc_core, test_s21_sub_15);
  tcase_add_test(tc_core, test_s21_sub_16);
  tcase_add_test(tc_core, test_s21_sub_17);
  tcase_add_test(tc_core, test_s21_sub_18);
  tcase_add_test(tc_core, test_s21_sub_19);
  tcase_add_test(tc_core, test_s21_sub_20);

  // тест кейс добавляем в suite
  suite_add_tcase(suite, tc_core);
  return suite;
}
