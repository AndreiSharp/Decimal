#include <stdio.h>
#include <stdint.h>

/*--------------------------------CONST---------------------------------*/

#define MAX_BLOCKS 4       // count of bits
#define MAX_BIT_BLOCKS 96  // count of bits in one block
#define SIZE_BLOCK 32      // size of one block
#define DATA_INDEX 3    // index of bits where exponent and sign of s21_decimal
#define EXP_POS_L 16    // left positon of exponent in bits[DATA_INDEX]
#define EXP_POS_R 23    // right positon of exponent in bits[DATA_INDEX]
#define SIGN_POS 31     // position of s21_decimal sign in bits[DATA_INDEX]
#define NO_BIT_VALUE 2  // not 1 or 2
#define SIZE_MANTIS 95
/*--------------------------------STRUCT--------------------------------*/

typedef uint8_t bit_t;  // 1 or 0
typedef uint32_t
    bit32_t;  // 32 bit in bits[i], bits[i] - one block in s21_decimal

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

typedef struct {
  bit32_t bits[MAX_BLOCKS];
} s21_decimal;

int s21_set_bit(int number, int index) { return number | (0b1 << index); }

int s21_get_bit(int number, int index) {
  // return 0b1 & (number >> index);
  return ((0b1 << index) & number) >> index;
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

int exp_plus (s21_decimal *value_1, int count) {
 s21_arithmetic_result_t flag = S21_ARITHMETIC_OK;
  //Узнаем знак числа
int sign = s21_decimal_sign(*value_1);
//Берем модуль числа
*value_1 = s21_decimal_abs(*value_1);
//Сдвигаем третий блок на 15 позиций
(*value_1).bits[DATA_INDEX] >>= EXP_POS_L - 1;
//Увеличиваем экспонент до нужной суммы
(*value_1).bits[DATA_INDEX] += count;
//Проверяем на допустимые пределы
if ((*value_1).bits[DATA_INDEX] > 28) {flag = S21_ARITHMETIC_SMALL;}
//Сдвигаем третий блок на 15 позиций обратно
(*value_1).bits[DATA_INDEX] <<= EXP_POS_L - 1;
//Возращаем знак числа
*value_1 = s21_decimal_set_bit( *value_1, SIGN_POS, sign);
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
    flag = s21_decimal_get_bit(value, i-1);
    res = s21_decimal_set_bit(res, i, flag);
  }
  for (int i = 3; i < SIZE_MANTIS; i++) {
    flag = s21_decimal_get_bit(res, i) +
           s21_decimal_get_bit(value, i-3) + flag;
    res = s21_decimal_set_bit(res, i, flag % 2);
    flag = flag / 2;
  }
  return res;
}

int s21_count_mul10(s21_decimal *value, int count) {
  for (int i = 0; i < count; i++) {
    //Умножение мантисы на 10
    *value = s21_mul10(*value);
  }
  return 0;
}

int s21_normalization(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *res) {
s21_arithmetic_result_t flag = S21_ARITHMETIC_OK;
int exp_1 = s21_decimal_exp(*value_1);
int exp_2 = s21_decimal_exp(*value_2);
if (exp_1 > exp_2) {
//Умножение на 10 числителя и знаменателя 
s21_count_mul10(value_2, exp_1 - exp_2);
//Увеличение экспонента
flag = exp_plus (value_2, exp_1 - exp_2);
}
else if (exp_2 > exp_1) {
  //Умножение на 10 числителя и знаменателя 
flag = s21_count_mul10(value_1, exp_2 - exp_1);
//Увеличение экспонента
flag = exp_plus (value_1, exp_2 - exp_1);
}
//Приравнивание экспонента результата к получившимуся общему экспоненту
(*res).bits[3] = (*value_1).bits[3];
  return flag;
}

int s21_add_two_mantis (s21_decimal value_1, s21_decimal value_2, s21_decimal *res) {
  int flag = 0;
  int a = 0;
  int b = 0;
  for (int i = 0; i < SIZE_MANTIS; i++) {
      // printf("%d!!!!!\n", (*res).bits[0]);
      a = s21_decimal_get_bit(value_1, i);
      b = s21_decimal_get_bit(value_2, i);
    flag = a + b + flag;
           printf("flag = %d, a = %d, b = %d, index = %d!!!!\n", flag, a, b, i);
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
}
else if (sign_value1 == 1 && sign_value2 == 1){
   //Нормализация Экспонента
flag = s21_normalization(&value_1, &value_2, result);
  //Сложение мантис
flag = s21_add_two_mantis(value_1, value_2, result);
}



return flag; 
}


int main() {
  s21_decimal decimal;
  s21_decimal decimal2;
  s21_decimal decimal3;
  decimal.bits[0] = 0b00000000000000000000000000000001;
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[3] = 0b10000000000000010000000000000000;
  decimal2.bits[0] = 0b00000000000000000000000000000001;
  decimal2.bits[1] = 0b00000000000000000000000000000000;
  decimal2.bits[2] = 0b00000000000000000000000000000000;
  decimal2.bits[3] = 0b10000000000000001000000000000000;
  decimal3.bits[0] = 0b00000000000000000000000000000000;
  decimal3.bits[1] = 0b00000000000000000000000000000000;
  decimal3.bits[2] = 0b00000000000000000000000000000000;
  decimal3.bits[3] = 0b00000000000000000000000000000000;
  
  s21_add(decimal, decimal2, &decimal3);
  
  printf ("%d\n", decimal.bits[0]);
  printf ("%d\n", decimal2.bits[0]);
  printf ("%d\n", decimal3.bits[0]);
  printf ("\n");
int exp_1 = s21_decimal_exp(decimal);
int exp_2 = s21_decimal_exp(decimal2);
int exp_3 = s21_decimal_exp(decimal3);

  printf ("%d\n", exp_1);
  printf ("%d\n", exp_2);
  printf ("%d\n", exp_3);
  printf ("\n");

int sign_1 = s21_decimal_sign(decimal);
int sign_2 = s21_decimal_sign(decimal2);
int sign_3 = s21_decimal_sign(decimal3);
printf ("\n");printf ("\n");
  printf ("%d\n", sign_1);
  printf ("%d\n", sign_2);
  printf ("%d\n", sign_3);

}
