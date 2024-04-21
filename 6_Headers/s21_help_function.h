#ifndef S21_HELP_FUNCTION
#define s21_HELP_FUNCTION

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_types.h"

/*------------------------Arithmetic_help_function-----------------------*/

/**
 * @brief Get sign of s21_decimal
 * @author boilbrit
 * @param decimal source of value
 * @return int s21_decimal sign
 */
int s21_get_sign(s21_decimal decimal);

/**
 * @brief Get absolute value of s21_decimal
 * @author boilbrit
 * @param decimal source of value
 * @return s21_decimal absolute value
 */
s21_decimal s21_decimal_abs(s21_decimal decimal);

/**
 * @brief Get value of degree indicator
 * @author morsbard
 * @param value decimal where searching degree indicator
 * @return int result
 */
int s21_get_exp(s21_decimal value);

int s21_decimal_add_exp(s21_decimal *value, int count);

int s21_decimal_sub_exp(s21_decimal *value, int count);

/**
 * @brief sum two mantis
 * @author morsbard
 * @param value_1 first summand
 * @param value_2 first summand
 * @param res pointer to decimal number that result of sum two mantis
 * @return decimal number that result of sum two mantis
 */
int s21_add_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res);

/**
 * @brief subtraction of two mantis
 * @author morsbard
 * @param value_1 diminutive
 * @param value_2 deductible
 * @param res pointer to decimal number of residual
 * @return the code of the function execution:
 *      0 - SUCSESS
 *      1 - ERROR
 */
int s21_sub_two_mantis(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *res);
/*------------------------Compare_help_function-----------------------*/

/*---------------Convertation_and_parsers_help_function---------------*/

/*-------------------Anouther_function_help_function------------------*/

/*------------------------Decimal_help_function-----------------------*/

/**
 * @brief initialization s21_decimal
 * @author "boilbrit"
 * @param decimal source of value
 * @return result of initialization
 */
unsigned int s21_decimal_init(s21_decimal *decimal);

/**
 * @brief copy decimal from src to dest
 * @author boilbrit
 * @param src source of value (from)
 * @param dest source of value (to)
 * @return decimal copy from src
 */
unsigned int s21_decimal_copy(s21_decimal src, s21_decimal *dest);

/**
 * @brief copy decimal from src to dest
 * @author boilbrit
 * @param src source of value (from)
 * @param dest source of value (to)
 * @return decimal copy from src
 */
unsigned int s21_check_normalization(s21_decimal value_1, s21_decimal value_2);

unsigned int s21_normalization(s21_decimal *value_1, s21_decimal *value_2);

/**
 * @brief sub prefix of first n bin digits in decimal and 10
 * @author "boilbrit"
 * @param bit_t prefix[] first few bits in decimal
 * @param bit_t n count of bits
 * @return int sub prefix of first n bin digits in decimal and 10
 */
static int s21_get_sub_10(bit_t prefix[], size_t n);

/**
 * @brief sub to binary
 * @author "boilbrit"
 * @param bit_t prefix[] first few bits in decimal
 * @param bit_t n count of bits
 * @param unsigned int sub prefix of sub
 * @return static bit_t[] new prefix
 */
static bit_t *s21_sub_to_bin(bit_t prefix[], size_t n, unsigned int sub);

/**
 * @brief division decimal by 10
 * @author "boilbrit"
 * @param decimal source of value
 * @return division decimal by 10
 */
s21_decimal s21_decimal_div_10(s21_decimal decimal);

s21_decimal s21_mul10(s21_decimal value);

unsigned int s21_count_mul10(s21_decimal *value, int count);
#endif