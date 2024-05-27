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
bit32_t s21_get_high_bit(bit32_t value) {
  bit32_t index = SIZE_BLOCK;
  while (index >= 0 && !s21_get_bit(value, index)) {
    index--;
  }
  return (bit32_t)(index + 1);
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
bit32_t s21_decimal_get_high_bit(s21_decimal value) {
  int index = SIZE_DECIMAL;
  for (int i = DATA_INDEX; i > 0 && !value.bits[i]; i--) {
    if (!value.bits[i]) {
      index -= SIZE_BLOCK;
    }
  }
  while (index != -1 && !s21_decimal_get_bit(value, index)) {
    index--;
  }
  return (bit32_t)(index + 1);
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

bit32_t s21_decimal_is_null(s21_decimal value) {
  bit32_t result = 1;
  for (int i = 0; i < COUNT_BLOCKS; i++) {
    result = result && (value.bits[i] == 0);
  }
  return result;
}

// работает
void print_decimal(s21_decimal value) {
  printf("decimal:");
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
  printf("\ndecimal data:");
  printf("sign = %d\n", data.sign);
  printf("scale = %d\n", data.scale);
  printf("high_bit = %d\n", data.high_bit);
  print_decimal(data.value);
}

// работает
s21_decimal s21_decimal_rshift(s21_decimal value) {
  s21_decimal result = s21_decimal_null();
  for (bit32_t i = 0; i < s21_decimal_get_high_bit(value); i++) {
    result = s21_decimal_set_bit(result, i, s21_decimal_get_bit(value, i + 1));
  }
  return result;
}

// работает
s21_decimal s21_decimal_lshift(s21_decimal value) {
  s21_decimal result = s21_decimal_null();
  for (bit32_t i = 0; i < s21_decimal_get_high_bit(value); i++) {
    result = s21_decimal_set_bit(result, i + 1, s21_decimal_get_bit(value, i));
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

// работает
bit32_t s21_check_null_stack(s21_decimal value) {
  bit32_t bits = 0;
  for (bit32_t i = 0; i < SCALE_POS_L - 1 && !bits; i++) {
    bits += s21_decimal_get_bit(value, i + SIZE_MANTIS);
  }
  if (!bits) {
    for (bit32_t i = SCALE_POS_L; i < SIGN_POS; i++) {
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
    bit32_t scale = s21_decimal_get_scale(value);
    if (scale < 0 || scale > 28) {
      flag = S21_FALSE;
    }
  }
  return flag;
}

// работает
s21_decimal s21_decimal_invert(s21_decimal value, bit32_t count) {
  for (bit32_t i = 0; i < count; i++) {
    value.bits[i] = ~value.bits[i];
  }
  return value;
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
  data.high_bit = s21_decimal_get_high_bit(value);
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

// работает
bit32_t s21_max(bit32_t val_1, bit32_t val_2) {
  return val_1 > val_2 ? val_1 : val_2;
}

// работает
// возвращает 1 - если нет переполнения и 0 - если переполнение есть
bit32_t s21_add_mantis(s21_DecData value_1, s21_DecData value_2,
                       s21_DecData *result) {
  bit32_t error_code = S21_TRUE;
  bit_t bit = 0;
  s21_decimal new = s21_decimal_null();
  for (bit32_t i = 0; i <= s21_max(value_1.high_bit, value_2.high_bit); i++) {
    bit = s21_decimal_get_bit(value_1.value, i) +
          s21_decimal_get_bit(value_2.value, i) + s21_decimal_get_bit(new, i);
    new = s21_decimal_set_bit(new, i, bit % 2);
    if (bit / 2) {
      new = s21_decimal_set_bit(new, i + 1, bit / 2);
    }
  }
  if (new.bits[DATA_INDEX] != 0) {
    error_code = S21_FALSE;
  }
  result->value = new;
  result->high_bit = s21_decimal_get_high_bit(result->value);
  return error_code;
}

// хз
bit32_t s21_sub_mantis(s21_DecData value_1, s21_DecData value_2,
                       s21_DecData *result) {
  bit_t error_code = S21_TRUE;
  s21_DecData new = s21_decimal_null_data();
  value_1.value = s21_decimal_invert(value_1.value, COUNT_BLOCKS);
  value_1.high_bit = s21_decimal_get_high_bit(value_1.value);
  error_code = s21_add_mantis(value_1, value_2, &new);
  new.value = s21_decimal_invert(new.value, COUNT_BLOCKS);
  result->value = new.value;
  result->high_bit = s21_decimal_get_high_bit(result->value);
  return error_code;
}

// работает
bit_t s21_mul_mantis(s21_DecData value_1, s21_DecData value_2,
                     s21_DecData *result) {
  s21_DecData new = s21_decimal_null_data();
  bit_t error_code = S21_TRUE;
  if (value_1.high_bit < value_2.high_bit) {
    for (bit32_t i = 0; i < value_1.high_bit; i++) {
      if (s21_decimal_get_bit(value_1.value, i)) {
        error_code = s21_add_mantis(new, value_2, &new);
      }
      value_2.value = s21_decimal_lshift(value_2.value);
      value_2.high_bit++;
    }
  } else {
    for (bit32_t i = 0; i < value_2.high_bit; i++) {
      if (s21_decimal_get_bit(value_2.value, i)) {
        error_code = s21_add_mantis(new, value_1, &new);
      }
      value_1.value = s21_decimal_lshift(value_1.value);
      value_1.high_bit++;
    }
  }
  *result = new;
  return error_code;
}

// работает
// возвращает 1 - если успешно и 0 - если есть переполнение;
bit32_t s21_mul_10(s21_DecData *value) {
  bit_t error_code = S21_TRUE;
  s21_DecData ten = s21_decimal_null_data();
  ten.value.bits[0] = 10;
  ten.high_bit = s21_get_high_bit(10);
  s21_DecData new = s21_decimal_null_data();
  error_code = s21_mul_mantis(*value, ten, &new);
  value->value = new.value;
  value->high_bit = new.high_bit;
  value->sign = new.sign;
  value->scale++;
  return error_code;
}

bit32_t s21_decimal_compare_mantis(s21_DecData value_1, s21_DecData value_2) {
  bit32_t flag = 0;
  if (value_1.high_bit == value_2.high_bit) {
    for (int i = value_1.high_bit - 1; i >= 0 && flag == 0; i--) {
      if (s21_decimal_get_bit(value_1.value, i) >
          s21_decimal_get_bit(value_2.value, i)) {
        flag = 1;
      } else if (s21_decimal_get_bit(value_1.value, i) <
                 s21_decimal_get_bit(value_2.value, i)) {
        flag = 2;
      }
    }
  } else if (value_1.high_bit > value_2.high_bit) {
    flag = 1;
  } else {
    flag = 2;
  }
  return flag;
}

s21_DecData s21_div_mantis(s21_DecData value_1, s21_DecData value_2,
                           s21_DecData *result) {
  s21_decimal new = s21_decimal_null();
  bit32_t shift = value_1.high_bit - value_2.high_bit;
  if ((int)shift >= 0) {
    value_2.value = s21_decimal_lshift_count(value_2.value, shift);
    value_2.high_bit += shift;
    while ((int)shift >= 0) {
      if (s21_decimal_compare_mantis(value_1, value_2) == 2) {
        value_2.value = s21_decimal_rshift(value_2.value);
        value_2.high_bit--;
        new = s21_decimal_set_bit(new, shift, 0);
      } else {
        s21_sub_mantis(value_1, value_2, &value_1);
        new = s21_decimal_set_bit(new, shift, 1);
        value_2.value = s21_decimal_rshift(value_2.value);
        value_2.high_bit--;
      }
      shift--;
    }
  }
  result->value = new;
  result->high_bit = s21_decimal_get_high_bit(result->value);
  return value_1;
}

// ошибка по округлению здесь
bit32_t s21_bank_round_data(s21_DecData *num, s21_DecData residue) {
  bit_t error_code = S21_TRUE;
  residue.value = s21_decimal_lshift(residue.value);
  residue.high_bit++;
  if (s21_decimal_compare_mantis(residue, *num) != 2 &&
      (s21_decimal_get_bit(num->value, 0) || s21_decimal_is_null(num->value))) {
    s21_DecData new = s21_decimal_null_data();
    new.value.bits[0] = 1;
    new.high_bit = 0;
    error_code = s21_add_mantis(new, *num, num);
  }
  return error_code;
}

// возвращает остаток от деления
bit32_t s21_div_10(s21_DecData *value) {
  bit_t error_code = S21_TRUE;
  s21_DecData ten = s21_decimal_null_data();
  ten.value.bits[0] = 10;
  ten.high_bit = s21_decimal_get_high_bit(ten.value);
  s21_DecData new = s21_decimal_null_data();
  s21_DecData residue = s21_div_mantis(*value, ten, &new);
  if (!s21_decimal_is_null(residue.value)) {
    error_code = s21_bank_round_data(&new, residue);
  }
  value->value = new.value;
  value->high_bit = new.high_bit;
  value->sign = new.sign;
  value->scale--;
  return error_code;
}

// возвращает количество удавшихся умножений
bit32_t s21_count_mul_10(s21_DecData *value, bit32_t count) {
  bit32_t error_code = S21_TRUE;
  bit32_t i = 0;
  for (; i < count && error_code; i++) {
    error_code = s21_mul_10(value);
  }
  if (!error_code) {
    s21_div_10(value);
    i--;
  }
  return i;
}

// возвращает остаток от деления
bit32_t s21_count_div_10(s21_DecData *value, bit32_t count) {
  bit32_t error_code = S21_TRUE;
  bit32_t i = 0;
  for (; i < count && error_code; i++) {
    error_code = s21_div_10(value);
  }
  return error_code;
}

// найти случаи когда возможна ошибка и добавить изменение степени
bit32_t s21_norm_base(s21_DecData *val_data_1, s21_DecData *val_data_2) {
  bit32_t error_code = S21_TRUE;
  bit32_t count_scale = val_data_1->scale - val_data_2->scale;
  bit32_t need_bits = count_scale * 3;
  bit32_t free_bits = SIZE_MANTIS - val_data_2->high_bit;
  bit32_t count_free = free_bits / 3;
  if (need_bits < free_bits) {
    count_free = s21_count_mul_10(val_data_2, count_scale);
    if ((bit32_t)val_data_1->high_bit + 1 >= 3 * (count_scale - count_free)) {
      s21_count_div_10(val_data_1, (count_scale - count_free));
    }
  } else {
    count_free = count_free - s21_count_mul_10(val_data_2, count_free);
    if ((bit32_t)val_data_1->high_bit + 1 >= 3 * (count_scale - count_free)) {
      s21_count_div_10(val_data_1, (count_scale - count_free));
    } else {
      error_code = S21_FALSE;
    }
  }
  return error_code;
}

bit32_t s21_normalize(s21_DecData *val_data_1, s21_DecData *val_data_2) {
  bit32_t error_code = S21_TRUE;
  if (val_data_1->scale > val_data_2->scale) {
    error_code = s21_norm_base(val_data_1, val_data_2);
  } else if (val_data_1->scale < val_data_2->scale) {
    error_code = s21_norm_base(val_data_2, val_data_1);
  }
  return error_code;
}

int main() {
  s21_DecData value_1 = s21_decimal_null_data();
  s21_DecData value_2 = s21_decimal_null_data();
  s21_DecData result = s21_decimal_null_data();
  value_1.value.bits[0] = 26;
  value_2.value.bits[0] = 6;
  value_1 = s21_decimal_get_data(value_1.value);
  value_2 = s21_decimal_get_data(value_2.value);

  printf("CHECK ADD_MANTIS\n");
  printf("START DATA\n");
  printf("Val_1\n");
  print_dec_data(value_1);
  printf("Val_2\n");
  print_dec_data(value_2);
  printf("___________________________________\n\n");
  printf("result add mantis = %d", s21_add_mantis(value_1, value_2, &result));
  print_dec_data(result);
  printf("___________________________________\n\n");

  printf("CHECK SUB_MANTIS\n");
  printf("START DATA\n");
  printf("Val_1\n");
  print_dec_data(value_1);
  printf("Val_2\n");
  print_dec_data(value_2);
  printf("___________________________________\n\n");
  printf("result sub mantis = %d", s21_sub_mantis(value_1, value_2, &result));
  print_dec_data(result);
  printf("___________________________________\n\n");

  printf("CHECK MUL_MANTIS\n");
  printf("START DATA\n");
  printf("Val_1\n");
  print_dec_data(value_1);
  printf("Val_2\n");
  print_dec_data(value_2);
  printf("___________________________________\n\n");
  printf("result mul mantis = %d", s21_mul_mantis(value_1, value_2, &result));
  print_dec_data(result);
  printf("___________________________________\n\n");

  printf("CHECK MUL10_MANTIS\n");
  printf("START DATA\n");
  print_dec_data(result);
  printf("___________________________________\n\n");
  printf("result mul10 mantis = %d", s21_mul_10(&result));
  print_dec_data(result);
  printf("___________________________________\n\n");

  printf("CHECK COUNT_MUL10_MANTIS\n");
  printf("START DATA\n");
  print_dec_data(result);
  printf("%d*100\n", result.value.bits[0]);
  printf("___________________________________\n\n");
  printf("result count_mul10 mantis = %d\n", s21_count_mul_10(&result, 2));
  print_dec_data(result);
  printf("res = %d\n", result.value.bits[0]);
  printf("___________________________________\n\n");

  printf("CHECK DIV_MANTIS\n");
  printf("START DATA\n");
  print_dec_data(result);
  print_dec_data(value_2);
  printf("%d/%d\n", result.value.bits[0], value_2.value.bits[0]);
  printf("___________________________________\n\n");
  print_dec_data(s21_div_mantis(result, value_2, &result));
  print_dec_data(result);
  printf("%d\n", result.value.bits[0]);
  printf("___________________________________\n\n");

  printf("CHECK DIV10_MANTIS\n");
  printf("START DATA\n");
  print_dec_data(result);
  printf("before = %u\n", result.value.bits[0]);
  printf("___________________________________\n\n");
  printf("result div10 mantis = %d\n", s21_div_10(&result));
  printf("res = %u\n", result.value.bits[0]);
  print_dec_data(result);
  printf("___________________________________\n\n");

  printf("CHECK COUNT_DIV10_MANTIS\n");
  printf("START DATA\n");
  print_dec_data(result);
  printf("%u/1000\n", result.value.bits[0]);
  printf("___________________________________\n\n");
  printf("result count_div10 mantis = %d\n", s21_count_div_10(&result, 3));
  print_dec_data(result);
  printf("res = %u\n", result.value.bits[0]);
  printf("___________________________________\n\n");

  value_1.value = s21_decimal_invert(value_1.value, COUNT_BLOCKS_MANTIS);
  value_1.high_bit = s21_decimal_get_high_bit(value_1.value);
  value_1.scale = 0;
  value_2.scale = 1;
  printf("CHECK NORM_DEC\n");
  printf("START DATA\n");
  printf("Val_1\n");
  print_dec_data(value_1);
  printf("Val_2\n");
  print_dec_data(value_2);
  printf("before = %u\n", value_2.value.bits[0]);
  printf("___________________________________\n\n");
  printf("result norm = %d\n", s21_normalize(&value_1, &value_2));
  printf("___________________________________\n\n");
  printf("Val_1\n");
  print_dec_data(value_1);
  printf("Val_2\n");
  print_dec_data(value_2);
  printf("res = %u\n", value_2.value.bits[0]);
  return 0;
}
