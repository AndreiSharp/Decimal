#ifndef S21_BINARY
#define S21_BINARY

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_decimal_types.h"

/*----------------------------Bimary function---------------------------*/

/**
* @brief Get value from nubmer with index of bit
* @author morsbard
* @param numer source of value
* @param index index of bit in number where searching bit
* @return int result of getting bit:
                    '0' - no bit,
                    '1' - bit here.
*/
int s21_get_bit(int number, int index);

/**
 * @brief Set bit in number with index of bit with walue 1
 * @author morsbard
 * @param number source of value
 * @param index index of bit in number where setting bit
 * @return int value with setting bit
 */
int s21_set_bit(int number, int index);

/**
 * @brief Reset bit in number with index of bit with value 0
 * @author morsbard
 * @param number source of value
 * @param index index of bit in number where reseting bit
 * @return int value with reseting bit
 */
int s21_reset_bit(int number, int index);

/**
  * @brief Get value from decimal with index of bit
  * @author morsbard
  * @param decimal source of value
  * @param index index of bit in decimal where searching bit
  * @return int result of getting bit:
                    '0' - no bit,
                    '1' - bit here.
*/
int s21_decimal_is_set_bit(s21_decimal decimal, int index);

/**
 * @brief Set bit in decimal with index of bit with walue 1
 * @author morsbard
 * @param decimal source of value
 * @param index index of bit in decimal where setting bit
 * @param bit type operation set or reset bit
 * @return s21_decimal value with setting bit
 */
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index, int bit);

/*
 * @brief Find the first no nule bit
 * @author "morsbard"
 * @param decimal value where searching no nule bite
 * @return index of no null bit if doesn`t find return -1
 */
int s21_no_zero_bit(s21_decimal decimal);

/**
 * @brief check that decimal is null
 * @author "morsbard"
 * @param decimal value where checking for equal null
 * @return result of compare decimal with null
 */
int s21_is_equal_null(s21_decimal decimal);

/**
 * @brief compare two decimal
 * @author "morsbard"
 * @param decimal1 first comparing decimal
 * @param decimal2 second comparing decimal
 * @return result of comparing decimal1 with decimal2:
 *               '-1' - if decimal2 more then decimal1;
 *                '0' - if decimal1 equal decimal2;
 *                '1' - if decimal1 moe then decimal2.
 */
int s21_binary_compare(s21_decimal decimal1, s21_decimal decimal2);

int s21_get_index_high_bit(s21_decimal value);
#endif