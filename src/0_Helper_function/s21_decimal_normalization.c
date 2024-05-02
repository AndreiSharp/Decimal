
int exp_plus(s21_decimal *value_1, int count) {
  s21_arithmetic_result_t flag = S21_ARITHMETIC_OK;
  // Узнаем знак числа
  int sign = s21_decimal_sign(*value_1);
  // Берем модуль числа
  *value_1 = s21_decimal_abs(*value_1);
  // Сдвигаем третий блок на 15 позиций
  (*value_1).bits[DATA_INDEX] >>= EXP_POS_L - 1;
  // Увеличиваем экспонент до нужной суммы
  (*value_1).bits[DATA_INDEX] += count;
  // Проверяем на допустимые пределы
  if ((*value_1).bits[DATA_INDEX] > 28) {
    flag = S21_ARITHMETIC_SMALL;
  }
  // Сдвигаем третий блок на 15 позиций обратно
  (*value_1).bits[DATA_INDEX] <<= EXP_POS_L - 1;
  // Возращаем знак числа
  *value_1 = s21_decimal_set_bit(*value_1, SIGN_POS, sign);
  return flag;
}

s21_decimal s21_mul10(s21_decimal value) {
  s21_decimal res;
  res.bits[0] = 0;
  res.bits[1] = 0;
  res.bits[2] = 0;
  res.bits[3] = value.bits[3];
  int flag = 0;
  for (int i = 1; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_get_bit(value, i - 1);
    res = s21_decimal_set_bit(res, i, flag);
  }
  for (int i = 3; i < SIZE_MANTIS; i++) {
    flag =
        s21_decimal_get_bit(res, i) + s21_decimal_get_bit(value, i - 3) + flag;
    res = s21_decimal_set_bit(res, i, flag % 2);
    flag = flag / 2;
  }
  return res;
}

void s21_count_mul10(s21_decimal *value, int count) {
  for (int i = 0; i < count; i++) {
    // Умножение мантисы на 10
    *value = s21_mul10(*value);
  }
}

int s21_normalization(s21_decimal *value_1, s21_decimal *value_2,
                      s21_decimal *res) {
  s21_arithmetic_result_t flag = S21_ARITHMETIC_OK;
  int exp_1 = s21_decimal_exp(*value_1);
  int exp_2 = s21_decimal_exp(*value_2);
  if (exp_1 > exp_2) {
    // Умножение на 10 числителя и знаменателя
    s21_count_mul10(value_2, exp_1 - exp_2);
    // Увеличение экспонента
    flag = exp_plus(value_2, exp_1 - exp_2);
  } else if (exp_2 > exp_1) {
    // Умножение на 10 числителя и знаменателя
    flag = s21_count_mul10(value_1, exp_2 - exp_1);
    // Увеличение экспонента
    flag = exp_plus(value_1, exp_2 - exp_1);
  }
  // Приравнивание экспонента результата к получившимуся общему экспоненту
  (*res).bits[3] = (*value_1).bits[3];
  return flag;
}
