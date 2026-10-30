#include <math.h>
#include <stdio.h>

#include "calculator.h"

double evaluate_postfix(Token *output_queue, int count) {
    if (count == 0 || output_queue == NULL) {
        return NAN;
    }
    double stack[100];
    int top = -1;

    for (int i = 0; i < count; i++) {
        if (output_queue[i].type == NUMBER) {
            stack[++top] = output_queue[i].data.value;
        } else if (output_queue[i].type == OPERATOR) {
            if (top < 1) {
                printf("not enough operands for operator\n");
                return NAN;
            }
            double b = stack[top--];
            double a = stack[top--];

            switch (output_queue[i].data.op) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/':
                    if (b == 0.0) {
                        printf("Invalid division by 0!\n");
                        return NAN;
                    }
                    stack[++top] = a / b;
                    break;
                default:
                    printf("Invalid expression!\n");
                    return NAN;
            }
        } else {
            printf("Unexpected token: %c\n", output_queue[i].data.op);
            return NAN;
        }
    }

    if (top > 0) {
        printf("invalid postfix expression. stack had %d expressions but should have 1\n", top + 1);
        return NAN;
    }
    return stack[0];
}