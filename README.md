# **Decimal**

## **Contens**

1. [Creators](##Creators)
2. [Description](##Description)
3. [Main function](#main-function) \
    3.1. [Arithmetic function](#arithmetic-function) \
        3.1.1. [Sum of two decimals](#sum-of-two-decimals) \
        3.1.2. [Subtraction of two decimals](#subtraction-of-two-decimals) \
        3.1.3. [Multiplication of two decimals](#multipliction-of-two-decimals) \
        3.1.4. [Division of two decimals](#division-of-two-decimals) \
    3.2. [Comprasion operators](#compresion-operators) \
        3.2.1. [Greater of equal](#greater-or-equal) \
        3.2.2. [Greater](#greater) \
        3.2.3. [Less or eqaul](#less-or-equal)\
        3.2.4. [Less](#less) \
        3.2.5. [Not equal](#not-equal)\
    3.3 [Convertation and parsers](#convertation-and-parsers) \
        3.3.1. [From decimal to float](#from-decimal-to-float) \
        3.3.2. [From decimal to int](#from-decimal-to-int)\
        3.3.3. [From float to decimal](#from-float-to-decimal) \
        3.3.4 [From int to decimal](#from-int-to-decimal) \
    3.4 [Anouther function](#anouther-function) \
        3.4.1. [Floor](#floor) \
        3.4.2. [Negate](#negate) \
        3.4.3. [Round](#round) \
        3.4.4. [truncate](#trancate)
4. [Help function](#help-function)

## **Creators**

Данный проект реализован группой **`2BRYM`**.

## **Description**

Задачей являлось разработка библиотеки (`s21_decimal.a`) на языке си структуры хранания больших чисел decimal.

Проект разбит на отдельные библиотеки основных и вспомогательных функций.

## **Main function**

### **Arithmetic function**

Данный модуль представляет собой совокупность функций арифметических операций над `decimal`:

a. [Sum of two decimals](#sum-of-two-decimals) \
b. [Subtraction of two decimals](#subtraction-of-two-decimals)\
c. [Multipliction of two decimals](#multipliction-of-two-decimals)\
d. [Division of two decimals](#division-of-two-decimals)

#### **Sum of two decimals**

`unsigned int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)`

Данная функция предназначена для сложения двух `decimal` чисел. Возвращаемое значение - код выполения программы.

Функция использует следующие подфункции:

* [Decimal correct](#decimal-correct);
* [Normalization](#normalization);
* [Get sign](#get-sign);
* [Add two mantis](#add-two-mantis);
* [Greater mantis](#less-mantis);
* [Subtracion of two mantis](#subtracion-of-two-mantis).

#### **Subtraction of two decimals**

Заглавие фунции:

> unsigned int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

Данная функция предназначена для вычитания двух `decimal` чисел. Возвращаемое значение - код выполнения программы.

Функция использует следующие подфункции:

* [`Decimal correct`](#decimal-correct);
* [`Normalization`](#normalization);
* [`Get sign`](#get-sign);
* [`Add two mantis`](#add-two-mantis);
* [`Less mantis`](#less-mantis);
* [`Subtracion of two mantis`](#subtracion-of-two-mantis).

#### **Multipliction of two decimals**

Заглавие функции:

> unsigned int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

Данная функция предназначена для умножения двух `decimal` чисел. Возвращаемое значение - код выполнения программы.

Функция использует следующие подфункции:


#### **Division of two decimals**

Заглавие функции:

> unsigned int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

Данная функция предназначена для умножения
двух `decimal` чисел. Возвращаемое значение - код выполнения программы.

Функция использует следующие подфункции:

***

### **Compresion operators**

Данный модуль представляет собой совокупность функций сравния двух `decimal` чисел

#### **Equal**

Заглавие функции:

> unsigned int s21_is_equal(s21_decimal value_1, s21_decimal value_2)

Функция использует подфункцию [`Is set bit`](#is-set-bit).

#### **Greater or equal**

Заглавие функции:

> unsigned int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2)

Функция использует подфункцию [`Fucntion compare`](#function-compare).

#### **Greater**

Заглавие функции:

> usigned int s21_is_greater(s21_decimal value_1, s21_decimal value_2)

Функция использует подфункцию [`Fucntion compare`](#function-compare).

#### **Less or equal**

Заглавие функции:

> unsigned int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2)

Функция использует подфункцию [`Fucntion compare`](#function-compare).

#### **Less**

Заглавие функции:

> unsigned int s21_is_less(s21_decimal value_1, s21_decimal value_2)

Функция использует подфункцию [`Fucntion compare`](#function-compare).

#### **Not equal**

> unsigned int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2)

Функция использует подфункцию [`Is set bit`](#is-set-bit).

***

### **Convertation and parsers**

#### **From decimal to float**

Заглавие функции:

> unsigned int s21_from_decimal_to_float()

Функция использует следующие подфункции:


#### **From decimal to int**

Заглавие функции:

> unsigned int s21_from_decimal_to_int()

Функция использует следующие подфункции:

#### **From float to decimal**

Заглавие функции:

> unsigned int s21_from_float_to_decimal()

Функция использует следующие подфункции:

#### **From int to decimal**

Заглавие функции:

> unsigned int s21_from_int_to_decimal()

Функция использует следующие подфункции:

***

### **Anouther function**

#### **Floor**

Заглавие функции:

> unsigned int s21_floor(s21_decimal value, s21_decimal *result)

Функция использует следующие подфункции:

#### **Negate**

Заглавие функции:

> unsigned int s21_negate(s21_decimal value, s21_decimal *result)

Функция использует следующие подфункции:

#### **Round**

Заглавие функции:

> unsigned int s21_round(s21_decimal value, s21_decimal *result)

Функция использует следующие подфункции:

#### **Truncate**

Заглавие функции:

> unsigned int s21_truncate(s21_decimal value, s21_decimal *result)

Функция использует следующие подфункции:

## **Help function**

***

### **Binary help function**

***

### **Decimal help function**

#### **Decimal correct**

Заглавие функции:

> unsigned int s21_decimal_is_correct(s21_decimal value).

Функция использует следующие подфункции:

* [Check null stack](#check-null-stack);
* [Get exp](#get-exp).

#### **Check null stack**

Заглавие функции:

> unsigned int s21_check_null_stack(s21_decimal value).

#### **Decimal init**

Заглавие функции:

> unsigned int s21_decimal_init(s21_decimal *decimal).

Функция использует следующие подфункцию:

s21_decimal_set_bit(*decimal, EXP_POS_L, 1).

#### **Decimal copy**

Заглавие функции:

> unsigned int s21_decimal_copy(s21_decimal src, s21_decimal *dest).

#### **Get sub 10**

Заглавие функции:

> static int s21_get_sub_10(bit_t prefix[], size_t n).

#### **Get sub to bin**

Заглавие функции:

> static bit_t *s21_sub_to_bin(bit_t prefix[], size_t n, unsigned int sub).


#### **Div 10**
> s21_decimal s21_decimal_div_10(s21_decimal decimal)

#### **Normalization**

Заглавие функции:

> unsigned int s21_normalization(s21_decimal *value_1, s21_decimal *value_2);

Функция использует следующие подфункции:

* [Get exp](#get-exp);
* [Count mul 10](#count-mul-10);
* [Add exp](#add-exp).

#### 
***

### **Arithmetic help function**

***

### **Comprasion operators help function**

***

### **Convertation and parsers help function**

***

### **Anouther help function**

***