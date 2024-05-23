#include "../s21_test_decimal.h"

START_TEST(test_s21_from_decimal_to_int1) {
  s21_decimal decimal;
  decimal = s21_decimal_null();

  int result, error_code;

  error_code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(error_code, S21_CONV_SUCCESS);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int2) {
  s21_decimal decimal;
  decimal = s21_decimal_null();
  decimal = s21_decimal_set_bit(decimal, 0, 1);

  int result, error_code;

  error_code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(error_code, S21_CONV_SUCCESS);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int3) {
  s21_decimal decimal;
  decimal = s21_decimal_null();
  decimal = s21_decimal_invert(decimal, SIZE_MANTIS);

  int result, error_code;
  error_code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(error_code, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int4) {
  s21_decimal decimal;
  decimal = s21_decimal_null();

  int error_code;
  error_code = s21_from_decimal_to_int(decimal, NULL);
  ck_assert_int_eq(error_code, S21_CONV_ERROR);
}
END_TEST

Suite *test_s21_from_decimal_to_int_suite() {
  // создаем новый набор для тестов функции
  Suite *suite = suite_create("s21_from_decimal_to_int");
  TCase *tc_core = tcase_create("core_of_s21_decimal_to_int");

  // каждыйй тест добавляем
  tcase_add_test(tc_core, test_s21_from_decimal_to_int1);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int2);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int3);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int4);

  // тест кейс добавляем в suite
  suite_add_tcase(suite, tc_core);

  return suite;
}