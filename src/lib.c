#include "lib.h"
#include <stdbool.h> 
#include <ctype.h>
/**

@brief Визначає пріоритет оператора
@param c Символ оператора
@return Приорітет оператора (1 - самий низький, 3 - самий высокий), або -1, если символ не являється оператором
*/
int priority(char c) {
    switch (c) {
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        case '^': return 3;
        default: return -1;
    }
}
/**

@brief Обчислює підвираз з двох чисел та оператора
@param num1 Перше число
@param num2 Друге число
@param op Оператор (+, -, *, /, %, ^)
@return result Результат обчислення підвиразу
*/
int calculate_sub_expression(int num1, int num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                printf("Помилка: Ділення на нуль неможливе\n");
                return 0;
            }
            return num1 / num2;
        case '%':
            return num1 % num2;
        case '^':
            int result = 1;
            for (int i = 0; i < num2; i++) {
                result *= num1;
            }
            return result;
        default:
            return 0;
    }
}
/**

@brief Обчислює значення арифметичного виразу у вигляді рядка
@param expression Рядок з арифметичним виразом
@return Результат обчислення виразу
*/
int calculate(char* expression) {
    int num_stack[MAX_EXPR_LEN];
    char op_stack[MAX_EXPR_LEN];
    int num_top = -1;
    int op_top = -1;
    int i = 0;
    while (expression[i]) {
        if (isdigit(expression[i])) {
            int num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i++] - '0');
            }
            num_stack[++num_top] = num;
        } else if (strchr("+-*/%^", expression[i])) {
            while (op_top >= 0 && priority(op_stack[op_top]) >= priority(expression[i])) {
                int num2 = num_stack[num_top--];
                int num1 = num_stack[num_top--];
                char op = op_stack[op_top--];
                num_stack[++num_top] = calculate_sub_expression(num1, num2, op);
            }
            op_stack[++op_top] = expression[i++];
        } else if (expression[i] == '(') {
            op_stack[++op_top] = expression[i++];
        } else if (expression[i] == ')') {
            while (op_stack[op_top] != '(') {
                int num2 = num_stack[num_top--];
                int num1 = num_stack[num_top--];
                char op = op_stack[op_top--];
                num_stack[++num_top] = calculate_sub_expression(num1, num2, op);
            }
            op_top--;
            i++;
        } else {
            i++;
        }
    }
    while (op_top >= 0) {
        int num2 = num_stack[num_top--];
        int num1 = num_stack[num_top--];
        char op = op_stack[op_top--];
        num_stack[++num_top] = calculate_sub_expression(num1, num2, op);
    }
    return num_stack[num_top];
}
