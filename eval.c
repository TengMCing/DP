//
// Created by Patrick Li on 10/7/22.
//

#include "eval.h"
#include <stdio.h>
#include <string.h>

void remove_end_of_line_and_space(char *expr)
{
    unsigned int expr_len = strnlen(expr, MAX_TOKEN_LEN);

    // Return if the string is empty
    if (expr_len == 0)
        return;

    // Start from the last character, till the first character
    for (unsigned int i = expr_len - 1; i >= 0; i--)
    {
        // Remove '\n' and ' '
        if (expr[i] == '\n' || expr[i] == ' ')
            expr[i] = '\0';
        else
            break;
    }
}

token_list_t tokenize(token_list_t token_list, char *expr)
{
    // Init token list
    token_list.num_tokens = 0;
    for (int i = 0; i < MAX_TOKEN_NUM; i++)
    {
        token_list.tokens_len[i] = 0;
        for (int j = 0; j < MAX_TOKEN_LEN; j++)
        {
            token_list.tokens[i][j] = '\0';
        }
    }

    unsigned char active = 0;

    remove_end_of_line_and_space(expr);

    unsigned int expr_len = strlen(expr);

    if (expr_len == 0)
    {
        print_prompt();
        return token_list;
    }

    // Split expression by space
    for (unsigned int i = 0; i < expr_len; i++)
    {
        if (expr[i] == ' ')
        {
            if (active)
                active = 0;
        }
        else
        {
            if (!active)
            {
                active = 1;
                token_list.num_tokens += 1;
            }
            int current_token = token_list.num_tokens - 1;
            int current_token_len = token_list.tokens_len[current_token];
            token_list.tokens[current_token][current_token_len] = expr[i];
            token_list.tokens_len[current_token] += 1;
        }
    }

    for (int i = 0; i < token_list.num_tokens; i++)
        printf("token[%d] = %s (%d)\n", i, token_list.tokens[i], token_list.tokens_len[i]);
    return token_list;
}

void eval(char *expr)
{
    token_list_t token_list;
    tokenize(token_list, expr);
}

// IR -> run-time
// NEW v VEC VEC_INT
// PUSH v 1

// IR -> C -> Machine code

// R-like language -> IR
// Use r code to build this part
// v = c(1,2,3) --> NEW v VEC VEC_INT\n PUSH v 1\n PUSH v 2\n PUSH v 3\n
// parser
// tokenizer
// abstract syntax tree