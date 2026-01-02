#include <stdio.h>

#define MAX_EXPRESSION_LENGTH 100



int main(void) {
    char expression[MAX_EXPRESSION_LENGTH];
    double num1, num2;
    char op;

    printf("Enter an expression:\n");
    fgets(expression, sizeof(expression), stdin);

    if (sscanf(expression, "%lf%c%lf",&num1, &op, &num2) == 3 ) {
        double result;
        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 == 0) {
                    printf("Error: Division by zero");
                    return 1;
                }
                result = num1 / num2;
                break;
            default:
                printf("invalid operator!");
                return 1;
        }
    printf("The answer to your expression is: %.2lf", result);
    }
    else {
        printf("Invalid expression!\n");
    }


    return 0;
}