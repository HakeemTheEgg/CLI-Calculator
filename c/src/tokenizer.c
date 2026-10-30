#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 50
#define MAX_EXPRESSION_LENGTH 100

//structs and enums for structure

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
void printTokens(Token *tokens, int token_count);

int main(void) {
    char expression[MAX_EXPRESSION_LENGTH];

    printf("Enter an expression: \n");
    fgets(expression, MAX_EXPRESSION_LENGTH, stdin);

    //get rid of newline
    expression[strcspn(expression, "\n")] = '\0';

    int token_count = 0;
    Token *tokens = tokenize(expression, &token_count);

    if (tokens != NULL) {
        printTokens(tokens, token_count);
        free(tokens);
    }




    return 0;
}

//function definitions
Token *tokenize(const char *expression, int *token_count) {
    Token *tokens = malloc(sizeof(Token) * MAX_TOKENS);
    printf("Allocated %llu bytes at address %p\n",
       sizeof(Token) * MAX_TOKENS,
       (void*)tokens);
    if (!tokens) {
        printf("memory allocation failed!\n");
        return NULL;
    }
    int i = 0;
    int t = 0;


    while (expression[i] != '\0' && t < MAX_TOKENS) {
         if (isspace(expression[i])) {
             i++; //skip whitespaces
             continue;
         }
        if (isdigit(expression[i]) || expression[i] == '.') {
            int j = 0;
            char num_string[50];

            while ((isdigit(expression[i]) || expression[i] == '.') && j<49) {
                num_string[j++] = expression[i++];  //store numbers and decimals in temporary buffer
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
            continue; //sorts the arithmetic symbols and places them as  "operator" types of the struct
        }

        printf("Unexpected character: %c\n", expression[i]);
        free(tokens);
        return NULL;
    }

    tokens[t].type = END_OF_INPUT;
    *token_count = t;
    return tokens;
}
void printTokens(Token *tokens, int token_count) {
    printf("Tokens found(%d):\n", token_count);
    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type == NUMBER) {
            printf(" Number: %.2f\n",tokens[i].data.value);
        }else if (tokens[i].type == OPERATOR) {
            printf(" Operator: %c\n",tokens[i].data.op);
        }
    }
}