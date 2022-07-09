//
// Created by Patrick Li on 9/7/22.
//

#ifndef VEC_LANG_VECTOR_H
#define VEC_LANG_VECTOR_H

#endif//VEC_LANG_VECTOR_H

typedef enum VEC_TYPE {
    VEC_INT = 0,
    VEC_FLOAT = 1,
    VEC_DOUBLE = 2,
    VEC_CHAR = 3,
    VEC_VEC_P = 4
} VEC_TYPE;

typedef struct vector {
    int size;
    int capacity;
    VEC_TYPE type;
    void *data;
} vector_t;

typedef vector_t *vector_p;

#define push_xx(vector, item, vec_type)                \
    resize(vector, v->size + 1);                       \
    ((vec_type *) (vector)->data)[(vector)->size] = x; \
    v->sie += 1

#define push_int(vector, item) \
    push_xx(vector, item, int)


vector_p new_vector(VEC_TYPE vec_type);

void delete_vector(vector_p vector);

void *get(vector_p vector, int index);

vector_p set(vector_p vector, int index, ...);

/// \n \n Add a constant to a vector
/// @description This function adds a constant to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_add(vector_p vector, ...);

/// \n \n Subtract a constant from a vector
/// @description This function subtracts a constant from a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_sub(vector_p vector, ...);

/// \n \n Multiply a constant to a vector
/// @description This function multiplies a constant to a vector.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_mul(vector_p vector, ...);

/// \n \n Divide a vector by a constant
/// @description This function divides a vector by a constant.
/// @param vector: (vector_p). A pointer to a vector.
/// @param ...: (int/float/double/char). A constant.
/// @return (vector_p) A pointer to the input vector.
vector_p const_div(vector_p vector, ...);

void print_vector_(vector_p vector, unsigned char depth);

vector_p resize(vector_p vector, int size);

vector_p push(vector_p vector, ...);

vector_p push_many(vector_p vector, int num_item, ...);

#define get_ij(vector, i, j) get(get(v, i), j)
#define resize_realloc(data, type, size) data = realloc(data, sizeof(type) * (size))

/// \n \n Print a vector and a '\\n'
/// @description This function prints a vector and a '\\n'.
/// @param vector: (vector_p). A pointer to a vector.
/// @param depth: (unsigned char). Depth to print.
/// @return No return value, called for side effects.
#define print_vector(vector, depth) \
    print_vector_(vector, depth);   \
    printf("\n")

#define as_int(void_p) *((int *) (void_p))
#define as_float(void_p) *((float *) (void_p))
#define as_double(void_p) *((double *) (void_p))
#define as_char(void_p) *((char *) (void_p))

#define const_op(op, name)                                                \
    vector_p const_##name(vector_p vector, ...) {                         \
        if (vector->type == VEC_VEC_P) {                                  \
            printf("ERROR: unable to add constant to a nested vector!");  \
            exit(1);                                                      \
        }                                                                 \
                                                                          \
        va_list ap;                                                       \
        va_start(ap, vector);                                             \
                                                                          \
        if (vector->type == VEC_INT) {                                    \
            int placeholder = va_arg(ap, int);                            \
            for (int i = 0; i < vector->size; i++) {                      \
                set(vector, i, as_int(get(vector, i)) op placeholder);    \
            }                                                             \
        }                                                                 \
                                                                          \
        if (vector->type == VEC_FLOAT) {                                  \
            float placeholder = (float) va_arg(ap, double);               \
            for (int i = 0; i < vector->size; i++) {                      \
                set(vector, i, as_float(get(vector, i)) op placeholder);  \
            }                                                             \
        }                                                                 \
                                                                          \
        if (vector->type == VEC_DOUBLE) {                                 \
            double placeholder = va_arg(ap, double);                      \
            for (int i = 0; i < vector->size; i++) {                      \
                set(vector, i, as_double(get(vector, i)) op placeholder); \
            }                                                             \
        }                                                                 \
                                                                          \
        if (vector->type == VEC_CHAR) {                                   \
            char placeholder = (char) va_arg(ap, int);                    \
            for (int i = 0; i < vector->size; i++) {                      \
                set(vector, i, as_char(get(vector, i)) op placeholder);   \
            }                                                             \
        }                                                                 \
                                                                          \
        va_end(ap);                                                       \
        return vector;                                                    \
    }
