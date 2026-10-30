#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calculator.h"

int main(void) {
    char expression[MAX_EXPRESSION_LENGTH];

    printf("Enter an expression:\n");
    if (!fgets(expression, sizeof(expression), stdin)) {
        return 1;
    }
    expression[strcspn(expression, "\n")] = '\0';

    int num_tokens = 0;
    Token *tokens = tokenize(expression, &num_tokens);
    if (tokens == NULL) {
        return 1;
    }
    printTokens(tokens, num_tokens);

    int postfix_count = 0;
    Token *postfix = shunting_yard(tokens, num_tokens, &postfix_count);
    free(tokens);

    if (postfix == NULL) return 1;
    printf("Postfix order:\n");
    for (int i = 0; i < postfix_count; i++) {
        if (postfix[i].type == NUMBER) printf("%.0f ", postfix[i].data.value);
        else printf("%c ", postfix[i].data.op);
    }

    double result = evaluate_postfix(postfix, postfix_count);
    free(postfix);

    if (isnan(result)) {
        printf("result failed!\n");
        return 1;
    }

    printf("\nResult: %.2f\n", result);
    return 0;
}