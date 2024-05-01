#include "test_s21_decimal.h"

START_TEST(test_s21_from_decimal_to_int1) {
	s21_decimal decimal;
	s21_decimal_init(&decimal);
	
	int result, error_code;

	error_code = s21_from_decimal_to_int(decimal, &result);
	
	ck_assert_int_eq(error_code, S21_CONV_SUCCESS);
	ck_assert_int_eq(result, 0);
} 
END_TEST

START_TEST(test_s21_from_decimal_to_int2) {
	s21_decimal decimal;
	s21_decimal_init(&decimal);
	decimal_1 = s21_decimal_set_bit(decimal, 1, 1); 

	int result, error_code;

	error_code = s21_from_decimal_to_int(decimal, &result);

	ck_assert_int_eq(error_code, S21_CONV_SUCCESS);
	ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int3) {
	s21_decimal decimal;
	s21_decimal_init(&decimal);

	for (int i = 0; i < MAX_BLOCK - 1; ++i) {
		decimal.bits[i] = ~decimal.bits[i];
	}
	
	int result, error_code;

	error_code = s21_from_decimal_to_int(decimal, &result);

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

	// тест кейс добавляем в suite
    suite_add_tcase(suite, tc_core);

    return suite;
}
