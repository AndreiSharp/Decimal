#include "./../../Headers/s21_decimal_function.h"

s21_decimal s21_decimal_null() {
  s21_decimal new;
  for (int i = 0; i < COUNT_BLOCKS; ++i) {
    new.bits[i] = 0;
  }
  return new;
}


bit32_t s21_decimal_is_null(s21_decimal value) {
  return !(value.bits[0] || value.bits[1] || value.bits[2]);
}

s21_decimal s21_decimal_invert(s21_decimal value, bit32_t count) {
  for (bit32_t i = 0; i < count; i++) {
    value.bits[i] = ~value.bits[i];
  }
  return value;
}

s21_decimal s21_decimal_lshift(s21_decimal value) {
  s21_decimal result = s21_decimal_null();
  for (bit32_t i = 0; i < s21_decimal_get_high_bit(value); i++) {
    result = s21_decimal_set_bit(result, i + 1, s21_decimal_get_bit(value, i));
  }
  return result;
}

s21_decimal s21_decimal_rshift(s21_decimal value) {
  s21_decimal result = s21_decimal_null();
  bit32_t high_bit = s21_decimal_get_high_bit(value);
  for (bit32_t i = 0; i < high_bit; i++) {
    result = s21_decimal_set_bit(result, i, s21_decimal_get_bit(value, i + 1));
  }
  return result;
}

s21_decimal s21_decimal_lshift_count(s21_decimal value, bit32_t count) {
  for (bit32_t i = 0; i < count; i++) {
    value = s21_decimal_lshift(value);
  }
  return value;
}

s21_decimal s21_decimal_rshift_count(s21_decimal value, bit32_t count) {
  for (bit32_t i = 0; i < count; i++) {
    value = s21_decimal_rshift(value);
  }
  return value;
}

bit32_t s21_check_null_stack(s21_decimal value) {
  bit32_t bits = 0;
  for (bit32_t i = 0; i < SCALE_POS_L - 1 && !bits; i++) {
    bits |= s21_decimal_get_bit(value, i + SIZE_MANTIS);
  }
  if (!bits) {
    for (bit32_t i = SCALE_POS_R; i < SIGN_POS; i++) {
      bits |= s21_decimal_get_bit(value, i + SIZE_MANTIS);
    }
  }
  return !bits;
}


s21_DecData s21_decimal_null_data() {
  s21_DecData data;
  for (bit32_t i = 0; i < COUNT_BLOCKS; i++) {
    data.value.bits[i] = 0;
  }
  data.sign = 0;
  data.scale = 0;
  data.high_bit = 0;
  return data;
}

s21_DecData s21_decimal_get_data(s21_decimal value) {
  s21_DecData data;
  for (bit32_t i = 0; i < COUNT_BLOCKS_MANTIS; i++) {
    data.value.bits[i] = value.bits[i];
  }
  data.value.bits[3] = 0;
  data.sign = s21_decimal_get_sign(value);
  data.scale = s21_decimal_get_scale(value);
  data.high_bit = s21_decimal_get_high_bit(data.value);
  return data;
}

s21_decimal s21_decimal_set_data(s21_DecData data) {
  s21_decimal value;
  for (bit32_t i = 0; i < COUNT_BLOCKS_MANTIS; i++) {
    value.bits[i] = data.value.bits[i];
  }
  value = s21_decimal_set_scale(value, data.scale);
  value = s21_decimal_set_sign(value, data.sign);
  return value;
}

s21_DecData s21_decimal_copy_data(s21_DecData data) {
  s21_DecData new = data;
  return new;
}

// Функции для вывода перед сдачей удалить!!

// void print_decimal(s21_decimal value, char* name) {
//   printf("decimal : %s\n", name);
//   for (int j = COUNT_BLOCKS - 1; j >= 0; j--) {
//     for (int i = (SIZE_BLOCK) * (j + 1) - 1; i >= SIZE_BLOCK * j; i--) {
//       printf("%u", s21_decimal_get_bit(value, i));
//     }
//     printf(" ");
//   }
//   printf("\n\n");
// }

// // работает
// void print_dec_data(s21_DecData data, char* name) {
//   printf("\ndecimal data: %s\n", name);
//   printf("sign = %d\n", data.sign);
//   printf("scale = %d\n", data.scale);
//   printf("high_bit = %d\n", data.high_bit);
//   print_decimal(data.value, "");
// }

// s21_decimal s21_decimal_copy(s21_decimal value) {
//   s21_decimal result;
//   for (int i = 0; i < COUNT_BLOCKS; i++) {
//     result.bits[i] = value.bits[i];
//   }
//   return result;
// }



bit32_t s21_decimal_is_correct(s21_decimal value) {
  bit32_t flag = S21_TRUE;
  if (!s21_check_null_stack(value)) {
    flag = S21_FALSE;
  } else {
    int scale = s21_decimal_get_scale(value);
    if (scale < 0 || scale > 28) {
      flag = S21_FALSE;
    }
  }
  return flag;
}