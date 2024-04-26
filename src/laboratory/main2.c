#include <stdint.h>
#include <stdio.h>

/*--------------------------------CONST---------------------------------*/

#define MAX_BLOCKS 4      // count of bits
#define MAX_BIT_BLOCKS 96 // count of bits in one block
#define SIZE_BLOCK 32     // size of one block
#define DATA_INDEX 3   // index of bits where exponent and sign of s21_decimal
#define EXP_POS_L 16   // left positon of exponent in bits[DATA_INDEX]
#define EXP_POS_R 23   // right positon of exponent in bits[DATA_INDEX]
#define SIGN_POS 31    // position of s21_decimal sign in bits[DATA_INDEX]
#define NO_BIT_VALUE 2 // not 1 or 2
#define SIZE_MANTIS 95
#define TRUE 1
#define FALSE 0
/*--------------------------------STRUCT--------------------------------*/

typedef uint8_t bit_t; // 1 or 0
typedef uint32_t
    bit32_t; // 32 bit in bits[i], bits[i] - one block in s21_decimal

/* main struct of decimal:
  in 0 bit [0..31] contain low bits of 96-bit integer
  in 1 bit [32..63] contain middle bits of 96-bit integer
  in 2 bit [64..95] contain high bits of 96-bit integer
  in 3 bit :
    [0..15] - the lower word, are unused and must be zero.
    [16..23] - contain an exponent between 0 and 28, which indicates the power
               of 10 to divide the integer number
    [24..30] - unused and must be zero
    [31] - contains the sign
*/

typedef enum {
  S21_ARITHMETIC_OK = 0,
  S21_ARITHMETIC_BIG = 1,
  S21_ARITHMETIC_SMALL = 2,
  S21_ARITHMETIC_ZERO_DIV = 3,
  S21_ARITHMETIC_ERROR = 4
} s21_arithmetic_result_t;

enum POSITIONS {
  DECIMAL_EXP_POS_L = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_L - 1,
  DECIMAL_EXP_POS_R = (MAX_BLOCKS - 1) * SIZE_BLOCK + EXP_POS_R - 1,
};

typedef struct {
  bit32_t bits[MAX_BLOCKS];
} s21_decimal;

int s21_set_bit(int number, int index) { return number | (0b1 << index); }

int s21_get_bit(int number, int index) {
  // return 0b1 & (number >> index);
  // printf ("%d???\n", ((0b1 << index) & number) >> index);
  // printf ("%d|||||\n", number);
  return ((1U << index) & number) >> index;
}

int s21_reset_bit(int number, int index) { return number & ~(0b1 << index); }

int s21_decimal_sign(s21_decimal decimal) {
  return 0b1 & (decimal.bits[DATA_INDEX] >> SIGN_POS);
}

s21_decimal s21_decimal_abs(s21_decimal decimal) {
  decimal.bits[DATA_INDEX] = s21_reset_bit(decimal.bits[DATA_INDEX], SIGN_POS);
  return decimal;
}

int s21_decimal_exp(s21_decimal decimal) {
  if (s21_decimal_sign(decimal)) {
    decimal = s21_decimal_abs(decimal);
  }
  decimal.bits[DATA_INDEX] >>= EXP_POS_L - 1;

  return decimal.bits[DATA_INDEX];
}

s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index, int bit) {
  if (bit == 0) {
    decimal.bits[index / SIZE_BLOCK] =
        s21_reset_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  } else {
    decimal.bits[index / SIZE_BLOCK] =
        s21_set_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
  }
  return decimal;
}

bit_t s21_decimal_get_bit(s21_decimal decimal, int index) {
  return s21_get_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
}

int exp_plus(s21_decimal *value_1, int count) {
  s21_arithmetic_result_t flag = S21_ARITHMETIC_OK;

  int sign = s21_decimal_sign(*value_1); //Узнаем знак числа

  *value_1 = s21_decimal_abs(*value_1); //Берем модуль числа

  (*value_1).bits[DATA_INDEX] >>=
      EXP_POS_L - 1; //Сдвигаем третий блок на 15 позиций

  (*value_1).bits[DATA_INDEX] += count; // Увеличиваем экспонент до нужной суммы
  if ((*value_1).bits[DATA_INDEX] > 28) {
    flag = S21_ARITHMETIC_SMALL;
  } else {
    (*value_1).bits[DATA_INDEX] <<=
        EXP_POS_L - 1; //Сдвигаем третий блок на 15 позиций обратно
  } //Проверяем на допустимые пределы
  *value_1 = s21_decimal_set_bit(*value_1, 127, sign); //Возращаем знак числа
  return flag;
}
int s21_no_zero_bit(s21_decimal decimal) {
  unsigned int index = -1;
  for (int i = SIZE_MANTIS - 1; i >= 0; i--) {
    if (s21_decimal_get_bit(decimal, i) == 1) {
      index = i;
      break;
    }
  }
  return index;
}

s21_decimal s21_decimal_init(s21_decimal *decimal) {
  // s21_from_int_to_decimal(decimal, 0);

  for (int i = 0; i < MAX_BLOCKS; ++i) {
    (*decimal).bits[i] = 0b00000000000000000000000000000000;
  }

  *decimal = s21_decimal_set_bit(*decimal, DECIMAL_EXP_POS_L, 1);

  return *decimal;
}

/**
 * @brief sub prefix of first n bin digits in decimal and 10
 * @author "boilbrit"
 * @param bit_t prefix[] first few bits in decimal
 * @param bit_t n count of bits
 * @return int sub prefix of first n bin digits in decimal and 10
 */
static int s21_get_sub_10(bit_t prefix[], size_t n) {
  unsigned int prefix10 = 0;
  for (int i = 0, pow = 1 << (n - 1); i < (int)n; ++i, pow >>= 1) {
    prefix10 += prefix[i] * pow;
  }
  return prefix10 - 10;
}

/**
 * @brief sub to binary
 * @author "boilbrit"
 * @param bit_t prefix[] first few bits in decimal
 * @param bit_t n count of bits
 * @param unsigned int sub prefix of sub
 * @return static bit_t[] new prefix
 */
static bit_t *s21_sub_to_bin(bit_t prefix[], size_t n, unsigned int sub) {
  for (int i = 0, pow = 1 << (n - 1); i < (int)n; ++i, pow >>= 1) {
    prefix[i] = sub / pow;
    sub %= pow;
  }
  return prefix;
}

/**
 * @brief division decimal by 10
 * @author "boilbrit"
 * @param decimal source of value
 * @return division decimal by 10
 */
s21_decimal s21_decimal_div_10(s21_decimal decimal) {
  s21_decimal result;
  s21_decimal_init(&result);
  result.bits[3] = decimal.bits[3];
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

int s21_decimal_is_equal_null(s21_decimal decimal) {
  return !(decimal.bits[0] || decimal.bits[1] || decimal.bits[2] ||
           decimal.bits[3]);
}

int s21_mantis_is_equal_null(s21_decimal decimal) {
  return !(decimal.bits[0] || decimal.bits[1] || decimal.bits[2]);
}

void change_sign_if_zero(s21_decimal *value) {
  int check_zero = s21_mantis_is_equal_null(*value);
  printf("%d", check_zero);
  if (check_zero == 1) {
    *value = s21_decimal_set_bit(*value, 127, 0);
  }
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0; //// добавить ошибки при вычислении (если переменные не по
                ///формату и тп)
  int exp = s21_decimal_exp(value);
  for (int i = exp; i > 0; i--) {
    value = s21_decimal_div_10(value);
    exp_plus(&value, -1);
  }
  *result = value;
  change_sign_if_zero(result);
  return flag;
}

/ int s21_add_two_mantis(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *res) {
  int flag = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_get_bit(value_1, i) + s21_decimal_get_bit(value_2, i) +
           flag;
    *res = s21_decimal_set_bit(*res, i, flag % 2);
    flag = flag / 2;
  }
  return flag; // изменить
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_result_t flag = S21_ARITHMETIC_OK;

  int sign_value1 = s21_decimal_sign(value_1);
  int sign_value2 = s21_decimal_sign(value_2);

  if (sign_value1 == 0 && sign_value2 == 0) {
    //Нормализация Экспонента
    flag = s21_normalization(&value_1, &value_2, result);
    //Сложение мантис
    flag = s21_add_two_mantis(value_1, value_2, result);
  } else if (sign_value1 == 1 && sign_value2 == 1) {
    //Нормализация Экспонента
    flag = s21_normalization(&value_1, &value_2, result);
    //Сложение мантис
    flag = s21_add_two_mantis(value_1, value_2, result);
  }
  return flag;
}

int s21_sub_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res) {
  int flag = 0;
  int res_div = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
    res_div =
        s21_decimal_is_set_bit(value_1, i) - s21_decimal_is_set_bit(value_2, i);
    if (res_div - flag >= 0) {
      *res = s21_decimal_set_bit(*res, i, res_div + flag);
      flag = 0;
    } else {
      flag = 1;
      *res = s21_decimal_set_bit(*res, i, 1);
    }
  }
  return flag;
}
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int flag = S21_SUCCES;
  int sign_value1 = s21_take_sign(value_1);
  int sign_value2 = s21_take_sign(value_2);
  if (sign_value1 == sign_value2) {
    if (s21_is_less(value_1, value_2)) {
      flag = s21_sub_two_mantis(value_1, value_2);
    } else {
      flag = s21_sub_two_mantis(value_2, value_1);
    }
  } else {
    flag = s21_normalization(&value_1, &value_2, result);
    if (flag) {
      flag = s21_add_two_mantis(value_1, value_2, result);
    }
  }
  return flag;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 0; // для возврата
  //добавить проверку на корректность децимала
  s21_decimal_init(result);
  (*result).bits[3] = value.bits[3];
  change_sign_if_zero(result);
  int sign = s21_decimal_sign(value);
  flag = s21_truncate(value, result);
  if (sign == 1) {
    s21_decimal bufer;
    s21_decimal_init(&bufer);
    flag = s21_sub(value, result, &bufer);
    if (s21_mantis_is_equal_null(bufer) != 1) {
      s21_decimal_init(&bufer);
      bufer.bits[0] = 0b0000000000000000000000000000001;
      flag = s21_add(result, bufer, *result);
    }
  }
  return flag;
}

int main() {
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  decimal.bits[0] = 0b00000000000000000001000000000000;
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[3] = 0b10000000000000010000000000000000;
  decimal2.bits[0] = 0b00000000000000000000000000000001;
  decimal2.bits[1] = 0b00000000000000000000000000000000;
  decimal2.bits[2] = 0b00000000000000000000000000000000;
  decimal2.bits[3] = 0b00000000000000010000000000000000;
  decimal3.bits[0] = 0b00000000000000000000000000000000;
  decimal3.bits[1] = 0b00000000000000000000000000000000;
  decimal3.bits[2] = 0b00000000000000000000000000000000;
  decimal3.bits[3] = 0b00000000000000000000000000000000;

  // s21_add(decimal, decimal2, &decimal3);

  printf("number - %d\n", decimal.bits[0]);
  // printf("%d\n", decimal2.bits[0]);
  // printf("%d\n", decimal3.bits[0]);
  // printf("\n");
  int exp_1 = s21_decimal_exp(decimal);
  // int exp_2 = s21_decimal_exp(decimal2);
  // int exp_3 = s21_decimal_exp(decimal3);

  printf("exp1 - %d\n", exp_1);
  // printf("%d\n", exp_2);
  // printf("%d\n", exp_3);
  // printf("\n");

  int sign_1 = s21_decimal_sign(decimal);
  // int sign_2 = s21_decimal_sign(decimal2);
  // int sign_3 = s21_decimal_sign(decimal3);
  // printf("\n");
  printf("sign - %d\n", sign_1);
  // printf("%d\n", sign_2);
  // printf("%d\n", sign_3);
  printf("\n");
  s21_floor(decimal, &decimal3);

  printf("new number - %d\n", decimal3.bits[0]);
  int exp_3 = s21_decimal_exp(decimal3);
  printf("exp_result - %d\n", exp_3);
  int sign_3 = s21_decimal_sign(decimal3);
  printf("sign - %d\n", sign_3);
  return 0;
}
