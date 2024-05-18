#include "./../../Headers/s21_arithmetic_function.h"

bit32_t s21_normalize(s21_DecData *val_data_1, s21_DecData *val_data_2) {
  bit32_t error_code = S21_TRUE;
  if (val_data_1->scale > val_data_2->scale) {
    error_code = s21_norm_base(val_data_1, val_data_2);
  } else if (val_data_1->scale < val_data_2->scale) {
    error_code = s21_norm_base(val_data_2, val_data_1);
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

// работает
bit32_t s21_max(bit32_t val_1, bit32_t val_2) {
  return val_1 > val_2 ? val_1 : val_2;
}

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

// возвращает остаток от деления
bit32_t s21_count_div_10(s21_DecData *value, bit32_t count) {
  bit32_t error_code = S21_TRUE;
  bit32_t i = 0;
  for (; i < count && error_code; i++) {
    error_code = s21_div_10(value);
  }
  return error_code;
}

bit32_t s21_basic_add(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {
  bit32_t code_error = s21_norm_base(&value_1, &value_2);
  if (code_error) {
    if (value_1.sign == value_2.sign) {
      code_error = s21_add_mantis(value_1, value_2, result);
    } else {
      if (s21_decimal_compare_mantis == 1) {
        result->sign = value_1.sign;
        code_error = s21_sub_mantis(value_1, value_2, result);
      } else {
        result->sign = value_2.sign;
        code_error = s21_sub_mantis(value_2, value_1, result);
      }
    }
    if (code_error) {
      code_error = s21_decimal_norm(result);
    } else {
      *result = s21_decimal_null_data();
    }
  } else {
    *result = s21_decimal_null_data();
  }
  return code_error;
}

// с учетом переполнения
bit32_t s21_basic_sub(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {
  bit32_t code_error = s21_norm_base(&value_1, &value_2);
  if (code_error) {
    code_error = s21_sub_mantis(value_1, value_2, result);
    if (code_error) {
      code_error = s21_decimal_norm(result);
    } else {
      *result = s21_decimal_null_data();
    }
  } else {
    *result = s21_decimal_null_data();
  }
  return code_error;
}

// с учетом переполнения
bit32_t s21_basic_mul(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {}

// с учетом округления
bit32_t s21_basic_div(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {}
