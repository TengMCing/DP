//
// Created by Patrick Li on 10/7/22.
//

#ifndef VEC_LANG_EVAL_H
#define VEC_LANG_EVAL_H

#endif//VEC_LANG_EVAL_H

/*-----------------------------------------------------------------------------
 |  Token List Data Structure
 ----------------------------------------------------------------------------*/

#define MAX_TOKEN_NUM 255
#define MAX_TOKEN_LEN 255

typedef struct token_list
{
    int num_tokens;
    char tokens[MAX_TOKEN_NUM][MAX_TOKEN_LEN];
    int tokens_len[MAX_TOKEN_NUM];
} token_list_t;

/*-----------------------------------------------------------------------------
 |  Token List Data Structure
 ----------------------------------------------------------------------------*/

#define MAX_VAR_NUM 255
#define MAX_VAR_NAME_LEN MAX_TOKEN_LEN

typedef struct var_table
{
    int num_var;
    void *data;
    char var_name[MAX_VAR_NUM][MAX_VAR_NAME_LEN];
} var_table_t;


/*-----------------------------------------------------------------------------
 |  REPL APIs
 ----------------------------------------------------------------------------*/

/// \n \n Print prompt in a new line
/// @description This function prints prompt in a new line.
/// @return No return value, called for side effects.
#define print_prompt() printf("\n>>>")

/// \n \n Remove '\\n' and ' ' from the end of a string
/// @description This function removes '\\n' and ' ' from the end of a string.
/// @param expr: (char*). A mutable string.
/// @return No return value, called for side effects.
void remove_end_of_line_and_space(char *expr);

void eval(char *expr);

token_list_t tokenize(token_list_t token_list, char *expr);