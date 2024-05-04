#include "test_s21_decimal.h"

START_TEST(test_s21_from_int_to_decimal_1) {
  // тест 1
  s21_decimal dst;
  int src;


  int result_s21_from_int_to_decimal = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result_s21_from_int_to_decimal, S21_TRUE);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_2) {
  // тест 2
  s21_decimal dst;
  int src;

  int result_s21_from_int_to_decimal = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result_s21_from_int_to_decimal, S21_TRUE);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_3) {
  // тест 3
  s21_decimal dst;
  int src;

  int result_s21_from_int_to_decimal = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result_s21_from_int_to_decimal, S21_TRUE);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_4) {
  // тест 4
  s21_decimal dst;
  int src;

  int result_s21_from_int_to_decimal = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result_s21_from_int_to_decimal, S21_TRUE);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_5) {
  // тест 5
  s21_decimal dst;
  int src;

  int result_s21_from_int_to_decimal = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result_s21_from_int_to_decimal, S21_TRUE);
}
END_TEST

Suite *test_s21_from_int_to_decimal_suite() {
  // создаем новый набор для тестов функции
  Suite *suite = suite_create("s21_from_int_to_decimal");
  TCase *tc_core = tcase_create("core_of_s21_from_int_to_decimal");

  // каждый тест добавляем
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_1);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_2);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_3);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_4);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_5);
  // тест кейс добавляем в suite
  suite_add_tcase(suite, tc_core);
  return suite;
}
