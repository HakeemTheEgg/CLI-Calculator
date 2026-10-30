#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"

Token *tokenize(const char *expression, int *token_count) {
    Token *tokens = malloc(sizeof(Token) * MAX_TOKENS);

    if (!tokens) {
        printf("memory allocation failure!\n");
        return NULL;
    }
    int i = 0;
    int t = 0;

    while (expression[i] != '\0' && t < MAX_TOKENS) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        if (isdigit(expression[i]) || expression[i] == '.') {
            int j = 0;
            char num_string[50];
            while ((isdigit(expression[i]) || expression[i] == '.') && j < 49 && expression[i] != '\0') {
                num_string[j++] = expression[i++];
            }
            num_string[j] = '\0';
            tokens[t].type = NUMBER;
            tokens[t].data.value = atof(num_string);
            t++;
            continue;
        }
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            tokens[t].type = OPERATOR;
            tokens[t].data.op = expression[i];
            t++;
            i++;
            continue;
        }
        if (expression[i] == '(') {
            tokens[t].type = PAREN_LEFT;
            tokens[t].data.op = '(';
            t++;
            i++;
            continue;
        }
        if (expression[i] == ')') {
            tokens[t].type = PAREN_RIGHT;
            tokens[t].data.op = ')';
            t++;
            i++;
            continue;
        }
        printf("Invalid character: %c\n", expression[i]);
        free(tokens);
        return NULL;
    }
    tokens[t].type = END_OF_INPUT;
    *token_count = t;
    return tokens;
}

void printTokens(Token *tokens, int token_count) {
    printf("Tokens found(%d): \n", token_count);
    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type == NUMBER) {
            printf("  [NUMBER: %.2f]\n", tokens[i].data.value);
        } else if (tokens[i].type == OPERATOR) {
            printf("  [OPERATOR: %c]\n", tokens[i].data.op);
        }
    }
}