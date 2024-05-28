#include "../s21_test_decimal.h"

START_TEST(test_s21_from_float_to_decimal_1) {
  // тест 1
  s21_decimal dst;
  float src = 0.0;
  s21_decimal decimal = {{0, 0, 0, 0}};
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_2) {
  // тест 2
  s21_decimal dst;
  float src = -0.0;
  s21_decimal decimal = {{0, 0, 0, 0}};
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_3) {
  // тест 3
  s21_decimal dst;
  float src = -5.5;
  s21_decimal decimal = {{55, 0, 0, 0b10000000000000000}};
  s21_negate(decimal, &decimal);
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_4) {
  // тест 4

  float src = -678.678;
  s21_decimal decimal = s21_decimal_null();
  decimal.bits[0] = 678678;
  decimal = s21_decimal_set_scale(decimal, 3);
  s21_negate(decimal, &decimal);

  s21_decimal result;
  int error_code = s21_from_float_to_decimal(src, &result);

  ck_assert_int_eq(error_code, S21_CONV_SUCCESS);

  ck_assert_int_eq(s21_is_equal(result, decimal), 1);

  int sign1 = s21_decimal_get_sign(result);
  int sign2 = s21_decimal_get_sign(decimal);

  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_5) {
  // тест 5
  s21_decimal dst;
  float src = -5.678786;
  s21_decimal decimal = {{5678786, 0, 0, 0}};
  decimal = s21_decimal_set_scale(decimal, 6);
  s21_negate(decimal, &decimal);
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_6) {
  // тест 6
  s21_decimal dst;
  float src = -324134.5;
  s21_decimal decimal = {{3241345, 0, 0, 0b10000000000000000}};
  s21_negate(decimal, &decimal);
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_7) {
  // тест 7
  s21_decimal dst;
  float src = -123134.6;
  s21_decimal decimal = {{1231346, 0, 0, 0b10000000000000000}};
  s21_negate(decimal, &decimal);
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_8) {
  // тест 8
  s21_decimal dst;
  float src = 123134.6;
  s21_decimal decimal = {{1231346, 0, 0, 0b10000000000000000}};
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_9) {
  // тест 9
  s21_decimal dst;
  float src = 4325.632;
  s21_decimal decimal = {{4325632, 0, 0, 0b110000000000000000}};
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_10) {
  // тест 10
  s21_decimal dst;
  float src = -4325.632;
  s21_decimal decimal = {{4325632, 0, 0, 0b110000000000000000}};
  s21_negate(decimal, &decimal);
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_SUCCESS);
  ck_assert_int_eq(s21_is_equal(dst, decimal), 1);
  int sign1 = s21_decimal_get_sign(dst);
  int sign2 = s21_decimal_get_sign(decimal);
  ck_assert_int_eq(sign1, sign2);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_11) {
  // тест 11
  s21_decimal dst;
  float src = INFINITY;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_12) {
  // тест 12
  s21_decimal dst;
  float src = -INFINITY;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_13) {
  // тест 13
  s21_decimal dst;
  float src = NAN;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_14) {
  // тест 14
  s21_decimal dst;
  float src = -NAN;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_15) {
  // тест 15
  s21_decimal dst;
  float src = 2658455991569831745807614120560689152.f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_16) {
  // тест 16
  s21_decimal dst;
  float src = 158456315583795709447797473280.0f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_17) {
  // тест 17
  s21_decimal dst;
  float src = 79228181403730269072124805120.f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_18) {
  // тест 18
  s21_decimal dst;
  float src =
      0.00000000000000000000000000009999998226151445646676901231373326364778153626990814f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_19) {
  // тест 19
  s21_decimal dst;
  float src =
      4.8148245739821641389174087312824996385704304343408247917894169330688125540973487659357488E-35f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_20) {
  // тест 20
  s21_decimal dst;
  float src =
      1.2621774483536188886587657044524579674771302961744368076324462890625E-29f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

Suite *test_s21_from_float_to_decimal_suite() {
  // создаем новый набор для тестов функции
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *tc_core = tcase_create("core_of_s21_from_float_to_decimal");

  // каждый тест добавляем
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_1);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_2);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_3);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_4);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_5);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_6);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_7);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_8);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_9);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_10);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_11);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_12);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_13);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_14);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_15);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_16);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_17);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_18);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_19);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_20);
  // тест кейс добавляем в suite
  suite_add_tcase(suite, tc_core);
  return suite;
}
