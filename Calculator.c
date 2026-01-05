#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//macros
#define MAX_TOKENS 50
#define MAX_EXPRESSION_LENGTH 100

//structs and enums
typedef enum {
    NUMBER,
    OPERATOR,
    END_OF_INPUT,
    PAREN_LEFT,
    PAREN_RIGHT,
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
int get_precedence(Token operator_token);//checks precedence on operators
int is_left_associative(Token operator_token);//checks if the current operator is left associative
Token *shunting_yard(Token *input_token, int input_count, int *output_count );//implements shunting yard algorithm on the said tokens
void test_shunting_yard();// test the shunting yard algorithm
double evaluate_postfix(Token *output_queue, int count);//perform postfix evaluation on the return output array of the shunting yard algorithm


int main(void) {
    char expression[MAX_EXPRESSION_LENGTH];


    printf("Enter an expression:\n");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';//creates the array of expression s

    int num_tokens = 0;

    Token *tokens = tokenize(expression, &num_tokens); // converts the input array to tokens
    if (tokens == NULL) {
        return 1;
    }
    printTokens(tokens, num_tokens);

    int postfix_count = 0;
    Token *postfix = shunting_yard(tokens, num_tokens, &postfix_count); //converts the tokens to postfix notation and then frees them
    free(tokens);

    if (postfix == NULL) return 1;
    printf("Postfix order:\n");
    for (int i = 0; i < postfix_count; i++) {
        if (postfix[i].type == NUMBER) printf("%.0f ", postfix[i].data.value);//prints out each member of the postfix
        else printf("%c ", postfix[i].data.op);
    }

    double result = evaluate_postfix(postfix, postfix_count); //evaluated each member of the postfix and stores the result
    free(postfix);

    if (isnan(result)) {
        printf("result failed!");
        return 1;
    }

    printf("\nResult: %.2f",result);

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
        if (expression[i] == '(' ) {
            tokens[t].type = PAREN_LEFT;//handle parentheses
            tokens[t].data.op = '(';
            t++; i++;
            continue;

        }
        if (expression[i] == ')' ) {
            tokens[t].type = PAREN_RIGHT;
            tokens[t].data.op = ')';
            t++; i++;
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
    return (operator_token.data.op == '+' || operator_token.data.op == '-' || operator_token.data.op == '*' || operator_token.data.op == '/');
}
Token *shunting_yard(Token *input_token, int input_count, int *output_count ) {
    Token *output_queue = malloc(sizeof(Token) * input_count);
    Token *operator_stack = malloc(sizeof(Token) * input_count);

    int output_queue_index = 0;
    int operator_stack_index = -1;//it's made to have value of -1 to make sure that the stack is empty before even starting
    for (int i = 0; i < input_count; i++) {
        Token token = input_token[i];
        if (token.type == NUMBER) {
            output_queue[output_queue_index++] = token;
        }
        else if (token.type == OPERATOR) {
            while (operator_stack_index >= 0
                && operator_stack[operator_stack_index].type == OPERATOR
                && ((get_precedence(operator_stack[operator_stack_index]) > get_precedence(token))
                || (get_precedence(operator_stack[operator_stack_index]) == get_precedence(token) && is_left_associative(token)))
                && operator_stack[operator_stack_index].data.op != '(') {

                output_queue[output_queue_index++] = operator_stack[operator_stack_index--]; //pop from stack to output
            }
            operator_stack[++operator_stack_index] = token;
        }
        else if (token.type== PAREN_LEFT) {
            operator_stack[++operator_stack_index] = token;

        }
        else if (token.type == PAREN_RIGHT) {
            while (operator_stack_index >= 0 && operator_stack[operator_stack_index].data.op != '(') { //pop until '('
                output_queue[output_queue_index++] = operator_stack[operator_stack_index--];
            }
            if (operator_stack_index >= 0 && operator_stack[operator_stack_index].data.op == '(') {
                operator_stack_index--;
            }
            else {
                free(output_queue);
                free(operator_stack);
                *output_count = 0;
                return NULL;
            }

        }
    }
    while (operator_stack_index >= 0) {
        if (operator_stack[operator_stack_index].data.op == '(') {//mismatched or too much parenthesis
            free(output_queue);
            free(operator_stack);
            *output_count = 0;
            return NULL;
        }
        output_queue[output_queue_index++] = operator_stack[operator_stack_index--];//pop the rest
    }

    free(operator_stack);
    *output_count = output_queue_index;
    return output_queue;

}

void test_shunting_yard() {
    // Simple test: "3 + 4 * 2"
    Token input[] = {
        {NUMBER, .data.value = 3},
        {OPERATOR, .data.op = '+'},
        {NUMBER, .data.value = 4},
        {OPERATOR, .data.op = '*'},
        {NUMBER, .data.value = 2}
    };

    int output_count;
    Token* output = shunting_yard(input, 5, &output_count);

    if (output) {
        printf("Postfix output (%d tokens):\n", output_count);
        for (int i = 0; i < output_count; i++) {
            if (output[i].type == NUMBER) {
                printf("%.0f ", output[i].data.value);
            } else {
                printf("%c ", output[i].data.op);
            }
        }
        printf("\n");
        free(output);
    }
}




double evaluate_postfix(Token *output_queue, int count) {
    if (count == 0 || output_queue == NULL) {
        return NAN;
    }
    double stack[100];
    int top = -1;

    for (int i = 0; i < count; i++) {
        if (output_queue[i].type == NUMBER) {
            stack[++top] = output_queue[i].data.value;
        }
        else if (output_queue[i].type == OPERATOR) {
            if (top < 1){
            printf("not enough operands for operator");
            return NAN;}
            double b = stack[top--];
            double a = stack[top--];

            switch (output_queue[i].data.op) {
                case '+':
                    stack[++top] = a + b;
                    break;
                case  '-':
                    stack[++top] = a - b;
                    break;
                case  '*':
                    stack[++top] = a * b;
                    break;
                case  '/':
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

        }
        else {
            printf("Unexpected token: %c\n", output_queue[i].data.op);
            return NAN;
        }
    }

    if (top > 0) {
        printf("invalid postfix expression. stack had %d expressions but should have 1", top + 1);
        return NAN;
    }
    return stack[0];
}