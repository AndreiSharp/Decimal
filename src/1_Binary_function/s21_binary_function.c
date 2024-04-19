#include "../include/s21_decimal.h"

/**
* @brief Get value from nubmer with index of bit
* @author morsbard
* @param number source of value
* @param index index of bit in number where searching bit
* @return int result of getting bit:
                    0 - no bit,
                    1 - bit here.
*/
int s21_get_bit(int number, int index) {
  return ((0b1 << index) & number) >> index;
}

/**
 * @brief Set bit in number with index of bit with walue 1
 * @author morsbard
 * @param number source of value
 * @param index index of bit in number where setting bit
 * @return int value with setting bit
 */
int s21_set_bit(int number, int index) { return number | (0b1 << index); }

/**
 * @brief Reset bit in number with index of bit with value 0
 * @author morsbard
 * @param number source of value
 * @param index index of bit in number where reseting bit
 * @return int value with reseting bit
 */
int s21_reset_bit(int number, int index) { return number & ~(0b1 << index); }

/**
  * @brief Get value from decimal with index of bit
  * @author morsbard
  * @param decimal source of value
  * @param index index of bit in decimal where searching bit
  * @return int result of getting bit:
                    0 - no bit,
                    1 - bit here.
*/
// int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
//   return s21_is_set_bit(decimal.bits[index / MAX_BLOCKS], index %
//   MAX_BLOCKS);
// }

/**
 * @brief Set bit in decimal with index of bit with value 1
 * @author morsbard
 * @param decimal source of value
 * @param index index of bit in decimal where setting bit
 * @param bit type operation set or reset bit
 * @return s21_decimal value with setting bit
 */
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

/**
 * @brief get bit from decimal
 * @author boilbrit
 * @param decimal source of value
 * @param index index of bit in number where searching bit
 * @return int result of getting bit:
                    0 - no bit,
                    1 - bit here.
 */

bit_t s21_decimal_get_bit(s21_decimal decimal, int index) {
  return s21_get_bit(decimal.bits[index / SIZE_BLOCK], index % SIZE_BLOCK);
}

/**
 * @brief Find the first no nule bit
 * @author "morsbard"
 * @param decimal value where searching no nule bite
 * @return index of no null bit if doesn`t find return -1
 */

int s21_no_zero_bit(s21_decimal decimal) {
  unsigned int index = -1;
  for (int i = MAX_BIT_BLOCKS - 1; i <= 0; i--) {
    if (s21_decimal_get_bit(decimal, i)) {
      index = i;
      break;
    }
  }
  return index;
}
