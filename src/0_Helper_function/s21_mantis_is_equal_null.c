#include "../include/s21_decimal.h"
/**
 * @brief check that mantis is null
 * @author "yrelcary"
 * @param decimal value where checking for equal null
 * @return result of compare mantis with null
 */

int s21_mantis_is_equal_null (s21_decimal decimal) {
  return !(decimal.bits[0] || decimal.bits[1] || decimal.bits[2]);
}