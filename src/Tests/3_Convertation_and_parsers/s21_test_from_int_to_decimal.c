#include "../test_s21_decimal.h"

START_TEST(test_s21_from_int_to_decimal_1) {
  // тест 1
  int src = 5000;
  int result = s21_from_int_to_decimal(src, NULL);

  ck_assert_int_eq(result, S21_FALSE);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_2) {
  // тест 2
  s21_decimal dst;
  int src = 2147483647;
  s21_decimal decimal = {{2147483647, 0, 0, 0}};
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_TRUE);
  ck_assert_int_eq(s21_is_equal(decimal, dst), 1);
  int sign1 = s21_decimal_sign(dst);
  int sign2 = s21_decimal_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_3) {
  // тест 3
  s21_decimal dst;
  int src = -2147483648;
  s21_decimal decimal = {{2147483648, 0, 0, 0}};
  s21_negate(decimal, &decimal);
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_TRUE);
  ck_assert_int_eq(s21_is_equal(decimal, dst), 1);
  int sign1 = s21_decimal_sign(dst);
  int sign2 = s21_decimal_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_4) {
  // тест 4
  s21_decimal dst;
  int src = 5000;
  s21_decimal decimal = {{5000, 0, 0, 0}};
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_TRUE);
  ck_assert_int_eq(s21_is_equal(decimal, dst), 1);
  int sign1 = s21_decimal_sign(dst);
  int sign2 = s21_decimal_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_5) {
  // тест 5
  s21_decimal dst;
  int src = -5000;
  s21_decimal decimal = {{5000, 0, 0, 0}};
  s21_negate(decimal, &decimal);
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_TRUE);
  ck_assert_int_eq(s21_is_equal(decimal, dst), 1);
  int sign1 = s21_decimal_sign(dst);
  int sign2 = s21_decimal_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_6) {
  // тест 6
  s21_decimal dst;
  int src = -56738287;
  s21_decimal decimal = {{56738287, 0, 0, 0}};
  s21_negate(decimal, &decimal);
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_TRUE);
  ck_assert_int_eq(s21_is_equal(decimal, dst), 1);
  int sign1 = s21_decimal_sign(dst);
  int sign2 = s21_decimal_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
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
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_6);
  // тест кейс добавляем в suite
  suite_add_tcase(suite, tc_core);
  return suite;
}