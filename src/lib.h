/**

@file lib.h
@brief Файл з оголошеннями функцій для обчислення арифметичних виразів
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
/**

@def MAX_EXPR_LEN
@brief Максимальна довжина виразу
*/
#define MAX_EXPR_LEN 100
/**

@brief Визначення приорітета для математичних знаків
@param c Оператор для определения приоритета
*/
int priority(char c);
/**

@brief Обчислює результат виразу, що складається з двох чисел та оператора
@param num1 Перше число у виразі
@param num2 Друге число у виразі
@param op Оператор у висловленні
*/
int calculate_sub_expression(int num1, int num2, char op);
/**

@brief Обчислює результат арифметичного виразу
@param expression Арифметичний вираз для обчислення
*/
int calculate(char* expression);
