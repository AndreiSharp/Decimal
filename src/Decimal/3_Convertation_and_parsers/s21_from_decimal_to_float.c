#include "./../../Headers/s21_convertation_and_parsers.h"

// hernya
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_code = S21_CONV_SUCCESS;
  if (dst == NULL || !s21_decimal_is_correct(src)) {
    error_code = S21_CONV_ERROR;
  } else {
    *dst = 0;
    s21_DecData src_DecData = s21_decimal_get_data(src);
    if ((bit32_t)src_DecData.scale -
            (src_DecData.high_bit / 3 + (src_DecData.high_bit % 3 != 0)) >
        MAX_SCALE) {
      error_code = S21_CONV_ERROR;
      *dst = 0;
    } else {
      if (src_DecData.scale > 7) {
        s21_count_div_10(&src_DecData, src_DecData.scale - 7);
      }
      if (src_DecData.high_bit > 23) {
        error_code = S21_CONV_ERROR;
      } else {
        s21_DecData residue = s21_decimal_null_data();
        for (int i = src_DecData.scale; i > 0; i--) {
          residue = s21_div_10(&src_DecData);
          *dst += residue.value.bits[0];
          *dst = *dst / 10;
        }
        *dst += src_DecData.value.bits[0];
        if (src_DecData.sign) {
          *dst *= -1;
        }
      }
    }
  }
  return error_code;
}