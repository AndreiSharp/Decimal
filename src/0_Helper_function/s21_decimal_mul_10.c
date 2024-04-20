#include "../include/s21_decimal_help.h"

/**
 * @brief multiply a decimal and 10
 * @author boilbrit
 * @param decimal source of value
 * @return results of multiplying 10 and decimal
 */

// s21_decimal s21_decimal_mul_10(s21_decimal decimal) {
//   s21_decimal result;
//   s21_decimal_copy(decimal, &result);

//   bit_t rem = 0;
//   for (int i = 0; i < MAX_BIT_BLOCKS * (MAX_BLOCKS - 1); ++i) {
//     bit_t right1 = 0, right3 = 0;
//     if (i > 0) {
//       right1 = s21_decimal_get_bit(decimal, i - 1);
//     }
//     if (i > 2) {
//       right3 = s21_decimal_get_bit(decimal, i - 3);
//     }

//     s21_decimal_set_bit(decimal, i, (right1 + right3 + rem) % 2);

//     rem = (right1 + right3 + rem) / 2;
//   }

//   return result;
// }