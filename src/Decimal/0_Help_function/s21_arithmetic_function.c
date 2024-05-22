#include "./../../Headers/s21_help_function.h"

void s21_normalize(s21_DecData *val_data_1, s21_DecData *val_data_2) {
  if (val_data_1->scale > val_data_2->scale) {
    s21_normalize_base(val_data_1, val_data_2);
  } else if (val_data_1->scale < val_data_2->scale) {
    s21_normalize_base(val_data_2, val_data_1);
  }
}

// найти случаи когда возможна ошибка и добавить изменение степени
void s21_normalize_base(s21_DecData *val_data_1, s21_DecData *val_data_2) {
  bit32_t count_scale =
      val_data_1->scale - val_data_2->scale;  // разница в степени
  bit32_t need_bits =
      count_scale * 3;  // количество бит для предполагаемого сдвига
  bit32_t free_bits =
      SIZE_MANTIS - val_data_2->high_bit;  // количество свободных бит
  bit32_t count_free = free_bits / 3;  // возможное возведение в степень

  if (need_bits < free_bits) {  // провряем возможность умножения
    // умножаем пока не заполним мантису
    count_free = s21_count_mul_10(val_data_2, count_scale);
    // делим с банковским округлением, если мантиса переполнилась
    if ((bit32_t)val_data_1->high_bit + 1 >= 3 * (count_scale - count_free)) {
      s21_count_div_10(val_data_1, (count_scale - count_free));
    }
  } else {
    // умножаем на сколько можем
    count_free = count_free - s21_count_mul_10(val_data_2, count_free);
    // оставшееся делим с банковским округлением
    s21_count_div_10(val_data_1, (count_scale - count_free));
  }
}

bit32_t s21_max(bit32_t val_1, bit32_t val_2) {
  return val_1 > val_2 ? val_1 : val_2;
}

// возвращает 1 - если нет переполнения и 0 - если переполнение есть
bit32_t s21_add_mantis(s21_DecData value_1, s21_DecData value_2,
                       s21_DecData *result) {
  bit32_t error_code = S21_SUCCES;
  bit_t bit = 0;  // переходный бит
  s21_decimal new = s21_decimal_null();
  for (bit32_t i = 0; i <= s21_max(value_1.high_bit, value_2.high_bit); i++) {
    bit = s21_decimal_get_bit(value_1.value, i) +
          s21_decimal_get_bit(value_2.value, i) + s21_decimal_get_bit(new, i);
    new = s21_decimal_set_bit(new, i, bit % 2);
    if (bit / 2) {
      new = s21_decimal_set_bit(new, i + 1, bit / 2);
    }
  }
  // проверка на наличие бита в запрещенной области
  if (new.bits[DATA_INDEX] != 0) {
    error_code = S21_TOO_LARGE;
  }
  result->value = new;
  result->high_bit = s21_decimal_get_high_bit(result->value);
  return error_code;
}

// предполагает вычитание из большего меньшее число
// возвращает ошибку если было подано вычитание из меньшего большего числа
bit32_t s21_sub_mantis(s21_DecData value_1, s21_DecData value_2,
                       s21_DecData *result) {
  bit_t error_code = S21_SUCCES;
  s21_DecData new = s21_decimal_null_data();
  // инвертируем число
  value_1.value = s21_decimal_invert(value_1.value, COUNT_BLOCKS);
  value_1.high_bit = s21_decimal_get_high_bit(value_1.value);
  // выполняем суммирование
  error_code = s21_add_mantis(value_1, value_2, &new);
  // инвертируем обратно
  new.value = s21_decimal_invert(new.value, COUNT_BLOCKS);
  result->value = new.value;
  result->high_bit = s21_decimal_get_high_bit(result->value);
  return error_code;
}

// умножение представляет сумму числа value_1 с самим собой со сдвигом на
// позицую i-ого бита числа value_2
// возвращает код ошибки от сложения
bit_t s21_mul_mantis(s21_DecData value_1, s21_DecData value_2,
                     s21_DecData *result) {
  s21_DecData new = s21_decimal_null_data();
  bit_t error_code = S21_SUCCES;
  // проверка для наименьшего цикла выполения умножения
  if (value_1.high_bit < value_2.high_bit) {
    for (bit32_t i = 0; i < value_1.high_bit; i++) {
      if (s21_decimal_get_bit(value_1.value, i)) {
        error_code |= s21_add_mantis(new, value_2, &new);
      }
      value_2.value = s21_decimal_lshift(value_2.value);
      value_2.high_bit++;
    }
  } else {
    for (bit32_t i = 0; i < value_2.high_bit; i++) {
      if (s21_decimal_get_bit(value_2.value, i)) {
        error_code |= s21_add_mantis(new, value_1, &new);
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
  bit_t error_code = S21_SUCCES;
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
  bit32_t error_code = S21_SUCCES;
  bit32_t i = 0;
  for (; i < count && error_code == S21_SUCCES; i++) {
    error_code = s21_mul_10(value);
  }
  if (error_code != S21_SUCCES) {
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

bit32_t s21_bank_round_data(s21_DecData *num, s21_DecData divider,
                            s21_DecData residue) {
  bit_t error_code = S21_SUCCES;
  residue.value = s21_decimal_lshift(residue.value);
  residue.high_bit++;
  if (s21_decimal_compare_mantis(residue, divider) != 2 &&
      (s21_decimal_get_bit(num->value, 0) || s21_decimal_is_null(num->value))) {
    s21_DecData new = s21_decimal_null_data();
    new.value.bits[0] = 1;
    new.high_bit = 0;
    error_code = s21_add_mantis(new, *num, num);
  }
  return error_code;
}

bit32_t s21_bank_ten_round_data(s21_DecData *num, s21_DecData residue) {
  bit_t error_code = S21_SUCCES;
  residue.value = s21_decimal_lshift(residue.value);
  residue.high_bit++;
  s21_DecData ten = s21_decimal_null_data();
  ten.value.bits[0] = 10;
  ten.high_bit = s21_decimal_get_high_bit(ten.value);
  if (s21_decimal_compare_mantis(residue, ten) != 2 &&
      (s21_decimal_get_bit(num->value, 0) || s21_decimal_is_null(num->value))) {
    s21_DecData new = s21_decimal_null_data();
    new.value.bits[0] = 1;
    new.high_bit = 0;
    error_code = s21_add_mantis(new, *num, num);
  }
  return error_code;
}

s21_DecData s21_div_10(s21_DecData *value) {
  bit_t error_code = S21_SUCCES;
  s21_DecData ten = s21_decimal_null_data();
  ten.value.bits[0] = 10;
  ten.high_bit = s21_decimal_get_high_bit(ten.value);
  s21_DecData new = s21_decimal_null_data();
  s21_DecData residue = s21_div_mantis(*value, ten, &new);
  value->value = new.value;
  value->high_bit = new.high_bit;
  value->sign = new.sign;
  value->scale--;
  return residue;
}

bit32_t s21_count_div_10(s21_DecData *value, bit32_t count) {
  bit32_t error_code = S21_SUCCES;
  bit32_t i = 0;
  s21_DecData residue;
  for (; i < count && error_code == S21_SUCCES; i++) {
    residue = s21_div_10(value);
    if (!s21_decimal_is_null(residue.value)) {
      error_code = s21_bank_ten_round_data(value, residue);
    }
  }
  return error_code;
}

bit32_t s21_basic_add(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {
  bit32_t error_code = S21_SUCCES;
  s21_normalize(&value_1, &value_2);
  if (value_1.sign == value_2.sign) {
    result->sign = value_1.sign;
    error_code = s21_add_mantis(value_1, value_2, result);
  } else {
    bit32_t result_compare = s21_decimal_compare_mantis(value_1, value_2);
    if (result_compare == 1) {
      error_code = s21_sub_mantis(value_1, value_2, result);
    } else if (result_compare == 2) {
      error_code = s21_sub_mantis(value_1, value_2, result);
    } else {
      *result = s21_decimal_copy_data(value_1);
      result->value = s21_decimal_null();
    }
  }
  if (error_code == S21_SUCCES) {
    error_code = s21_decimal_norm(result);
  } else {
    *result = s21_decimal_null_data();
  }
  return error_code;
}

bit32_t s21_decimal_norm(s21_DecData *result) {
  bit32_t error_code = S21_SUCCES;
  if (result->scale >= MIN_SCALE && result->scale <= MAX_SCALE) {
    if (result->high_bit >= SIZE_MANTIS) {
      bit32_t shift = SIZE_MANTIS - result->high_bit;
      bit32_t count = shift / 3 + (shift % 3 != 0);
      error_code = s21_count_div_10(result, count);
    }
  } else {
    if (result->scale < 0) {
      error_code = s21_count_mul_10(result, -result->scale);
      if (result->value.bits[DATA_INDEX]) {
        error_code = result->sign ? S21_TOO_SMALL : S21_TOO_LARGE;
      }
    } else {
      error_code = s21_count_div_10(result, (result->scale - MAX_SCALE));
    }
  }
  return error_code;
}

// с учетом переполнения
bit32_t s21_basic_sub(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {
  bit32_t error_code = S21_SUCCES;
  s21_normalize(&value_1, &value_2);
  if (value_1.sign == value_2.sign) {
    bit32_t result_compare = s21_decimal_compare_mantis(value_1, value_2);
    if (result_compare == 1) {
      error_code = s21_sub_mantis(value_1, value_2, result);
    } else if (result_compare == 2) {
      error_code = s21_sub_mantis(value_1, value_2, result);
    } else {
      *result = s21_decimal_copy_data(value_1);
      result->value = s21_decimal_null();
    }
  } else {
    error_code = s21_add_mantis(value_1, value_2, result);
    if (error_code != S21_SUCCES) {
      bit32_t shift = result->high_bit - SIZE_MANTIS;
      bit32_t count_div = shift / 3 + (shift % 3 != 0);
      s21_count_div_10(result, count_div);
      result->scale = value_1.scale;
      result->sign = value_1.sign;
    }
  }
  if (error_code == S21_SUCCES) {
    error_code = s21_decimal_norm(result);
  } else {
    *result = s21_decimal_null_data();
  }
  return error_code;
}

void s21_create_residue(s21_DecData *value, s21_DecData *residue,
                        bit32_t count) {
  while (count > 0) {
    s21_mul_10(residue);
    s21_add_mantis(*residue, s21_div_10(value), residue);
    count--;
  }
}

// с учетом переполнения
bit32_t s21_basic_mul(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {
  bit32_t error_code = S21_SUCCES;
  // заполнение результата
  result->scale = value_1.scale + value_2.scale;
  result->sign = value_1.sign || value_2.sign;
  // проверка на результат умножения
  bit32_t result_hight_bit = value_1.high_bit + value_2.high_bit;
  bit32_t excess = result_hight_bit - SIZE_MANTIS;
  bit32_t count_div = excess / 3 + (excess % 3 != 0);
  if (count_div == 0) {
    error_code = s21_mul_mantis(value_1, value_2, result);
    if (error_code != S21_SUCCES) {
      s21_count_div_10(result, (result->high_bit - SIZE_MANTIS) / 3 + 1);
    }
    error_code = s21_decimal_norm(result);
    if (error_code != S21_SUCCES) {
      *result = s21_decimal_null_data();
    }
  } else {
    s21_DecData residue = s21_decimal_null_data();
    if (value_1.high_bit > value_2.high_bit) {
      s21_create_residue(&value_1, &residue, count_div);
      error_code = s21_mul_mantis(residue, value_2, &residue);
      error_code = s21_count_div_10(&residue, count_div);
    } else {
      s21_create_residue(&value_2, &residue, count_div);
      error_code = s21_mul_mantis(residue, value_1, &residue);
      error_code = s21_count_div_10(&residue, count_div);
    }
    error_code = s21_mul_mantis(value_1, value_2, result);
    error_code = s21_add_mantis(*result, residue, result);
    if (error_code != S21_SUCCES) {
      bit32_t shift = result->high_bit - SIZE_MANTIS;
      bit32_t count_div = shift / 3 + (shift % 3 != 0);
      s21_count_div_10(result, count_div);
    }
    error_code = s21_decimal_norm(result);
    if (error_code != S21_SUCCES) {
      *result = s21_decimal_null_data();
    }
  }
  return error_code;
}

// с учетом округления
bit32_t s21_basic_div(s21_DecData value_1, s21_DecData value_2,
                      s21_DecData *result) {
  bit32_t error_code = S21_SUCCES;
  result->scale = value_1.scale - value_2.scale;
  result->sign = value_1.sign || value_2.sign;
  s21_DecData residue = s21_decimal_null_data();
  bit32_t free_bit = SIZE_MANTIS - value_1.high_bit;
  bit32_t count_mul = free_bit / 3 + (free_bit % 3 != 0);
  s21_count_mul_10(&value_1, count_mul);
  residue = s21_div_mantis(value_1, value_2, result);
  free_bit = SIZE_MANTIS - result->high_bit;
  count_mul = free_bit / 3 + (free_bit % 3 != 0);
  s21_count_mul_10(result, count_mul);
  if (result->high_bit > SIZE_MANTIS) {
    free_bit = result->high_bit - SIZE_MANTIS;
    count_mul = free_bit / 3 + (free_bit % 3 != 0);
    s21_count_div_10(result, count_mul);
    count_mul--;
  }
  s21_count_mul_10(&residue, count_mul);
  if (residue.high_bit > SIZE_MANTIS) {
    free_bit = residue.high_bit - SIZE_MANTIS;
    count_mul = free_bit / 3 + (free_bit % 3 != 0);
    s21_count_div_10(&residue, 1);
  }
  s21_DecData residue_2 = s21_div_mantis(residue, value_2, &residue);
  s21_bank_round_data(&residue, value_2, residue_2);
  if (s21_add_mantis(*result, residue, result)) {
    free_bit = result->high_bit - SIZE_MANTIS;
    count_mul = free_bit / 3 + (free_bit % 3 != 0);
    s21_count_div_10(result, count_mul);
  }
  error_code = s21_decimal_norm(result);
  if (error_code != S21_SUCCES) {
    *result = s21_decimal_null_data();
  }
  return error_code;
}
