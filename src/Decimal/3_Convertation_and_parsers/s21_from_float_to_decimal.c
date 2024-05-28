#include <math.h>

#include "./../../Headers/s21_convertation_and_parsers.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  bit32_t error_code = S21_CONV_SUCCESS;
  if (dst == NULL || isinf(src) || isnan(src)) {
    error_code = S21_CONV_ERROR;
  } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
    error_code = S21_CONV_ERROR;
  } else if (fabsf(src) == 0.0) {
    *dst = s21_decimal_null();
  } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
    *dst = s21_decimal_null();
    error_code = S21_CONV_ERROR;
  } else {
    float new = src;
    *dst = s21_decimal_null();
    if (new < 0.0) {
      *dst = s21_decimal_set_sign(*dst, 1);
      src = fabsf(src);
    }
    float check_scale = src;
    int scale = 7;
    while (check_scale > 1) {
      check_scale /= 10;
      scale--;
    }
    if (scale > 0) {
      for (int i = scale; i > 0; i--) {
        src *= 10;
      }
      float new = src - round(src * 10) / 10;
      if (new > 1e-7) {
        src++;
      }
    }

    dst->bits[0] = round(src);
    *dst = s21_decimal_set_scale(*dst, scale);
  }
  return error_code;
}