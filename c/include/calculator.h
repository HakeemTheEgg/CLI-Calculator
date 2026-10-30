#ifndef CALCULATOR_H
#define CALCULATOR_H

#define MAX_TOKENS 50
#define MAX_EXPRESSION_LENGTH 100

typedef enum {
    NUMBER,
    OPERATOR,
    END_OF_INPUT,
    PAREN_LEFT,
    PAREN_RIGHT,
} TokenType;

typedef struct {
    TokenType type;
    union {
        double value;
        char op;
    } data;
} Token;

/* tokenizer.c */
Token *tokenize(const char *expression, int *token_count);
void printTokens(Token *tokens, int token_count);

/* parser.c */
int get_precedence(Token operator_token);
int is_left_associative(Token operator_token);
Token *shunting_yard(Token *input_tokens, int input_count, int *output_count);

/* evaluator.c */
double evaluate_postfix(Token *output_queue, int count);

#endif /* CALCULATOR_H */