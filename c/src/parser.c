#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"

int get_precedence(Token operator_token) {
    switch (operator_token.data.op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int is_left_associative(Token operator_token) {
    return (operator_token.data.op == '+' || operator_token.data.op == '-' ||
            operator_token.data.op == '*' || operator_token.data.op == '/');
}

Token *shunting_yard(Token *input_tokens, int input_count, int *output_count) {
    Token *output_queue = malloc(sizeof(Token) * input_count);
    Token *operator_stack = malloc(sizeof(Token) * input_count);

    if (!output_queue || !operator_stack) {
        free(output_queue);
        free(operator_stack);
        *output_count = 0;
        return NULL;
    }

    int output_queue_index = 0;
    int operator_stack_index = -1;

    for (int i = 0; i < input_count; i++) {
        Token token = input_tokens[i];
        if (token.type == NUMBER) {
            output_queue[output_queue_index++] = token;
        } else if (token.type == OPERATOR) {
            while (operator_stack_index >= 0
                && operator_stack[operator_stack_index].type == OPERATOR
                && ((get_precedence(operator_stack[operator_stack_index]) > get_precedence(token))
                    || (get_precedence(operator_stack[operator_stack_index]) == get_precedence(token)
                        && is_left_associative(token)))
                && operator_stack[operator_stack_index].data.op != '(') {
                output_queue[output_queue_index++] = operator_stack[operator_stack_index--];
            }
            operator_stack[++operator_stack_index] = token;
        } else if (token.type == PAREN_LEFT) {
            operator_stack[++operator_stack_index] = token;
        } else if (token.type == PAREN_RIGHT) {
            while (operator_stack_index >= 0 && operator_stack[operator_stack_index].data.op != '(') {
                output_queue[output_queue_index++] = operator_stack[operator_stack_index--];
            }
            if (operator_stack_index >= 0 && operator_stack[operator_stack_index].data.op == '(') {
                operator_stack_index--;
            } else {
                free(output_queue);
                free(operator_stack);
                *output_count = 0;
                return NULL;
            }
        }
    }
    while (operator_stack_index >= 0) {
        if (operator_stack[operator_stack_index].data.op == '(') {
            free(output_queue);
            free(operator_stack);
            *output_count = 0;
            return NULL;
        }
        output_queue[output_queue_index++] = operator_stack[operator_stack_index--];
    }

    free(operator_stack);
    *output_count = output_queue_index;
    return output_queue;
}