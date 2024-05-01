#include "./../6_Headers/s21_help_function.h"

unsigned int s21_decimal_is_correct(s21_decimal value) {
  unsigned int flag = S21_SUCCES;
  if (!s21_check_null_stack(value)) {
    flag = S21_ERROR;
  } else {
    int exp = s21_get_exp(value);
    if (exp < 0 || exp > 28) {
      flag = S21_ERROR;
    }
  }
  return flag;
}

unsigned int s21_check_null_stack(s21_decimal value) {
  int bits = 0;
  for (int i = 0; i < EXP_POS_L - 1 && !bits; i++) {
    bits |= value.bits[DATA_INDEX] >> i;
  }
  for (int i = EXP_POS_R; i < SIGN_POS; i++) {
    bits |= value.bits[DATA_INDEX] >> i;
  }
  return bits;
}

unsigned int s21_decimal_init(s21_decimal *decimal) {
  int point_error = S21_SUCCES;
  if (decimal) {
    for (int i = 0; i < COUNT_BLOCKS; ++i) {
      (*decimal).bits[i] = 0;
    }
    *decimal = s21_decimal_set_bit(*decimal, EXP_POS_L, 1);
  } else {
    point_error = S21_ERROR;
  }
  return point_error;
}

unsigned int s21_decimal_copy(s21_decimal src, s21_decimal *dest) {
  unsigned int flag_error = 1;
  if (dest) {
    for (int i = 0; i < COUNT_BLOCKS; ++i) {
      (*dest).bits[i] = src.bits[i];
    }
  } else {
    flag_error = 0;
  }
  return flag_error;
}

unsigned int s21_normalization(s21_decimal *value_1, s21_decimal *value_2) {
  unsigned int flag = S21_SUCCES;
  if (value_1 && value_2) {
    int exp_1 = s21_decimal_exp(*value_1);
    int exp_2 = s21_decimal_exp(*value_2);
    if (exp_1 > exp_2) {
      flag = s21_count_mul10(value_2, exp_1 - exp_2);
      flag = s21_decimal_add_exp(value_2, exp_1 - exp_2);
    } else if (exp_2 > exp_1) {
      flag = s21_count_mul10(value_1, exp_2 - exp_1);
      flag = s21_decimal_add_exp(value_1, exp_2 - exp_1);
    }
  } else {
    flag = S21_ERROR;
  }
  return flag;
}

static int s21_get_sub_10(bit_t prefix[], size_t n) {
  unsigned int prefix10 = 0;
  for (int i = 0, pow = 1 << (n - 1); i < n; ++i, pow >>= 1) {
    prefix10 += prefix[i] * pow;
  }
  return prefix10 - 10;
}

static bit_t *s21_sub_to_bin(bit_t prefix[], size_t n, unsigned int sub) {
  for (int i = 0, pow = 1 << (n - 1); i < n; ++i, pow >>= 1) {
    prefix[i] = sub / pow;
    sub %= pow;
  }
  return prefix;
}

s21_decimal s21_decimal_div_10(s21_decimal decimal) {
  s21_decimal result;
  s21_decimal_init(&result);
  int start = s21_no_zero_bit(decimal);
  for (int i = start; i >= 3; --i) {
    if (i == start) {
      bit_t prefix[4];
      for (int j = 0; j < 4; ++j) {
        prefix[j] = s21_decimal_get_bit(decimal, i - j);
      }
      int sub = s21_get_sub_10(prefix, 4);
      if (sub >= 0) {
        bit_t *new_prefix = s21_sub_to_bin(prefix, 4, sub);
        for (int j = 0; j < 4; ++j) {
          decimal = s21_decimal_set_bit(decimal, i - j, new_prefix[j]);
        }
        result = s21_decimal_set_bit(result, i - 3, 1);
      }
    } else {
      bit_t prefix[5];
      for (int j = 0; j < 5; ++j) {
        prefix[j] = s21_decimal_get_bit(decimal, i - j + 1);
      }
      int sub = s21_get_sub_10(prefix, 5);
      if (sub >= 0) {
        bit_t *new_prefix = s21_sub_to_bin(prefix, 5, sub);
        for (int j = 0; j < 5; ++j) {
          decimal = s21_decimal_set_bit(decimal, i - j + 1, new_prefix[j]);
        }

        result = s21_decimal_set_bit(result, i - 3, 1);
      }
    }
  }
  return result;
}

unsigned int s21_mul10(s21_decimal value, s21_decimal *result) {
  s21_decimal *buf;
  s21_decimal_init(buf);
  buf->bits[3] = value.bits[3];
  unsigned int flag = S21_SUCCES;
  unsigned int res = 0;
  for (int i = 1; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_get_bit(value, i - 1);
    *buf = s21_decimal_set_bit(*buf, i, res);
  }
  for (int i = 3; i < SIZE_MANTIS; i++) {
    flag =
        s21_decimal_get_bit(*buf, i) + s21_decimal_get_bit(value, i - 3) + res;
    *buf = s21_decimal_set_bit(*buf, i, res % 2);
    res = res / 2;
  }
  if (res) {
    flag = S21_TOO_LARGE;
  } else {
    result = buf;
  }
  return flag;
}

unsigned int s21_count_mul10(s21_decimal *value, int count) {
  unsigned int flag = S21_SUCCES;
  s21_decimal *result;
  for (int i = 0; i < count; i++) {
    // Умножение мантисы на 10
    flag = s21_mul10(*value, result);
  }
  if (!flag) {
    value = result;
  }
  return flag;
}

void s21_pos_zero_decimal(s21_decimal *value) {
  int check_zero = s21_mantis_is_equal_null(*value);
  if (check_zero == 1) {
    *value = s21_decimal_set_bit(*value, 127, 0);
  }
}