#include "../test_s21_decimal.h"

START_TEST(test_s21_is_greater_1) {
  // тест 1
  s21_decimal decimal_1, decimal_2;
  s21_decimal_init(&decimal_1);
  s21_decimal_init(&decimal_2);

  int result_s21_is_greater = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_greater, S21_FALSE);
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  // тест 2
  s21_decimal decimal_1, decimal_2;
  s21_decimal_init(&decimal_1);
  s21_decimal_init(&decimal_2);
  decimal_1 = s21_decimal_set_bit(decimal_1, 10, 1);

  int result_s21_is_greater = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_greater, S21_TRUE);
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  // тест 3
  s21_decimal decimal_1, decimal_2;
  s21_decimal_init(&decimal_1);
  s21_decimal_init(&decimal_2);
  decimal_1 = s21_decimal_set_bit(decimal_1, 127, 1);

  int result_s21_is_greater = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_greater, S21_FALSE);
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  // тест 4
  s21_decimal decimal_1, decimal_2;
  s21_decimal_init(&decimal_1);
  s21_decimal_init(&decimal_2);
  decimal_1 = s21_decimal_set_bit(decimal_1, 0, 1);

  int result_s21_is_greater = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_greater, S21_TRUE);
}
END_TEST

START_TEST(test_s21_is_greater_5) {
  // тест 5
  s21_decimal decimal_1, decimal_2;
  s21_decimal_init(&decimal_1);
  s21_decimal_init(&decimal_2);
  decimal_1 = s21_decimal_set_bit(decimal_1, 9, 1);
  decimal_2 = s21_decimal_set_bit(decimal_2, 10, 1);
  decimal_2 = s21_decimal_set_bit(decimal_2, 127, 1);

  int result_s21_is_greater = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_greater, S21_TRUE);
}
END_TEST

Suite *test_s21_is_greater_suite() {
  // создаем новый набор для тестов функции
  Suite *suite = suite_create("s21_is_greater");
  TCase *tc_core = tcase_create("core_of_s21_is_greater");

  // каждый тест добавляем
  tcase_add_test(tc_core, test_s21_is_greater_1);
  tcase_add_test(tc_core, test_s21_is_greater_2);
  tcase_add_test(tc_core, test_s21_is_greater_3);
  tcase_add_test(tc_core, test_s21_is_greater_4);
  tcase_add_test(tc_core, test_s21_is_greater_5);
  // тест кейс добавляем в suite
  suite_add_tcase(suite, tc_core);
  return suite;
}