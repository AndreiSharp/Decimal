#ifndef S21_HELP_FUNCTION
#define s21_HELP_FUNCTION

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_types.h"

/*----------------------------Help_function-----------------------------*/

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
int s21_take_exp(s21_decimal value);

/**
 * @brief Get sign of s21_decimal
 * @author boilbrit
 * @param decimal source of value
 * @return int s21_decimal sign
 */

int s21_take_sign(s21_decimal decimal);

/**
 * @brief copy decimal from src to dest
 * @author boilbrit
 * @param src source of value (from)
 * @param dest source of value (to)
 * @return decimal copy from src
 */
s21_decimal s21_decimal_copy(s21_decimal src, s21_decimal *dest);

/**
 * @brief Get absolute value of s21_decimal
 * @author boilbrit
 * @param decimal source of value
 * @return s21_decimal absolute value
 */

s21_decimal s21_decimal_abs(s21_decimal decimal);

#endif