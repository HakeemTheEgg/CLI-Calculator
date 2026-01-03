#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//macros
#define MAX_TOKENS 50
#define MAX_EXPRESSION_LENGTH 100

//structs and enums
typedef enum {
    NUMBER,
    OPERATOR,
    END_OF_INPUT,
}TokenType;

typedef struct {
    TokenType type;
    union {
        double value;
        char op;
    }data;
}Token;

//function declarations
Token *tokenize(const char *expression, int *token_count);
void printTokens(Token *token, int token_count);

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

//function definitions
Token *tokenize(const char *expression, int *token_count) {
    Token *tokens = malloc(sizeof(Token) * MAX_TOKENS);
    printf("allocated %llu bytes at address %p", sizeof(Token) * MAX_TOKENS, (void*)tokens);

    if (!tokens) {
        printf("memory allocation failure!\n");
        return NULL;
    }
    int i = 0; // loop counter
    int t = 0; //token counter

    while (expression[i] != '\0' && t <MAX_TOKENS) {
        if (isspace(expression[i])) {
            i++;
            continue;

        }
        if (isdigit(expression[i]) || expression[i] == '.') {
            int j = 0;
            char num_string[50];
            while ((isdigit(expression[i]) || expression[i] == '.') && j < 49) {
                num_string[j++] = expression[i++]; //temporary buffer for holding decimal numbers
            }
            num_string[j] = '\0';
            tokens[t].type = NUMBER;
            tokens[t].data.value= atof(num_string);
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
        printf("Unexpected character: %c\n", expression[i]);
        free(tokens);
        return NULL;
    }
    tokens[t].type = END_OF_INPUT;
    *token_count = t;
    return tokens;
}

void printTokens(Token *token, int token_count) {
    printf("Tokens found(%d): ", token_count);
    for (int i = 0; i < token_count; i++) {
        if (token[i].type == NUMBER) {
            printf("Number: %.3lf\n", token[i].data.value);
        }
        else if (token[i].type == OPERATOR) {
            printf("Operator: %c\n", token[i].data.op);
        }
    }


}