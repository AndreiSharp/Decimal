#include "../s21_test_decimal.h"

START_TEST(test_s21_from_decimal_to_float1) {
  s21_decimal decimal;
  decimal = s21_decimal_null();

  int error_code;
  float result;
  error_code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(error_code, S21_CONV_SUCCESS);
  ck_assert_float_eq(result, 0.0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float2) {
  s21_decimal decimal;
  decimal = s21_decimal_null();
  decimal = s21_decimal_set_bit(decimal, 0, 1);
  decimal = s21_decimal_set_scale(decimal, 3);

  int error_code;
  float result;
  error_code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(error_code, S21_CONV_SUCCESS);
  ck_assert_float_eq(result, 0.001);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float3) {
  s21_decimal decimal;
  decimal = s21_decimal_null();
  decimal = s21_decimal_set_bit(decimal, 0, 1);
  decimal = s21_decimal_set_scale(decimal, 20);

  int error_code;
  float result;
  error_code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(error_code, S21_CONV_SUCCESS);
  ck_assert_float_eq(result, 0.0);
}
END_TEST

Suite *test_s21_from_decimal_to_float_suite() {
  Suite *suite = suite_create("s21_from_decimal_to_float");
  TCase *tc_core = tcase_create("core_of_s21_decimal_to_float");

  tcase_add_test(tc_core, test_s21_from_decimal_to_float1);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float2);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float3);

  suite_add_tcase(suite, tc_core);

  return suite;
}