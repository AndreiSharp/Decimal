#include "./../../Headers/s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
	unsigned int error_code = S21_CONV_SUCCESS;
	if (dst) {
		unsigned int exp = 0, sign = 1;
		if (src < 0) {
			sign = 0;
			src *= -1;
		}
		int src_int = (int) src;
		while (src - src_int > 0) {
			src *= 10;
			src_int = (int) src;
			++exp;
		}
		s21_from_int_to_decimal(src_int, dst); 
		*dst = s21_decimal_set_exp(*dst, exp);
		*dst = s21_decimal_set_bit(*dst, DECIMAL_SIGN_POS, sign);
	} else {
		error_code = S21_CONV_ERROR;
	}

	return error_code;
}