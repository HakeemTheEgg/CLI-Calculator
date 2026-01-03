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
Token *tokenize(const char *expression, int *token_count);//converts the array into individual operators/operands(Tokens)
void printTokens(Token *token, int token_count);//prints out each of the individual tokens
double evaluate_from_left_to_right(Token *token, int token_count);//evaluates from left to right without operator precedent

int main(void) {
    char expression[MAX_EXPRESSION_LENGTH];


    printf("Enter an expression:\n");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';

    int num_tokens = 0;

    Token *tokens = tokenize(expression, &num_tokens);
    if (tokens == NULL) {
        return 1;
    }
    printTokens(tokens, num_tokens);

    double result = evaluate_from_left_to_right(tokens, num_tokens);
    printf("Result: %.2lf\n", result);

    free(tokens);
    return 0;


}

//function definitions
Token *tokenize(const char *expression, int *token_count) {
    Token *tokens = malloc(sizeof(Token) * MAX_TOKENS);
    printf("allocated %llu bytes at address %p\n", sizeof(Token) * MAX_TOKENS, (void*)tokens);

    if (!tokens) {
        printf("memory allocation failure!\n");
        return NULL;
    }
    int i = 0; // loop counter
    int t = 0; //token counter

    while (expression[i] != '\0' && t <MAX_TOKENS) {
        if (isspace(expression[i])) {
            i++;//skips whitespaces
            continue;

        }
        if (isdigit(expression[i]) || expression[i] == '.') {
            int j = 0;
            char num_string[50];
            while ((isdigit(expression[i]) || expression[i] == '.') && j < 49 && expression[i] != '\0') {
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
            tokens[t].data.op = expression[i];//creates a token struct for holding operators
            t++;
            i++;
            continue;
        }
        printf("Invalid character: %c\n", expression[i]);
        free(tokens);//free space temporary allocated
        return NULL;
    }
    tokens[t].type = END_OF_INPUT;
    *token_count = t;
    return tokens;
}

void printTokens(Token *token, int token_count) {
    printf("Tokens found(%d): \n", token_count);
    for (int i = 0; i < token_count; i++) {
        if (token[i].type == NUMBER) {
            printf("  [NUMBER: %.2f]\n", token[i].data.value);
        }
        else if (token[i].type == OPERATOR) {
            printf("  [OPERATOR: %c]\n", token[i].data.op);
        }
    }


}
double evaluate_from_left_to_right(Token *token, int token_count) {
    if (token_count == 0) {
        printf("Expression can not be empty!\n");
        return 0.0;
    }
    if (token[0].type != NUMBER) {
        printf("Expression cant start with an operator!\n");
        return 0.0;
    }
    double result = token[0].data.value;

    for (int i = 1; i < token_count; i += 2 ) {
        if (i + 1 >= token_count) {
            printf("Incomplete expression - missing number after operator\n");
            return result;
        }
        if (token[i].type != OPERATOR) {
            printf("Expected operator, got number\n");
            return result;
        }
        if (token[i + 1].type != NUMBER) {
            printf("Expected number after operator!\n");
            return result;
        }

        char op = token[i].data.op;//stores current operator
        double num2 = token[i + 1].data.value;

        switch (op) {
            case '+':
                result += num2;
                break;
            case '-':
                result -= num2;
                break;
            case '*':
                result *= num2;
                break;
            case '/':
                if (num2 == 0.0) {
                    printf("Error: Division by zero\n");
                    return result;
                }
                result /= num2;
                break;
            default:
                printf("invalid operator!: %c\n", op);
                return 1;

        }
    }
    return result;
}