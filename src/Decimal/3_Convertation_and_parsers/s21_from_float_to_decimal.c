#include "./../../Headers/s21_convertation_and_parsers.h"

char s21_is_not_max_float(float x) {
  return (MIN_FLOAT_TO_CONVERT < fabs(x) && fabs(x) < MAX_FLOAT_TO_CONVERT) || x == 0.0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_DecData dst_DecData = s21_decimal_null_data();
  bit32_t error_code = S21_CONV_SUCCESS;
  if (dst && !isinf(src) && !isnan(src) && s21_is_not_max_float(src)) {
    if (src < 0) {
      dst_DecData.sign = 1;
      src = fabs(src);
    }
    bit32_t len_int_part_from_src = 0;
    int src_int = src;
    printf("float %f, int part %d\n", src, src_int);
    do {
      src_int /= 10;
      ++len_int_part_from_src;
    }while (src_int > 0);
    printf("len int part %u count mul %u\n", len_int_part_from_src, FLOAT_LEN - len_int_part_from_src);
    for (int i = len_int_part_from_src; i < FLOAT_LEN; ++i) {
      src *= 10;
      printf("float %f\n", src);
      dst_DecData.scale++;
    }

    error_code = s21_from_int_to_decimal(round(src), &dst_DecData.value);
    if (error_code == S21_CONV_SUCCESS) {
      printf("src : %f, round(src) : %f\n", src, round(src));
      dst_DecData.high_bit = s21_decimal_get_high_bit(dst_DecData.value);
      *dst = s21_decimal_set_data(dst_DecData); 
    } else {
      *dst = s21_decimal_null();
    }
  } else {
    error_code = S21_CONV_ERROR;
    *dst = s21_decimal_null();
  }

  puts("");
  return error_code;
}
