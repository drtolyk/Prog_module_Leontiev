#include "lib.h"
/**

@brief Головна функція програми.
@expression Арифметичний вираз для обчислення
@result результат
@return 0 завершення програми.
*/
#define MAX_EXPR_LEN 100 

int main() {
    char expression[MAX_EXPR_LEN];
    printf("Введіть математичний вираз: ");
    fgets(expression, MAX_EXPR_LEN, stdin);
    double result = calculate(expression);
    printf("Результат: %.0lf\n", result);
    return 0;
}
