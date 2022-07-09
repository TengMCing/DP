//
// Created by Patrick Li on 9/7/22.
//

#include "vector.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// \n \n Vector constructor
/// @description This function allocates memory for a vector for a given type.
/// @param vec_type: (VEC_TYPE). Vector type.
/// @return (vector_p). A pointer to a vector.
vector_p new_vector(VEC_TYPE vec_type) {
    // Allocate memory for the struct
    vector_p vector = malloc(sizeof(vector_t));
    vector->capacity = 10;
    vector->size = 0;
    vector->type = vec_type;

    // Allocate memory for the container
    // Array of integers
    if (vec_type == VEC_INT)
        vector->data = calloc(vector->capacity, sizeof(int));

    // Array of floats
    if (vec_type == VEC_FLOAT)
        vector->data = calloc(vector->capacity, sizeof(float));

    // Array of doubles
    if (vec_type == VEC_DOUBLE)
        vector->data = calloc(vector->capacity, sizeof(double));

    // Array of chars
    if (vec_type == VEC_CHAR)
        vector->data = calloc(vector->capacity, sizeof(char));

    // Array of pointers to vector
    if (vec_type == VEC_VEC_P)
        vector->data = calloc(vector->capacity, sizeof(vector_p));

    return v;
}

/// \n \n Vector destroyer
/// @description This function deallocates memory for a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @return No return value, called for side effects.
void delete_vector(vector_p vector) {
    // Deallocate the memory of the inner vectors
    if (vector->type == VEC_VEC_P) {
        vector_p *vec_p_arr = (vector_p *) vector->data;
        for (int i = 0; i < vector->size; i++)
            delete_vector(vec_p_arr[i]);
    }

    // If type == VEC_VEC_P, deallocate the memory for storing the pointers to vector
    // Otherwise, deallocate the memory of an (int/float/double/char) array
    free(vector->data);

    // Deallocate the memory of the struct
    free(vector);
}


/// \n \n Get an item from a vector
/// @description This function gets the memory address of an (int/float/double/char) or
/// the pointer to the inner vector. Boundaries will be checked.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @return (void*) A void pointer pointing to that memory address.
void *get(vector_p vector, int index) {
    if (index >= vector->size || index < 0) {
        printf("ERROR: Index %d out of bound!", index);
        exit(1);
    }

    // Get the address of the item in an array
    if (vector->type == VEC_INT)
        return ((int *) vector->data) + index;
    if (vector->type == VEC_FLOAT)
        return ((float *) vector->data) + index;
    if (vector->type == VEC_DOUBLE)
        return ((double *) vector->data) + index;
    if (vector->type == VEC_CHAR)
        return ((char *) vector->data) + index;

    // Get what it points to
    if (vector->type == VEC_VEC_P)
        return ((vector_p *) vector->data)[index];

    return NULL;
}


/// \n \n Assign value to an item of a vector
/// @description This function assigns a value to an item of a vector. Boundaries will be checked.
/// @details It will cast the input as what `vector->type` indicated.
/// So make sure value of the correct type is passed. \n
/// Replacing an existing vector with another vector could lead to memory leak if
/// there are any other pointers pointing to the existing vector. \n
/// As a variadic function, it will promote (float) to (double) and (char) to (int) as input.
/// @param vector: (vector_p). A pointer to a vector.
/// @param index: (int). Index of the item.
/// @param ...: (int/float/double/char/vector_p). Item to be assigned.
/// @return (vector_p) A pointer to the input vector.
vector_p set(vector_p vector, int index, ...) {
    if (index >= vector->size || index < 0) {
        printf("ERROR: Index %d out of bound!", index);
        exit(1);
    }

    va_list ap;
    va_start(ap, index);

    if (vector->type == VEC_INT)
        ((int *) vector->data)[index] = va_arg(ap, int);

    // Type promotion
    if (vector->type == VEC_FLOAT)
        ((float *) vector->data)[index] = (float) va_arg(ap, double);

    if (vector->type == VEC_DOUBLE)
        ((double *) vector->data)[index] = va_arg(ap, double);

    // Type promotion
    if (vector->type == VEC_CHAR)
        ((char *) vector->data)[index] = (char) va_arg(ap, int);

    if (vector->type == VEC_VEC_P) {
        // Get the old vector
        vector_p old_v = (vector_p) get(vector, index);
        vector_p new_v = va_arg(ap, vector_p);

        // If both pointer points to the same vector
        if (old_v == new_v) {
            printf("WARNING: try to replace the vector with the same vector!");
            return vector;
        }

        if (old_v != NULL) {
            // Delete the old vector
            delete_vector(old_v);
        }

        // Assign the new pointer to the array
        ((vector_p *) vector->data)[index] = new_v;
    }

    va_end(ap);
    return vector;
}

// Add constant to a vector
const_op(+, add);

// Subtract a constant from a vector
const_op(-, sub);

// Multiply constant to a vector
const_op(*, mul);

// Divide a vector by a constant
const_op(/, div);

/// \n \n Print a vector
/// @description This function print a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param depth: (unsigned char). Depth to print.
/// @return No return value, called for side effects.
void print_vector_(vector_p vector, unsigned char depth) {
    printf("[");

    if (vector->type == VEC_INT) {
        for (int i = 0; i < vector->size; i++)
            printf("%i, ", as_int(get(vector, i)));
    }

    if (vector->type == VEC_FLOAT) {
        for (int i = 0; i < vector->size; i++)
            printf("%.3f, ", as_float(get(vector, i)));
    }

    if (vector->type == VEC_DOUBLE) {
        for (int i = 0; i < vector->size; i++)
            printf("%.3f, ", as_double(get(vector, i)));
    }

    if (vector->type == VEC_CHAR)
        printf("\"%s\"  ", ((char *) vector->data));

    if (vector->type == VEC_VEC_P) {
        if (depth <= 1)
            printf("<VEC_P>: %d  ", vector->size);
        else {
            vector_p *vec_p_arr = (vector_p *) vector->data;
            for (int i = 0; i < vector->size; i++) {
                print_vector_(vec_p_arr[i], depth - 1);
                printf(", ");
            }
        }
    }

    if (vector->size > 0 || (vector->type == VEC_VEC_P && depth <= 1))
        printf("\b\b");

    printf("]");
}

/// \n \n Resize a vector
/// @description This function increases the capacity of a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param size: (int). Target size.
/// @return (vector_p) A pointer to the input vector.
vector_p resize(vector_p vector, int size) {
    if (vector->capacity >= size)
        return vector;

    while (vector->capacity < size) {
        vector->capacity *= 3 + 8;
    }

    if (vector->type == VEC_INT)
        resize_realloc(vector->data, int, vector->capacity);

    if (vector->type == VEC_FLOAT)
        resize_realloc(vector->data, float, vector->capacity);

    if (vector->type == VEC_DOUBLE)
        resize_realloc(vector->data, double, vector->capacity);

    if (vector->type == VEC_CHAR)
        resize_realloc(vector->data, char, vector->capacity);

    if (vector->type == VEC_VEC_P)
        resize_realloc(vector->data, vector_p, vector->capacity);

    return vector;
}

/// \n \n Push an item to a vector
/// @description This function pushes an item to a vector.
/// @details It will cast the input as what `vector->type` indicated.
/// So make sure value of the correct type is passed. \n
/// As a variadic function, it will promote (float) to (double) and (char) to (int) as input.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char/vector_p). Item to be pushed.
/// @return (vector_p) A pointer to the input vector.
vector_p push(vector_p vector, ...) {
    va_list ap;
    va_start(ap, vector);

    resize(vector, vector->size + 1);

    if (vector->type == VEC_INT)
        ((int *) vector->data)[vector->size] = va_arg(ap, int);

    // type promotion
    if (vector->type == VEC_FLOAT)
        ((float *) vector->data)[vector->size] = (float) va_arg(ap, double);

    if (vector->type == VEC_DOUBLE)
        ((double *) vector->data)[vector->size] = va_arg(ap, double);

    // type promotion
    if (vector->type == VEC_CHAR)
        ((char *) vector->data)[vector->size] = (char) va_arg(ap, int);

    if (vector->type == VEC_VEC_P)
        ((vector_p *) vector->data)[vector->size] = va_arg(ap, vector_p);

    va_end(ap);
    vector->size += 1;
    return vector;
}

// Push many items to a vector
// float will be promoted to double
// char will be promoted to int
/// \n \n Push arbitrary items to a vector
/// @description This function pushes arbitrary items to a vector.
/// @details It will cast inputs as what `vector->type` indicated.
/// So make sure value of the correct type is passed. \n
/// As a variadic function, it will promote (float) to (double) and (char) to (int) as input.
/// @param vector: (vector_p). A pointer to a vector.
/// @param num_item: (int). Number of items.
/// @param ...: (int/float/double/char/vector_p). Items to be pushed.
/// @return (vector_p) A pointer to the input vector.
vector_p push_many(vector_p vector, int num_item, ...) {
    va_list ap;
    va_start(ap, num_item);

    resize(vector, vector->size + num_item);

    if (vector->type == VEC_INT) {
        for (int i = vector->size; i < vector->size + num_item; i++) {
            ((int *) vector->data)[i] = va_arg(ap, int);
        }
    }

    // type promotion
    if (vector->type == VEC_FLOAT) {
        for (int i = vector->size; i < vector->size + num_item; i++) {
            ((float *) vector->data)[i] = (float) va_arg(ap, double);
        }
    }

    if (vector->type == VEC_DOUBLE) {
        for (int i = vector->size; i < vector->size + num_item; i++) {
            ((double *) vector->data)[i] = va_arg(ap, double);
        }
    }

    // type promotion
    if (vector->type == VEC_CHAR) {
        for (int i = vector->size; i < vector->size + num_item; i++) {
            ((char *) vector->data)[i] = (char) va_arg(ap, int);
        }
    }

    if (vector->type == VEC_VEC_P) {
        for (int i = vector->size; i < vector->size + num_item; i++) {
            ((vector_p *) vector->data)[i] = va_arg(ap, vector_p);
        }
    }

    va_end(ap);
    vector->size += num_item;
    return vector;
}

#define MAX_TOKEN_NUM 255
#define MAX_TOKEN_LEN 255

typedef struct token_list {
    char num_tokens;
    char tokens[MAX_TOKEN_NUM][MAX_TOKEN_LEN];
    char tokens_len[MAX_TOKEN_NUM];
} token_list_t;

#define print_empty_line() printf(">>>\n")

void remove_end_of_line_and_space(char *expr) {
    int expr_len = strlen(expr);
    if (expr_len == 0)
        return;
    int i = expr_len - 1;
    while (i >= 0) {
        if (expr[i] == '\n' || expr[i] == ' ') {
            expr[i] = '\0';
        } else {
            break;
        }
        i -= 1;
    }
}

void eval(char *expr) {
    token_list_t token_list;

    // Init token list
    token_list.num_tokens = 0;
    for (int i = 0; i < MAX_TOKEN_NUM; i++) {
        token_list.tokens_len[i] = 0;
        for (int j = 0; j < MAX_TOKEN_LEN; j++) {
            token_list.tokens[i][j] = '\0';
        }
    }

    char active = 0;

    remove_end_of_line_and_space(expr);

    int expr_len = strlen(expr);

    if (expr_len == 0) {
        print_empty_line();
        return;
    }

    // Split expression by space
    for (int i = 0; i < expr_len; i++) {
        if (expr[i] == ' ') {
            if (active)
                active = 0;
        } else {
            if (!active) {
                active = 1;
                token_list.num_tokens += 1;
            }
            char current_token = token_list.num_tokens - 1;
            char current_token_len = token_list.tokens_len[current_token];
            token_list.tokens[current_token][current_token_len] = expr[i];
            token_list.tokens_len[current_token] += 1;
        }
    }

    // Check the first argument
    if (strcmp(token_list.tokens[0], "NEW") == 0) {
        ;
    }
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