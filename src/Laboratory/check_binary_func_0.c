#include <stdio.h>

#include "./../Headers/s21_decimal_types.h"

// работает
bit_t s21_get_bit(bit32_t number, int index) {
  return ((0b1 << index) & number) >> index;
}

// работает
bit32_t s21_set_bit(bit32_t number, int index) {
  return number | (0b1 << index);
}

// работает
bit32_t s21_reset_bit(bit32_t number, int index) {
  return number & ~(0b1 << index);
}

// работает
int s21_get_high_bit(bit32_t value) {
  int index = SIZE_BLOCK - 1;
  while (!s21_get_bit(value, index) && index != -1) {
    index--;
  }
  return index;
}

// работает
bit_t s21_decimal_get_bit(s21_decimal value, int index) {
  return s21_get_bit(value.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
}

// работает
s21_decimal s21_decimal_set_bit(s21_decimal value, int index, bit_t bit) {
  if (bit == 0) {
    value.bits[index / SIZE_BLOCK] =
        s21_reset_bit(value.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  } else {
    value.bits[index / SIZE_BLOCK] =
        s21_set_bit(value.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  }
  return value;
}

// работает
int s21_decimal_get_high_bit(s21_decimal value) {
  int index = SIZE_MANTIS - 1;
  while (!s21_decimal_get_bit(value, index) && index != -1) {
    index--;
  }
  return index;
}

// работает
bit32_t s21_decimal_get_sign(s21_decimal value) {
  return s21_decimal_get_bit(value, SIGN_POS + SIZE_MANTIS);
}

// работает
s21_decimal s21_decimal_set_sign(s21_decimal value, bit32_t bit) {
  return s21_decimal_set_bit(value, SIGN_POS + SIZE_MANTIS, bit);
}

// работает
s21_decimal s21_decimal_abs(s21_decimal value) {
  return s21_decimal_set_sign(value, 0);
}

// работает
bit32_t s21_decimal_get_scale(s21_decimal value) {
  bit32_t scale;
  value = s21_decimal_abs(value);
  scale = value.bits[DATA_INDEX] >> SCALE_POS_L;
  return scale;
}

// работает
s21_decimal s21_decimal_set_scale(s21_decimal value, bit32_t scale) {
  bit32_t sign = s21_decimal_get_sign(value);
  value.bits[DATA_INDEX] = scale << SCALE_POS_L;
  return s21_decimal_set_sign(value, sign);
}

// работает
s21_decimal s21_decimal_null() {
  s21_decimal new;
  for (int i = 0; i < COUNT_BLOCKS; ++i) {
    new.bits[i] = 0;
  }
  return new;
}

// работает
void print_decimal(s21_decimal value) {
  printf("\ndecimal:\n");
  for (int j = COUNT_BLOCKS - 1; j >= 0; j--) {
    for (int i = (SIZE_BLOCK) * (j + 1) - 1; i >= SIZE_BLOCK * j; i--) {
      printf("%u", s21_decimal_get_bit(value, i));
    }
    printf(" ");
  }
  printf("\n\n");
}

// работает
void print_dec_data(s21_DecData data) {
  printf("\ndecimal data:\n");
  printf("sign = %d\n", data.sign);
  printf("scale = %d\n", data.scale);
  printf("high_bit = %d\n", data.high_bit);
  print_decimal(data.value);
}

// работает
s21_decimal s21_decimal_rshift(s21_decimal value) {
  s21_decimal result = s21_decimal_null();
  for (int i = 0; i < s21_decimal_get_high_bit(value); i++) {
    result = s21_decimal_set_bit(result, i, s21_decimal_get_bit(value, i + 1));
  }
  return result;
}

// работает
s21_decimal s21_decimal_lshift(s21_decimal value) {
  s21_decimal result = s21_decimal_null();
  for (int i = 0; i <= s21_decimal_get_high_bit(value); i++) {
    result = s21_decimal_set_bit(result, i + 1, s21_decimal_get_bit(value, i));
  }
  return result;
}

// работает
bit32_t s21_check_null_stack(s21_decimal value) {
  bit32_t bits = 0;
  for (bit32_t i = 0; i < SCALE_POS_L - 1 && !bits; i++) {
    bits += s21_decimal_get_bit(value, i + SIZE_MANTIS);
  }
  if (!bits) {
    for (int i = SCALE_POS_L; i < SIGN_POS; i++) {
      bits |= s21_decimal_get_bit(value, i + SIZE_MANTIS);
    }
  }
  return !bits;
}

// работает
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

// работает
s21_decimal s21_decimal_invert(s21_decimal value) {
  for (int i = 0; i < COUNT_BLOCKS_MANTIS; i++) {
    value.bits[i] = ~value.bits[i];
  }
  return value;
}

// работает
bit32_t s21_add_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result) {
  bit32_t code_error = S21_TRUE;
  bit_t bit = 0;
  s21_decimal new = s21_decimal_null();
  for (int i = 0; i < SIZE_MANTIS; i++) {
    bit = s21_decimal_get_bit(value_1, i) + s21_decimal_get_bit(value_2, i) +
          s21_decimal_get_bit(new, i);
    new = s21_decimal_set_bit(new, i, bit % 2);
    if (bit / 2) {
      new = s21_decimal_set_bit(new, i + 1, bit / 2);
    }
  }
  if (new.bits[DATA_INDEX] != 0) {
    code_error = S21_FALSE;
  }
  *result = new;
  return code_error;
}

// работает
bit_t s21_mul_mantis(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  s21_decimal new = s21_decimal_null();
  bit_t code_error = S21_TRUE;
  bit_t high_bit_1 = s21_decimal_get_high_bit(value_1);
  bit_t high_bit_2 = s21_decimal_get_high_bit(value_2);
  if (high_bit_1 < high_bit_2) {
    for (bit32_t i = 0; i <= high_bit_1; i++) {
      if (s21_decimal_get_bit(value_1, i)) {
        code_error = s21_add_mantis(new, value_2, &new);
      }
      value_2 = s21_decimal_lshift(value_2);
    }
  } else {
    for (bit32_t i = 0; i <= high_bit_2; i++) {
      if (s21_decimal_get_bit(value_2, i)) {
        code_error = s21_add_mantis(new, value_1, &new);
      }
      value_1 = s21_decimal_lshift(value_1);
    }
  }
  *result = new;
  return code_error;
}

bit32_t s21_mul_10(s21_decimal *value) {
  bit_t code_error = S21_TRUE;
  s21_decimal ten = s21_decimal_null();
  ten.bits[0] = 10;
  s21_decimal new = s21_decimal_null();
  code_error = s21_mul_mantis(*value, ten, &new);
  if (code_error) {
    *value = new;
  }
  return code_error;
}

int main() {
  s21_decimal value = s21_decimal_null();
  s21_decimal result = s21_decimal_null();
  unsigned int num = 10;
  value.bits[0] = num;

  printf("CHECK DECIMAL_SET_BIT\n");
  value = s21_decimal_set_bit(value, 127, 1);
  print_decimal(value);

  printf("CHECK DECIMAL_INVERT\n");
  value = s21_decimal_invert(value);
  print_decimal(value);

  printf("CHECK ADD_MANTIS\n");
  printf("result add mantis = %d", s21_add_mantis(value, value, &result));
  print_decimal(result);

  value = s21_decimal_invert(value);
  result = s21_decimal_invert(result);

  printf("CHECK MUL_MANTIS\n");
  printf("result mul mantis = %d", s21_mul_mantis(value, result, &result));
  print_decimal(result);

  printf("CHECK MUL10_MANTIS\n");
  printf("result mul10 mantis = %d", s21_mul_10(&result));
  print_decimal(result);

  printf("CHECK DECIMAL_IS_CORRECT\n");
  printf("flag = %d\n", s21_decimal_is_correct(value));

  printf("CHECK DECIMAL_ABS\n");
  value = s21_decimal_abs(value);
  print_decimal(value);

  printf("CHECK DECIMAL_GET_SCALE\n");
  printf("scale = %d\n", s21_decimal_get_scale(value));

  printf("CHECK DECIMAL_SET_SCALE\n");
  value = s21_decimal_set_scale(value, 28);
  print_decimal(value);

  printf("CHECK DECIMAL_DATA\n");
  s21_DecData data;
  data.value = value;
  data.scale = s21_decimal_get_scale(value);
  data.sign = s21_decimal_get_sign(value);
  data.high_bit = s21_decimal_get_high_bit(value);
  print_dec_data(data);

  return 0;
}